#ifndef PAPER_ANALYSIS_TRANSLATION_LABEL_H
#define PAPER_ANALYSIS_TRANSLATION_LABEL_H

#include <string>

#include <json/json.h>

namespace qi {

class CTranslationLabel
{
 public:

  CTranslationLabel();
  ~CTranslationLabel();

  std::string getLabelDescription(char const* lable_name, Json::Value const* node);
  Json::Value getLabelAttribute(char const* lable_name, Json::Value const* node);
  std::string getLabelAttributeValue(char const* lable_name, char const* attribute_value, Json::Value const* node);
 private:
  Json::Value m_root;
  Json::Reader m_reader;
};

}
#endif //PAPER_ANALYSIS_TRANSLATION_LABEL_H
