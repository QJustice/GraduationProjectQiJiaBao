//
// Created by qijiabao on 11/11/2023.
//

#include "run_properties.h"
#include <xercesc/util/XMLString.hpp>

CRunProperties::CRunProperties() {}

CRunProperties::~CRunProperties() {}

void CRunProperties::parseRunProperties(const DOMNode* pNode) {
    if (!pNode)
        return;

    DOMNodeList* children = pNode->getChildNodes();
    const XMLSize_t childCount = children->getLength();

    for (XMLSize_t i = 0; i < childCount; ++i) {
        DOMNode* childNode = children->item(i);
        if (childNode->getNodeType() == DOMNode::ELEMENT_NODE) {
            parseProperty(childNode);
        }
    }
}

std::string CRunProperties::toJsonString() const {
    return properties_.toStyledString();
}

void CRunProperties::parseProperty(const DOMNode* propertyNode) {
    char* propertyName = XMLString::transcode(propertyNode->getNodeName());
    char* propertyValue = XMLString::transcode(propertyNode->getTextContent());

    // 示例属性：根据实际情况添加或修改属性
    // 这里使用子标签的名字作为 JSON key，子标签的文本内容作为 JSON value
    properties_[propertyName] = propertyValue;

    XMLString::release(&propertyName);
    XMLString::release(&propertyValue);
}
