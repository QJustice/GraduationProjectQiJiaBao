//
// Created by qijiabao on 2/3/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        XMLChToChar.h
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
#ifndef PAPER_ANALYSIS_TRANSSTRING_H
#define PAPER_ANALYSIS_TRANSSTRING_H

#include <vector>
#include <string>

#include <xercesc/util/XMLString.hpp>

#include "ErrorCode.h"

namespace qi {

class TransString {
private:
  // 保存转换后的 XMLCh 字符串, 用于释放内存
  std::vector<XMLCh*> xmlStrings_;
  // 保存转换后的 char 字符串, 用于释放内存
  std::vector<char*> charStrings_;
  // 保存转换后的 std::string 字符串, 用于释放内存
  std::vector<std::string*> strStrings_;
public:
  TransString();
  ~TransString();
  // 将 XMLCh 字符串转换为 char 字符串
  ErrorCode::ErrorCodeEnum xmlCharToChar(const XMLCh* toTranscode, char** charStr);
  // 将XMLCh字符串转换为std::string
  ErrorCode::ErrorCodeEnum xmlCharToString(const XMLCh* toTranscode, std::string** str);
  // 将 char 字符串转换为 XMLCh 字符串
  ErrorCode::ErrorCodeEnum charToXMLCh(const char* toTranscode, XMLCh** xmlStr);
  // // 把XMLSize_t转换为XMLCh
  ErrorCode::ErrorCodeEnum xmlsize_tToXMLCh(const XMLSize_t toTranscode, XMLCh** xmlStr);
  // 数字转字符串
  ErrorCode::ErrorCodeEnum convertToString(int num, std::string& str);
};

}// namespace qi

#endif//PAPER_ANALYSIS_TRANSSTRING_H
