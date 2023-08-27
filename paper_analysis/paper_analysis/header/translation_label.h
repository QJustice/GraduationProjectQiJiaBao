#ifndef PAPER_ANALYSIS_TRANSLATION_LABEL_H
#define PAPER_ANALYSIS_TRANSLATION_LABEL_H

#include <string>

#include <json/json.h>

#include "config.h"
#include "error_code.h"

namespace qi {

class CTranslationLabel
{
 public:
  CTranslationLabel();
  ~CTranslationLabel();

  qierr::error_code loadFile(char const* file_path);
  bool belongToMember(char const* member_name, Json::Value* node);
  std::string getLabelDescription(char const* lable_name, char const* lable_attribute);
  std::string getLabelAttributeDescription(char const* lable_name, char const* lable_attribute, char const* attribute_value);
  Json::Value getLabelAttribute(char const* lable_name, char const* lable_attribute);
  Json::Value getLabelAttributeValue(char const* lable_name, char const* lable_attribute, char const* attribute_value);
  //std::string getLabelAttributeValueDescription(char const* lable_name, char const* lable_attribute, char const* attribute_value, );
 private:
  Json::Value* root_= nullptr;
  Json::Reader* reader_ = nullptr;
};

}
#endif //PAPER_ANALYSIS_TRANSLATION_LABEL_H
