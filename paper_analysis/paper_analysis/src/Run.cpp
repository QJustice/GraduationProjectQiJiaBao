//
// Created by qijiabao on 2/1/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Run.cpp
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
#include "Run.h"

#include <iostream>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>

namespace qi {
Run::Run()
{
}
Run::Run(Paragraph* paragraph)
{
  // 获取段落的所有<w:r>标签
  runsParser(paragraph);
}
ErrorCode::ErrorCodeEnum Run::runsParser(Paragraph* paragraph)
{
  // 检查段落是否为空
  if (paragraph == nullptr)
  {
    std::cerr << "运行块为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存运行块
  paragraph_ = paragraph;
  // 临时保存运行块
  XERCES_CPP_NAMESPACE::DOMNode* tempParagraph = nullptr;
  // 当前运行块
  paragraph_->getParagraph(&tempParagraph);
  if (tempParagraph == nullptr)
  {
    std::cerr << "段落为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  if (tempParagraph->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
  {
    // 将 tempParagraph 转换为 DOMElement
    // 在Xerces-C++中，DOMElement是DOM节点的一种，它表示XML文档中的元素, DOMElement继承自DOMNode
    // 有些DOM节点是DOMElement，但不是所有的DOM节点都是DOMElement，所以先要判断节点类型再转换避免出错
    XERCES_CPP_NAMESPACE::DOMElement* convertedElement = dynamic_cast<XERCES_CPP_NAMESPACE::DOMElement*>(tempParagraph);
    // 调用 transcode 函数将 string 转换为 XMLCh
    XMLCh* xmlString = XERCES_CPP_NAMESPACE::XMLString::transcode("w:r");
    // 获取段落的所有<w:r>标签
    runList_ = convertedElement->getElementsByTagName(xmlString);
    // 释放内存
    XERCES_CPP_NAMESPACE::XMLString::release(&xmlString);
  } else
  {
    std::cerr << "段落类型错误" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取运行块数量
  runCount_ = runList_->getLength();
  // 重置运行块索引
  resetRunIndex();
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getRunCount(XMLSize_t* count) const
{
  // 获取运行块数量
  *count = runCount_;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getRunIndex(int* index) const
{
  // 获取当前运行块索引
  *index = runIndex_;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getRun(xercesc_3_2::DOMNode** run) const
{
  // 获取当前运行块
  *run = runList_->item(runIndex_);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getNextRun(xercesc_3_2::DOMNode** run)
{
  // 检查运行块索引是否超出范围
  if (runIndex_ >= runCount_)
  {
    std::cerr << "运行块索引超出范围" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 运行块索引加一
  ++runIndex_;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getPreviousRun(xercesc_3_2::DOMNode** run)
{
  // 检查运行块索引是否超出范围
  if (runIndex_ < 0)
  {
    std::cerr << "运行块索引超出范围" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 运行块索引减一
  --runIndex_;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::resetRunIndex()
{
  // 重置运行块索引
  runIndex_ = 0;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getRunText(std::string* text) const
{
  // 临时保存运行块
  XERCES_CPP_NAMESPACE::DOMNode* tempRun = nullptr;
  // 获取当前运行块
  getRun(&tempRun);
  // 检查运行块是否为空
  if (tempRun == nullptr)
  {
    std::cerr << "运行块为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取运行块的Text
  // 将 XMLCh* 转换为 char*
  char* charString = XERCES_CPP_NAMESPACE::XMLString::transcode(tempRun->getTextContent());
  // 保存运行块的Text
  *text = charString;
  // 释放内存
  XERCES_CPP_NAMESPACE::XMLString::release(&charString);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getRunProperties(xercesc_3_2::DOMNode** runProperties) const
{
  // 临时保存运行块
  XERCES_CPP_NAMESPACE::DOMNode* tempRun = nullptr;
  // 获取当前运行块
  getRun(&tempRun);
  // 检查运行块是否为空
  if (tempRun == nullptr)
  {
    std::cerr << "运行块为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取段落的<w:rPr>标签, 该标签包含段落的属性,<w:rPr>标签是<w:r>标签的第一个子标签
  *runProperties = tempRun->getFirstChild();
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi