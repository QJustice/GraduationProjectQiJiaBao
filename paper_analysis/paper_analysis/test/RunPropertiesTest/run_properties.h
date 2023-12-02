//
// Created by qijiabao on 11/11/2023.
//

#ifndef PAPER_ANALYSIS_RUN_PROPERTIES_H
#define PAPER_ANALYSIS_RUN_PROPERTIES_H

#include <json/json.h>
#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

class CRunProperties {
public:
    CRunProperties();
    ~CRunProperties();

    // 解析 <w:rPr> 标签
    void parseRunProperties(const DOMNode* pNode);

    // 获取运行段属性的 JSON 格式字符串
    std::string toJsonString() const;

private:
    void parseProperty(const DOMNode* propertyNode);

private:
    Json::Value properties_;
};

#endif //PAPER_ANALYSIS_RUN_PROPERTIES_H
