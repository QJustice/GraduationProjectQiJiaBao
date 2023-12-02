
#include <string>
#include <thread>
#include <mutex>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMLSParser.hpp>

#include "config.inc"
#include "error_code.h"
#include "translation_label.h"
#include "singal_mutex.h"

#ifndef _ANALYSIS_XML_FILE_H_
#define _ANALYSIS_XML_FILE_H_

namespace qi {

class CAnalysisXMLFile
{

public:
  CAnalysisXMLFile();
  ~CAnalysisXMLFile();

  static qierr::error_code init();
  static qierr::error_code relese();
  qierr::error_code loadXMLFile(char const* file_path);
  qierr::error_code analysisXMLFile(qi::CTranslationLabel* translation_lable);
  qierr::error_code analysisXMLFile(qi::CTranslationLabel* translation_lable, char const* xml_file_path, XERCES_STD_QUALIFIER map<XERCES_STD_QUALIFIER string, XERCES_CPP_NAMESPACE::DOMElement*>* results, XERCES_STD_QUALIFIER mutex* mtx);
  qierr::error_code getDOMElementPtr(XERCES_CPP_NAMESPACE::DOMElement** root);
  qierr::error_code printXMLInfo(XERCES_CPP_NAMESPACE::DOMElement* root, qi::CTranslationLabel* translation_lable);
  qierr::error_code XPathSearch(char const* XPathString);

private:

  XERCES_CPP_NAMESPACE::DOMLSParser* parser_ = nullptr;
  XERCES_CPP_NAMESPACE::ErrorHandler* errHandler_ = nullptr;
  XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc_ = nullptr;
  XERCES_CPP_NAMESPACE::DOMElement* root_ = nullptr;

  qierr::errorcode dfsTraverseXMLTree(XERCES_CPP_NAMESPACE::DOMNode* root, qierr::errorcode(qi::CAnalysisXMLFile::* printNodeFun)(XERCES_CPP_NAMESPACE::DOMNode* node, XERCES_STD_QUALIFIER string& labelPath, qi::CTranslationLabel* translation_lable), qi::CTranslationLabel* translation_lable);
  qierr::error_code parseXMLTree();          // 解析为xml树
  qierr::errorcode printNodeInfo(XERCES_CPP_NAMESPACE::DOMNode* node, std::string& path, qi::CTranslationLabel* translation_lable);
};

}
#endif
