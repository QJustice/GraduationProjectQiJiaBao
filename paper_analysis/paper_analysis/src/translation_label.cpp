#include "translation_label.h"

#include <iostream>
#include <fstream>

#include <json/json.h>

#include "config.h"
#include "error_code.h"

qi::CTranslationLabel::CTranslationLabel()
{
  this->root_ = nullptr;
  this->reader_ = nullptr;
}

qi::CTranslationLabel::CTranslationLabel(char const* file_path)
{
  this->root_ = nullptr;
  this->reader_ = nullptr;
  this->file_path_ = file_path;
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
  const char* path = file_path;

  //读取文件中的数据
  std::ifstream ifs; // 创建一个 std::ifstream 对象
  ifs.open(path, std::ios::in || std::ios::binary);
  if (!ifs.is_open())
  {
    std::cerr << "Error: open file is failed! " << std::endl;
    return qierr::E_OPENFAIL;
  }
  else
  {
    std::cout << "Successful: file read is success! " << std::endl;
  }
  this->root_ = new Json::Value();
  this->reader_ = new Json::Reader(Json::Features::strictMode());
  if (!reader_)
  {
    std::cerr << "reader_ is null" << std::endl;
    return qierr::E_EMPTY;
  }
  bool ret = this->reader_->parse(ifs, *this->root_);
  if (!ret) {
    std::cout << "parseJsonFromString error!" << std::endl;
    return qierr::E_INITFAIL;
  }

  ifs.close();

  return 0;
}

bool qi::CTranslationLabel::belongToMember(char const* member_name, Json::Value* node)
{
  if (!node)
  {
    std::cerr << "node is null" << std::endl;
    return false;
  }
  if (!node->isObject())
  {
    std::cerr << "node is not object. Cannot obtain member " << member_name << std::endl;
    return false;
  }
  Json::Value::Members members = node->getMemberNames();
  if (members.empty())
  {
    std::cerr << "members is empty" << std::endl;
    return false;
  }
  if (!node->isMember(member_name))
  {
    std::cerr << "node is not member " << member_name << std::endl;
    return false;
  }
  return true;
}

std::string qi::CTranslationLabel::getLabelDescription(char const* lable_name, char const* lable_sign)
{
  Json::StreamWriterBuilder builder;
  builder["emitUTF8"] = true;
  std::string str = "NULL";
  if (!this->root_)
  {
    std::cerr << "root_ is null" << std::endl;
    return str;
  }
  if (!belongToMember(lable_name, this->root_))
    return str;
  if (!belongToMember(lable_sign, &((*this->root_)[lable_name])))
    return str;
  Json::Value value = (*this->root_)[lable_name][lable_sign];
  str = Json::writeString(builder, value);

  return str;
}

Json::Value qi::CTranslationLabel::getLabelAttribute(char const* lable_name, char const* lable_sign)
{
  if (!this->root_)
  {
    std::cerr << "root_ is null" << std::endl;
    return NULL;
  }
  if (!belongToMember(lable_name, this->root_))
    return NULL;
  if (!belongToMember(lable_sign, &((*this->root_)[lable_name])))
    return NULL;
  return (*this->root_)[lable_name][lable_sign];
}

Json::Value qi::CTranslationLabel::getLabelAttributeValue(char const* lable_name, char const* lable_sign, char const* attribute_value)
{
  if (!this->root_)
  {
    std::cerr << "root_ is null" << std::endl;
    return NULL;
  }
  if (!belongToMember(lable_name, this->root_))
    return NULL;
  if (!belongToMember(lable_sign, &((*this->root_)[lable_name])))
    return NULL;
  if (!belongToMember(attribute_value, &((*this->root_)[lable_name][lable_sign])))
    return NULL;

  return (*this->root_)[lable_name][lable_sign][attribute_value];
}
