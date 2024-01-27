//
// Created by qijiabao on 1/14/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        XMLParserFactory.h
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        1/14/2024
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
#ifndef PAPER_ANALYSIS_XMLPARSERFACTORY_H
#define PAPER_ANALYSIS_XMLPARSERFACTORY_H

#include <string>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include "ErrorCode.h"

namespace qi {

class XMLParserFactory {
public:
  // 创建 DOM 解析器
  static ErrorCode::ErrorCodeEnum createDOMParser(std::string type, XERCES_CPP_NAMESPACE::DOMLSParser** parser);
};

}// namespace qi

#endif//PAPER_ANALYSIS_XMLPARSERFACTORY_H