// CParagraphProperties.cpp
// Created by qijiabao on 11/11/2023.
#include "paragraph_properties.h"

qi::CParagraphProperties::CParagraphProperties() = default;

qi::CParagraphProperties::~CParagraphProperties() = default;

qi::CParagraphProperties::CParagraphProperties(XERCES_CPP_NAMESPACE::DOMElement *pPr) : m_pPr_(pPr)
{
}
qierr::error_code qi::CParagraphProperties::setpPr(xercesc_3_2::DOMElement *pPr)
{
  this->m_pPr_ = pPr;
  return 0;
}
qierr::error_code qi::CParagraphProperties::getpPrMap(std::map<std::string, Json::Value> &pPrMap)
{
  if (this->m_pPr_ == nullptr)
    return qierr::E_EMPTY;
  this->pPrToMap(this->m_pPr_, this->m_pPrMap_);
    pPrMap = this->m_pPrMap_;
  return qierr::E_OK;
}
qierr::error_code qi::CParagraphProperties::pPrToMap(xercesc_3_2::DOMNode *node, std::map<std::string, Json::Value> &pPrMap)
{
    if (node == nullptr)
        return qierr::E_EMPTY;
    Json::Value nodeJson;
    this->nodeTojson(node, nodeJson);
    pPrMap[node->getNodeName()] = nodeJson;
    xercesc_3_2::DOMNode *child = node->getFirstChild();
    while (child != nullptr) {
        this->pPrToMap(child, pPrMap);
        child = child->getNextSibling();
    }
    return qierr::E_OK;
}
