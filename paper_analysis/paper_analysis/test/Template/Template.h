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
#include <vector>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMLSParser.hpp>

#include "ErrorCode.h"

namespace qi {

// 模板信息
struct TemplateBlock {
  // 块编号
  int BlockNum = 0;
  // 标记字
  std::string TemplateKey = "null";
  // 标记字格式
  // TODO: 标记字格式
  // 标记字块格式
  // TODO: 标记字块格式
};
// 模板
class Template {
private:
  // 保存模板信息
  std::vector<TemplateBlock> templateBlockVector_;
  // DOM 解析器
  XERCES_CPP_NAMESPACE::DOMLSParser* templateParser_;
  // 模板文档
  XERCES_CPP_NAMESPACE::DOMDocument* template_;

public:
  Template();
  ~Template();
  // get templateblock
  ErrorCode::ErrorCodeEnum getTemplateBlockVector(std::vector<TemplateBlock> templateBlockVector);
  // add templateblock
  bool addTemplateBlock(const TemplateBlock& templateBlock);
  // clear templateblock
  bool clearTemplateBlock();
  // 打开模板文件
  ErrorCode::ErrorCodeEnum openTemplateFile(const std::string& templateFilePath);
};

}// namespace qi

#endif//PAPER_ANALYSIS_TEMPLATE_H
