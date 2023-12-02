//
// Created by qijiabao on 11/11/2023.
//

#include <map>
#include <string>

#include "error_code.h"
#include <json/value.h>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMNode.hpp>

#ifndef PAPER_ANALYSIS_PARAGRAPH_PROPERTIES_H
#define PAPER_ANALYSIS_PARAGRAPH_PROPERTIES_H

namespace qi {

class CParagraphProperties {
  public:
  CParagraphProperties();
  explicit CParagraphProperties(XERCES_CPP_NAMESPACE::DOMElement *pPr);

  ~CParagraphProperties();


  qierr::error_code setpPr(XERCES_CPP_NAMESPACE::DOMElement *pPr);
  qierr::error_code getpPrMap(XERCES_STD_QUALIFIER map<XERCES_STD_QUALIFIER string, Json::Value> &pPrMap);
  qierr::error_code printPPrMapInfo();

  private:
  XERCES_CPP_NAMESPACE::DOMElement *m_pPr_ = nullptr;
  XERCES_STD_QUALIFIER map<XERCES_STD_QUALIFIER string, Json::Value> m_pPrMap_ = {};

   qierr::error_code nodeTojson(XERCES_CPP_NAMESPACE::DOMNode *node, Json::Value &nodeJson);
   qierr::error_code pPrToMap(XERCES_CPP_NAMESPACE::DOMNode *node, XERCES_STD_QUALIFIER map<XERCES_STD_QUALIFIER string, Json::Value> &pPrMap);
};
}// namespace qi
#endif//PAPER_ANALYSIS_PARAGRAPH_PROPERTIES_H
