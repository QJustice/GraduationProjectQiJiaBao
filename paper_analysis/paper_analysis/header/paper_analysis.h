#ifndef PAPER_ANALYSIS_PAPER_ANALYSIS_H
#define PAPER_ANALYSIS_PAPER_ANALYSIS_H

#include "config.inc"
#include "error_code.h"
#include "translation_label.h"
#include <string>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMLSParser.hpp>

namespace qi {


class CPaperAnalysis
{
 public:
  CPaperAnalysis();
  ~CPaperAnalysis();
  qierr::error_code init();
  qierr::error_code relese();
  qierr::error_code loadXMLFile(char const* file_path);
  qierr::error_code analysisXMLFile(qi::CTranslationLabel* translation_lable);
  //qierr::errorcode  printNodeInfo(XERCES_CPP_NAMESPACE::DOMNode* node);
  
  //qierr::error_code getDomElement();
  //qierr::error_code getBodyElement();
  qierr::error_code printLableProperties(XERCES_CPP_NAMESPACE::DOMNode* node, qi::CTranslationLabel* translation_lable);
  qierr::errorcode printNodeInfo(XERCES_CPP_NAMESPACE::DOMNode* node,  std::string& path, qi::CTranslationLabel* translation_lable);
  // qierr::error_code getElementChilds();
  qierr::error_code XPathSearch(char const* XPathString);


 private:
   XERCES_CPP_NAMESPACE::DOMLSParser* parser_ = nullptr;
   XERCES_CPP_NAMESPACE::ErrorHandler* errHandler_ = nullptr;
   XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc_ = nullptr;
   XERCES_CPP_NAMESPACE::DOMElement* root_ = nullptr;
   XERCES_CPP_NAMESPACE::DOMElement* body_ = nullptr;

   //qierr::errorcode  dfsTraverseXMLTree(XERCES_CPP_NAMESPACE::DOMNode* root, qierr::errorcode(qi::CPaperAnalysis::*printNodeFun)(XERCES_CPP_NAMESPACE::DOMNode* node));
   qierr::errorcode dfsTraverseXMLTree(XERCES_CPP_NAMESPACE::DOMNode* root, qierr::errorcode(qi::CPaperAnalysis::* printNodeFun)(XERCES_CPP_NAMESPACE::DOMNode* node, XERCES_STD_QUALIFIER string& labelPath, qi::CTranslationLabel* translation_lable), qi::CTranslationLabel* translation_lable);
};

} // namespace qi

#endif //PAPER_ANALYSIS_PAPER_ANALYSIS_H
