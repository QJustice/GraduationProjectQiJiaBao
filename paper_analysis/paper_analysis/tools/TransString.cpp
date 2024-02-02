//
// Created by qijiabao on 2/3/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        XMLChToChar.cpp
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
#include "TransString.h"

namespace qi {
TransString::TransString()
{
}
TransString::~TransString()
{
  // 检测 xmlStrings_ 是否为空，判断是否有未释放内存的 XMLCh 字符串
  if (!xmlStrings_.empty())
  {
    // 循环遍历 xmlStrings_ 并释放内存
    while (xmlStrings_.size() > 0)
    {
      XERCES_CPP_NAMESPACE::XMLString::release(&xmlStrings_.back());
      // 丢弃最后一个元素，因为它已经被释放
      xmlStrings_.pop_back();
    }
  }
  // 检测 charStrings_ 是否为空，判断是否有未释放内存的 char 字符串
  if (!charStrings_.empty())
  {
    // 循环遍历 charStrings_ 并释放内存
    while (charStrings_.size() > 0)
    {
      XERCES_CPP_NAMESPACE::XMLString::release(&charStrings_.back());
      // 丢弃最后一个元素，因为它已经被释放
      charStrings_.pop_back();
    }
  }
}
ErrorCode::ErrorCodeEnum qi::TransString::xmlCharToChar(const XMLCh *toTranscode, char **charStr)
{
  // 调用 transcode 函数将 XMLCh 转换为 string
  char* tempChar = XERCES_CPP_NAMESPACE::XMLString::transcode(toTranscode);
  // 带出转换后的 char 字符串
  *charStr = tempChar;
  // 保存转换后的 char 字符串, 用于释放内存
  charStrings_.push_back(tempChar);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum TransString::charToXMLCh(const char *toTranscode, XMLCh **xmlStr)
{
  // 调用 transcode 函数将 string 转换为 XMLCh
  XMLCh* tempXMLCh = XERCES_CPP_NAMESPACE::XMLString::transcode(toTranscode);
  // 带出转换后的 XMLCh 字符串
  *xmlStr = tempXMLCh;
  // 保存转换后的 XMLCh 字符串, 用于释放内存
  xmlStrings_.push_back(tempXMLCh);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi