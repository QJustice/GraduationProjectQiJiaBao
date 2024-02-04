//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Template.h
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

// Additional comments or code go here

#ifndef PAPER_ANALYSIS_TEMPLATE_H
#define PAPER_ANALYSIS_TEMPLATE_H

#include <string>
#include <map>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMLSParser.hpp>

#include "ErrorCode.h"
#include "DOMElementComparator.h"
#include "TransString.h"
#include "Run.h"

namespace qi {

// 模板
class Template {
private:
  // DOM 解析器
  XERCES_CPP_NAMESPACE::DOMLSParser* templateParser_;
  // 模板文档
  XERCES_CPP_NAMESPACE::DOMDocument* template_;
  // 模板文件路径
  std::string templateFilePath_;
  // 模板名称
  std::string templateName_;
  // 关键字数量
  XMLSize_t keywordCount_;
  // 字符串转换工具
  TransString transString_;
  // 模板关键字, 关键字索引
  std::map<const std::string , XMLSize_t> keywords_;

public:
  Template();
  Template(const std::string& templateFilePath);
  ~Template();

  // 打开模板文件
  ErrorCode::ErrorCodeEnum openTemplateFile(const std::string& templateFilePath);
  // 解析模板文件
  ErrorCode::ErrorCodeEnum parseTemplateFile();
  // Find the keyword in the template
  ErrorCode::ErrorCodeEnum findKeyword(const std::string keyword, XMLSize_t** index);
  // 获取rPr样式
  ErrorCode::ErrorCodeEnum getRunStyle(const XERCES_CPP_NAMESPACE::DOMNode* run,XERCES_CPP_NAMESPACE::DOMNode** rpr);
  // 获取pPr样式
  ErrorCode::ErrorCodeEnum getParagraphStyle(const XERCES_CPP_NAMESPACE::DOMNode* paragraph,XERCES_CPP_NAMESPACE::DOMNode** ppr);
  // 检测目标run是否符合模板格式
  ErrorCode::ErrorCodeEnum checkRun(const XERCES_CPP_NAMESPACE::DOMNode * run, const std::string keyword, const XERCES_CPP_NAMESPACE::DOMNode* paragraphs);
  // 根据关键字获取模板样式
  ErrorCode::ErrorCodeEnum getStyleFromKey(const std::string keyword, XERCES_CPP_NAMESPACE::DOMNode** style);
};

}// namespace qi

#endif//PAPER_ANALYSIS_TEMPLATE_H
