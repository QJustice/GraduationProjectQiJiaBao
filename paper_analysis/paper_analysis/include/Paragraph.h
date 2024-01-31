//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        main.cpp
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

// Add

#ifndef PAPER_ANALYSIS_Paragraph_H
#define PAPER_ANALYSIS_Paragraph_H

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNode.hpp>

#include "ErrorCode.h"

namespace qi {

/*
 * 获取文档的所有<w:p>标签
 *
 */

class Paragraph {
private:
  // 文档
  XERCES_CPP_NAMESPACE::DOMDocument* document_ = nullptr;
  // <w:p> list
  XERCES_CPP_NAMESPACE::DOMNodeList* paragraphList_ = nullptr;
  // 段落索引
  int paragraphIndex_ = 0;
  // 段落数量
  XMLSize_t paragraphCount_ = 0;

public:
  Paragraph();
  explicit Paragraph(XERCES_CPP_NAMESPACE::DOMDocument* document);
  ~Paragraph() = default;
  // 获取文档的所有<w:p>标签
  ErrorCode::ErrorCodeEnum paragraphsParser(XERCES_CPP_NAMESPACE::DOMDocument* document);
  // 获取段落数量
  ErrorCode::ErrorCodeEnum getParagraphCount(XMLSize_t* count) const;
  // 获取当前遍历的段落索引
  ErrorCode::ErrorCodeEnum getParagraphIndex(XMLSize_t* index) const;
  // 获取当前遍历的段落
  ErrorCode::ErrorCodeEnum getParagraph(XERCES_CPP_NAMESPACE::DOMNode** paragraph) const;
  // 获取下一个段落
  ErrorCode::ErrorCodeEnum nextParagraph();
  // 获取上一个段落
  ErrorCode::ErrorCodeEnum previousParagraph();
  // 重置段落索引
  ErrorCode::ErrorCodeEnum resetParagraphIndex();
  // 获取段落的<w:pPr>标签
  ErrorCode::ErrorCodeEnum getParagraphProperty(XERCES_CPP_NAMESPACE::DOMNode** paragraphProperty) const;
};

}// namespace qi

#endif//PAPER_ANALYSIS_Paragraph_H
