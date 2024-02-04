//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Document.cpp
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        1/6/2024
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

// Additional comments or code go here#include "Document.h"

#include "Document.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>

#include "CommandParser.h"
#include "EraseSpaces.h"
#include "Paragraph.h"
#include "Run.h"
#include "StringExtractor.h"
#include "XMLParserFactory.h"

namespace qi {
Document::Document()
{
  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &documentParser_);
}
Document::Document(const std::string &documentFilePath, const std::string &templateFilePath)
{
  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &documentParser_);
  // 打开文档，确保templateFilePath不为空
  loadDocument(documentFilePath);
}
Document::~Document()
{
  // 释放解析器
  documentParser_->release();
}
// 打开文档
ErrorCode::ErrorCodeEnum Document::loadDocument(const std::string &documentFilePath)
{
  // 检查文档路径是否为空
  if (documentFilePath.empty())
  {
    std::cerr << "Document path is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存文档路径
  documentPath_ = documentFilePath;
  // 保存文档名称
  documentName_ = documentFilePath.substr(documentFilePath.find_last_of('/') + 1);
  // 解析 XML 文件并获取文档
  document_ = documentParser_->parseURI(documentFilePath.c_str());
  // 检查文档是否为空
  if (document_ == nullptr)
  {
    std::cerr << "Document is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 获取文档的所有<w:p>标签
  paragraphs_.paragraphsParser(document_);


  return qi::ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Document::setTemplate(const std::string &templateFilePath)
{
  // 检查模板路径是否为空
  if (templateFilePath.empty())
  {
    std::cerr << "Template path is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 打开模板
  documentTemplate_.openTemplateFile(templateFilePath);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}

ErrorCode::ErrorCodeEnum Document::setStyle(const std::string &styleFilePath)
{
  // 检查样式路径是否为空
  if (styleFilePath.empty())
  {
    std::cerr << "Style path is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  styleFilePath_ = styleFilePath;
  // 设置样式文件
  documentTemplate_.setStyleFile(styleFilePath_);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}


ErrorCode::ErrorCodeEnum Document::checkDocument()
{
  // 清除所有空格
  EraseSpaces eraseSpaces;
  // 获取段落数量
  XMLSize_t paragraphCount = 0;
  paragraphs_.getParagraphCount(&paragraphCount);
  // 标记是否检测
  bool isCheck = false;
  // 打印出所有段落中的文本
  for (XMLSize_t i = 0; i < paragraphCount; ++i)
  {
    // 保存获取的文本
    std::string text;
    paragraphs_.getParagraphText(text);
    // 清除空格
    eraseSpaces.eraseSpaces(text);
    // 清除换行符
    eraseSpaces.eraseNewLine(text);
    if (text.empty())
    {
      paragraphs_.nextParagraph();
      continue;
    }
    //std::cout << "Paragraph: " << text << std::endl;
    // 解析段落中的run
    Run runs(&paragraphs_, document_);
    XMLSize_t runCount = 0;                      // 段落中的run数量
    runs.getRunCount(&runCount);                 // 获取run数量
    XERCES_CPP_NAMESPACE::DOMNode *run = nullptr;// run 节点
    for (XMLSize_t j = 0; j < runCount; ++j)
    {
      // 获取run节点
      runs.getRun(&run);
      // 获取run文本
      runs.getRunText(&text);
      // 使用标准库的算法和迭代器去除空白字符
      eraseSpaces.eraseSpaces(text);
      // 清除换行符
      eraseSpaces.eraseNewLine(text);
      XMLSize_t *index = nullptr;
      documentTemplate_.findKeyword(text, &index);
      if (index != nullptr)
      {
        isCheck = true;
        std::cout << "Keyword: " << text << " Index: " << *index << std::endl;
      }
      if (isCheck)
      {
        XERCES_CPP_NAMESPACE::DOMNode *paragraph = nullptr;
        paragraphs_.getParagraph(&paragraph);
        documentTemplate_.checkRun(run, text, paragraph);
      }
      runs.getNextRun(&run);
    }
    paragraphs_.nextParagraph();
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}

}// namespace qi