#ifndef PAPER_ANALYSIS_PAPER_ANALYSIS_H
#define PAPER_ANALYSIS_PAPER_ANALYSIS_H

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include "config.inc"
#include "error_code.h"
#include "translation_label.h"

namespace qi {

class CPaperAnalysis
{
 public:
  CPaperAnalysis();
  ~CPaperAnalysis();
  qierr::error_code init();
  qierr::error_code relese();
  qierr::error_code loadXMLFile(char const* file_path);
  qierr::error_code getDomElement(XERCES_CPP_NAMESPACE::DOMElement* root);
  qierr::error_code getBodyElement(XERCES_CPP_NAMESPACE::DOMElement* body);
  qierr::error_code printLableProperties(XERCES_CPP_NAMESPACE::DOMNode* node, qi::CTranslationLabel* translation_lable);
  // qierr::error_code getElementChilds();
  qierr::error_code XPathSearch(char const* XPathString);
 private:
   XERCES_CPP_NAMESPACE::DOMLSParser* parser_ = nullptr;
   XERCES_CPP_NAMESPACE::ErrorHandler* errHandler_ = nullptr;
   XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc_ = nullptr;
   XERCES_CPP_NAMESPACE::DOMElement* root_ = nullptr;
   XERCES_CPP_NAMESPACE::DOMElement* body_ = nullptr;

};

} // namespace qi

#endif //PAPER_ANALYSIS_PAPER_ANALYSIS_H
