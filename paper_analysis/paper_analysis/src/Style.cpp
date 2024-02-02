//
// Created by qijiabao on 2/1/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Style.cpp
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        2/1/2024
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
#include "Style.h"

#include <iostream>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>

#include "XMLParserFactory.h"
#include "NodeToElement.h"

namespace qi {
Style::Style()
{
  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &styleParser_);
}
ErrorCode::ErrorCodeEnum Style::loadStyle(const std::string &stylePath)
{
  // 检测样式路径是否为空
  if (stylePath.empty())
  {
    std::cerr << "Document path is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存样式路径
  stylePath_ = stylePath;
  // 加载样式
  style_ = styleParser_->parseURI(stylePath.c_str());
  // 检测样式是否为空
  if (style_ == nullptr)
  {
    std::cerr << "Style is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
Style::Style(const std::string &stylePath)
{
  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &styleParser_);
  // 加载样式
  loadStyle(stylePath);
}
ErrorCode::ErrorCodeEnum Style::defaultStyle(xercesc_3_2::DOMElement **styleElement)
{
  // 检测样式元素是否为空
  if (styleElement == nullptr)
  {
    std::cerr << "Style element is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 调用 transcode 函数将 string 转换为 XMLCh
  XMLCh *xmlString = XERCES_CPP_NAMESPACE::XMLString::transcode("w:docDefaults");
  // 获取默认样式
  XERCES_CPP_NAMESPACE::DOMNodeList *defaultStyleElements = style_->getElementsByTagName(xmlString);
  // 释放内存
  XERCES_CPP_NAMESPACE::XMLString::release(&xmlString);
  // 检测默认样式元素是否为空
  if (defaultStyleElements->getLength() == 0)
  {
    std::cerr << "Default style element is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 默认样式元素有且只能有一个，如果多于一个则报错
  if (defaultStyleElements->getLength() > 1)
  {
    std::cerr << "More than one default style element!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存转换后的样式元素
  XERCES_CPP_NAMESPACE::DOMElement *tempElement = nullptr;
  NodeToElement nodeToElement;
  if (ErrorCode::ErrorCodeEnum::SUCCESS == nodeToElement.nodeToElement(defaultStyleElements->item(0), &tempElement))
  {
    // 保存样式元素
    *styleElement = tempElement;
  } else
  {
    std::cerr << "Failed to convert node to element!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Style::findStyleByStyleId(const std::string &styleId, xercesc_3_2::DOMElement **styleElement)
{
  // 检测样式 ID 是否为空
  if (styleId.empty())
  {
    std::cerr << "Style ID is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // NodeToElement 对象是用来将 DOMNode 转换为 DOMElement的工具类
  NodeToElement nodeToElement;
  // 临时保存样式元素
  XERCES_CPP_NAMESPACE::DOMElement *tempElement = nullptr;
  // 遍历xml根据styleId查找样式
  // 获取所有样式
  XERCES_CPP_NAMESPACE::DOMNodeList *styleElements = style_->getElementsByTagName(XERCES_CPP_NAMESPACE::XMLString::transcode("w:style"));
  // 遍历样式
  for (XMLSize_t i = 0; i < styleElements->getLength(); ++i)
  {
    // 获取样式
    nodeToElement.nodeToElement(styleElements->item(i), &tempElement);
    // 获取样式ID
    const XMLCh *xmlString = tempElement->getAttribute(XERCES_CPP_NAMESPACE::XMLString::transcode("w:styleId"));
    // 将 XMLCh 转换为 string
    std::string tempStyleId = XERCES_CPP_NAMESPACE::XMLString::transcode(xmlString);
    // 检测样式ID是否匹配
    if (tempStyleId == styleId)
    {
      // 保存样式元素
      *styleElement = tempElement;
      return ErrorCode::ErrorCodeEnum::SUCCESS;
    }
  }
  return ErrorCode::ErrorCodeEnum::FAILED;
}
}// namespace qi