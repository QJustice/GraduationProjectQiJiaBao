//
// Created by qijiabao on 2/3/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        FindElements.cpp
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
#include "FindElements.h"

#include <iostream>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMXPathEvaluator.hpp>
#include <xercesc/dom/DOMXPathException.hpp>
#include <xercesc/dom/DOMXPathResult.hpp>

#include "NodeToElement.h"

namespace qi {
FindElements::FindElements()
{
}
FindElements::~FindElements()
{
}
ErrorCode::ErrorCodeEnum FindElements::FindElementByXPath(XERCES_CPP_NAMESPACE::DOMDocument* doc, XERCES_CPP_NAMESPACE::DOMElement* parentElement, const std::string& XPathExpression, XERCES_CPP_NAMESPACE::DOMXPathResult** result)
{
  // 检查父节点是否为空
  if (parentElement == nullptr)
  {
    std::cerr << "父节点为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 检查标签名是否为空
  if (XPathExpression.empty())
  {
    std::cerr << "XPath为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存根节点
  rootElement_ = parentElement;
  // 调用 charToXMLCh 函数将 char* 转换为 XMLCh*
  transString_.charToXMLCh(XPathExpression.c_str(), &XPathExpression_);
  try
  {
    // 你的代码片段
    // 执行 XPath 查询
    *result = doc->evaluate(
            XPathExpression_,                                                // XPath 表达式
            rootElement_,                                                    // 上下文节点
            NULL,                                                            // 命名空间解析器
            XERCES_CPP_NAMESPACE::DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,// 结果类型
            NULL);                                                           // 结果
  } catch (const xercesc_3_2::DOMXPathException& e)                          // 捕获异常
  {
    char* message = nullptr;                             // 异常信息
    transString_.xmlCharToChar(e.getMessage(), &message);// 将 XMLCh* 转换为 char*
    std::cerr << "Caught exception: " << message << std::endl;
  }
  result_ = *result;// 保存结果
  // 检查结果是否为空
  if (result_->getSnapshotLength() == 0)
  {
    //std::cerr << "cannot find point" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取节点数量
  nodeCount_ = result_->getSnapshotLength();
  // 遍历结果
  for (XMLSize_t i = 0; i < nodeCount_; i++)
  {
    // 获取节点
    XERCES_CPP_NAMESPACE::DOMNode* node = result_->getNodeValue();
    // 将节点转换为元素
    XERCES_CPP_NAMESPACE::DOMElement* element = nullptr;
    NodeToElement nodeToElement;
    if (ErrorCode::ErrorCodeEnum::SUCCESS == nodeToElement.nodeToElement(node, &element))
    {
      char* text = nullptr;
      // 调用 xmlCharToChar 函数将 XMLCh* 转换为 char*
      transString_.xmlCharToChar(element->getTagName(), &text);
      //std::cout << "name: " << text << std::endl;
    }
  }

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum FindElements::FindOneElementByID(xercesc_3_2::DOMElement* parentElement, const std::string& targeID, const std::string& id, XERCES_CPP_NAMESPACE::DOMNode** result)
{
  // 检查父节点是否为空
  if (parentElement == nullptr)
  {
    std::cerr << "父节点为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 检查id是否为空
  if (id.empty())
  {
    std::cerr << "id为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 遍历寻找id==id的节点
  for (XERCES_CPP_NAMESPACE::DOMNode* node = parentElement->getFirstChild(); node != nullptr; node = node->getNextSibling())
  {
    XMLCh* targetID = nullptr;
    transString_.charToXMLCh(targeID.c_str(), &targetID);
//    // 打印节点名
//    char* text = nullptr;
//    transString_.xmlCharToChar(node->getNodeName(), &text);
//    std::cout << "name: " << text << std::endl;
    // 遍历node的所有属性
    if (node->getAttributes() == nullptr)
    {
      continue;
    }
    for (XERCES_CPP_NAMESPACE::DOMNode* attr = node->getAttributes()->getNamedItem(targetID); attr != nullptr; attr = attr->getNextSibling())
    {
      // 获取属性值
      char* text = nullptr;
      transString_.xmlCharToChar(attr->getTextContent(), &text);
      // 检查属性值是否等于id
      if (id == text)
      {
          *result = node;
          return ErrorCode::ErrorCodeEnum::SUCCESS;
      }
    }
  }

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi