//
// Created by qijiabao on 2/1/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Style.h
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
#ifndef PAPER_ANALYSIS_STYLE_H
#define PAPER_ANALYSIS_STYLE_H

#include <string>

#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMLSParser.hpp>

#include "ErrorCode.h"

namespace qi {

class Style {
private:
  // DOM 解析器
  XERCES_CPP_NAMESPACE::DOMLSParser* styleParser_;
  // 样式
  XERCES_CPP_NAMESPACE::DOMDocument* style_;
  // 样式路径
  std::string stylePath_;
public:
  Style();
  Style(const std::string& stylePath);
  ~Style() = default;
  // 加载样式
  ErrorCode::ErrorCodeEnum loadStyle(const std::string& stylePath);
  // 获取默认样式
  ErrorCode::ErrorCodeEnum defaultStyle(XERCES_CPP_NAMESPACE::DOMElement** styleElement);
  // 通过样式 ID 查找样式
  ErrorCode::ErrorCodeEnum findStyleByStyleId(const std::string& styleId, XERCES_CPP_NAMESPACE::DOMElement** styleElement);
};

}// namespace qi

#endif//PAPER_ANALYSIS_STYLE_H
