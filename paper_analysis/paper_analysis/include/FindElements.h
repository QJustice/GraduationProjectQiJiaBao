//
// Created by qijiabao on 2/3/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        FindElements.h
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        2/3/2024
 * @Description: 
 *               This file is generated by CLion to provide a
 *               template for C/C++ source or header files. You can modify
 *               this template according to your project's needs.
 * @Note:        Additional notes or important points related to the file.
 * @License:     License information if applicable.
 * @Version:     Version number or other version information.
 * @TODO:        List of tasks or things to be done in the file (if any).
 * @Bug:         List of known issues or bugs (if any).
 * @IDE:         CLion
 ************************************************************************/
// Include necessary headers, if any

// Additional comments or code go here
#ifndef PAPER_ANALYSIS_FINDELEMENTS_H
#define PAPER_ANALYSIS_FINDELEMENTS_H

#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMXPathEvaluator.hpp>
#include <xercesc/dom/DOMXPathResult.hpp>

#include "ErrorCode.h"
#include "TransString.h"

namespace qi {

class FindElements {
private:
  // 根节点
  XERCES_CPP_NAMESPACE::DOMElement* rootElement_;
  // XPat 结果保存到列表
  XERCES_CPP_NAMESPACE::DOMNodeList* resultList_;
  // XPath 结果
  XERCES_CPP_NAMESPACE::DOMXPathResult* result_;
  // 找到的节点数量
  XMLSize_t nodeCount_;
  // XPath 表达式
  XMLCh* XPathExpression_ = nullptr;
  // XPath 解析器
  XERCES_CPP_NAMESPACE::DOMXPathEvaluator* evaluator_;
  // 字符串转换工具
  TransString transString_;


public:
  FindElements();
  ~FindElements();
  // XPath搜索Element
  ErrorCode::ErrorCodeEnum FindElementByXPath(XERCES_CPP_NAMESPACE::DOMDocument* doc,
                                              XERCES_CPP_NAMESPACE::DOMElement* parentElement,
                                              const std::string& XPathExpression,
                                              XERCES_CPP_NAMESPACE::DOMXPathResult** result);
  // ID 搜索 Element
  ErrorCode::ErrorCodeEnum FindOneElementByID(XERCES_CPP_NAMESPACE::DOMElement* parentElement,
                                              const std::string& targeID,
                                              const std::string& id,
                                              XERCES_CPP_NAMESPACE::DOMNode** result);
};

}// namespace qi

#endif//PAPER_ANALYSIS_FINDELEMENTS_H