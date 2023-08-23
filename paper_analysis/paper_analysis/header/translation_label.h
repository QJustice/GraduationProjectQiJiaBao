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
  CTranslationLabel(char const* file_path);
  ~CTranslationLabel();

  qierr::error_code loadFile(char const* file_path);
  bool belongToMember(char const* member_name, Json::Value* node);
  std::string getLabelDescription(char const* lable_name, char const* lable_sign);
  Json::Value getLabelAttribute(char const* lable_name, char const* lable_sign);
  Json::Value getLabelAttributeValue(char const* lable_name, char const* lable_sign, char const* attribute_value);
 private:
  Json::Value* root_;
  Json::Reader* reader_;
  std::string file_path_;
};

}
#endif //PAPER_ANALYSIS_TRANSLATION_LABEL_H
