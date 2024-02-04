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
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/util/XMLString.hpp>

#include "FindElements.h"
#include "NodeToElement.h"

namespace qi {
Run::Run()
{
}
Run::Run(Paragraph* paragraph, XERCES_CPP_NAMESPACE::DOMDocument* doc)
{
  // 获取段落的所有<w:r>标签
  runsParser(paragraph, doc);
  // 保存文档
  doc_ = doc;
}
ErrorCode::ErrorCodeEnum Run::runsParser(Paragraph* paragraph, XERCES_CPP_NAMESPACE::DOMDocument* doc)
{
  if (doc == nullptr)
  {
    std::cerr << "文档为空" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存文档
  doc_ = doc;
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
  // 将 tempParagraph 转换为 DOMElement
  XERCES_CPP_NAMESPACE::DOMElement* convertedElement = nullptr;
  // NodeToElement 对象是用来将 DOMNode 转换为 DOMElement的工具类
  NodeToElement nodeToElement;
  // FindElements 对象是用来查找 XML 元素的工具类
  FindElements findElements;
  if (ErrorCode::ErrorCodeEnum::SUCCESS == nodeToElement.nodeToElement(tempParagraph, &convertedElement))
  {
    // 获取段落的所有<w:r>标签
    // runList_ = convertedElement->getElementsByTagName(xmlString);
    findElements.FindElementByXPath(doc_, convertedElement, "./r", &runListXPath_);

  } else
  {
    std::cerr << "段落类型错误" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取运行块数量
  //runCount_ = runList_->getLength();
  runCount_ = runListXPath_->getSnapshotLength();
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
ErrorCode::ErrorCodeEnum Run::getRun(XERCES_CPP_NAMESPACE::DOMNode** run) const
{
  // 获取当前运行块
  // *run = runList_->item(runIndex_);
  runListXPath_->snapshotItem(runIndex_);
  *run = runListXPath_->getNodeValue();
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Run::getNextRun(XERCES_CPP_NAMESPACE::DOMNode** run)
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
ErrorCode::ErrorCodeEnum Run::getPreviousRun(XERCES_CPP_NAMESPACE::DOMNode** run)
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
ErrorCode::ErrorCodeEnum Run::getRunText(std::string* text)
{
  // 临时保存运行块
  XERCES_CPP_NAMESPACE::DOMNode* tempRun = nullptr;
  // 获取当前运行块
  getRun(&tempRun);
  // 检查运行块是否为空
  if (tempRun == nullptr)
  {
    std::cerr << "run is empty" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取运行块的Text
  // 将 XMLCh* 转换为 char*
  char* charString = nullptr;
  transString_.xmlCharToChar(tempRun->getTextContent(), &charString);
  // 保存运行块的Text
  *text = charString;

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi