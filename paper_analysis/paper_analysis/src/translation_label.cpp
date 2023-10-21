#include "translation_label.h"

#include <iostream>
#include <fstream>
 
#include <json/json.h>
 
#include "config.h"
#include "error_code.h"

qi::CTranslationLabel::CTranslationLabel()
{
}

qi::CTranslationLabel::CTranslationLabel(const std::string& filePath) : m_filePath_(filePath)
{
}

qierr::error_code qi::CTranslationLabel::loadFile(char const* file_path)
{
  this->m_filePath_ = file_path;
  // 从文件中读取json内容
  std::ifstream file(m_filePath_);
  if (!file.is_open()) {
    std::cout << "Failed to open JSON file" << std::endl;
    return qierr::E_OPENFAIL;
  }
  bool parsingSuccessful = m_reader_.parse(file, this->m_root_);
  file.close();

  if (!parsingSuccessful) {
    std::cout << "Failed to parse JSON" << std::endl;
    return qierr::E_JSONEXCEPTION_CODE;
  }

  return qierr::E_OK;
}


std::string qi::CTranslationLabel::findValueByKey(const std::string& key)
{
  //// 打印全部key和value
  //Json::Value::Members members = this->m_root_.getMemberNames();
  //for (auto iter = members.begin(); iter != members.end(); iter++) {
  //  std::cout << *iter << ": " << this->m_root_[*iter].asString() << std::endl;
  //}

  // 查找key对应的value
  if (this->m_root_.isMember(key)) {
    Json::Value value = this->m_root_[key];
    if (value.isString()) {
      return value.asString();
    }
  }
  return  "Key '" + key + "' not found";
}

#if 0

qi::CTranslationLabel::CTranslationLabel()
{
  this->root_ = nullptr;
  this->reader_ = nullptr;
}

qi::CTranslationLabel::~CTranslationLabel()
{
  if (this->root_)
  {
    delete this->root_;
    this->root_ = nullptr;
  }
  if (this->reader_)
  {
    delete this->reader_;
    this->reader_ = nullptr;
  }
}

qierr::error_code qi::CTranslationLabel::loadFile(char const* file_path)
{
  char const* path = file_path;

  //读取文件中的数据
  std::ifstream ifs; // 创建一个 std::ifstream 对象
  ifs.open(path, std::ios::in || std::ios::binary);
  if (!ifs.is_open())
  {
    // std::cerr << "Error: open file is failed! "<< " ";
    return qierr::E_OPENFAIL;
  }
  else
  {
    // std::cout << "Successful: file read is success! "<< " ";
  }
  this->root_ = new Json::Value();
  this->reader_ = new Json::Reader(Json::Features::strictMode());
  if (!reader_)
  {
    std::cerr << "reader_ is null" << " ";
    return qierr::E_EMPTY;
  }
  bool ret = this->reader_->parse(ifs, *this->root_);
  if (!ret) {
    std::cout << "parseJsonFromString error!" << " ";
    return qierr::E_INITFAIL;
  }

  ifs.close();

  return qierr::E_OK;
}

bool qi::CTranslationLabel::belongToMember(char const* member_name, Json::Value* node)
{
  if (!node)
  {
    std::cerr << "node is null" << " ";
    return false;
  }
  if (!node->isObject())
  {
    std::cerr << "node is not object. Cannot obtain member " << member_name << " ";
    return false;
  }
  Json::Value::Members members = node->getMemberNames();
  if (members.empty())
  {
    std::cerr << "members is empty" << " ";
    return false;
  }
  if (!node->isMember(member_name))
  {
    std::cerr << "node is not member " << member_name << " ";
    return false;
  }
  return true;
}

std::string qi::CTranslationLabel::getLabelDescription(char const* lable_name, char const* lable_attribute)
{
  std::string str = "NULL";
  if (!this->root_)
  {
    std::cerr << "root_ is null" << " ";
    return str;
  }
  if (!belongToMember(lable_name, this->root_))
    return str;
  if (!belongToMember(lable_attribute, &((*this->root_)[lable_name])))
    return str;
  Json::StreamWriterBuilder builder;
  builder["emitUTF8"] = true;
  Json::Value value = (*this->root_)[lable_name][lable_attribute];
  str = Json::writeString(builder, value);

  return str;
}

std::string qi::CTranslationLabel::getLabelAttributeDescription(char const* lable_name, char const* lable_attribute, char const* attribute_value)
{
  std::string str = "NULL";
  if (!this->root_)
  {
    std::cerr << "root_ is null" << " ";
    return str;
  }
  if (!belongToMember(lable_name, this->root_))
    return str;
  if (!belongToMember(lable_attribute, &((*this->root_)[lable_name])))
    return str;
  Json::StreamWriterBuilder builder;
  builder["emitUTF8"] = true;
  Json::Value value = (*this->root_)[lable_name][lable_attribute];
  if (value.type() == Json::ValueType::stringValue)
  {
    if (attribute_value == "Description")
      str = Json::writeString(builder, value);
    else
      return attribute_value;
  }
  else if (value.type() == Json::ValueType::objectValue)
  {
    if (!belongToMember(attribute_value, &((*this->root_)[lable_name][lable_attribute])))
      return str;
    value = (*this->root_)[lable_name][lable_attribute][attribute_value];
    str = Json::writeString(builder, value);
  }
  else
  {
    std::cerr << "value type is not string or object" << " ";
    return str;
  }
  return str;
}

Json::Value qi::CTranslationLabel::getLabelAttribute(char const* lable_name, char const* lable_attribute)
{
  if (!this->root_)
  {
    std::cerr << "root_ is null" << " ";
    return NULL;
  }
  if (!belongToMember(lable_name, this->root_))
    return NULL;
  if (!belongToMember(lable_attribute, &((*this->root_)[lable_name])))
    return NULL;
  return (*this->root_)[lable_name][lable_attribute];
}

Json::Value qi::CTranslationLabel::getLabelAttributeValue(char const* lable_name, char const* lable_attribute, char const* attribute_value)
{
  if (!this->root_)
  {
    std::cerr << "root_ is null" << " ";
    return NULL;
  }
  if (!belongToMember(lable_name, this->root_))
    return NULL;
  if (!belongToMember(lable_attribute, &((*this->root_)[lable_name])))
    return NULL;
  if (!belongToMember(attribute_value, &((*this->root_)[lable_name][lable_attribute])))
    return NULL;

  return (*this->root_)[lable_name][lable_attribute][attribute_value];
}
#endif
