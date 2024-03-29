//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        StringExtractor.cpp
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
#include "StringExtractor.h"

#include <algorithm>
#include <regex>
#include <string>

qi::StringExtractor::StringExtractor() {}

qi::StringExtractor::~StringExtractor() {}

std::vector<std::string> qi::StringExtractor::extractStrings(const std::string& input)
{
  std::string tempString(input);
  if (clearSpaceAndNewLine_)
  {
    clearSpaceAndNewLine(tempString);
  }
  const std::string& basicString = tempString;
  // 保存所有匹配到的字符串
  std::vector<std::string> result;
  // 搜索起始位置
  std::string::const_iterator stringStart(basicString.cbegin());
  // 结尾{或者是有未必合的{{，则需要特殊处理
  if (leftBraceOne_ && *stringStart == '{' || leftBraceTwo_)
  {
    // 备份搜索起始位置
    std::string::const_iterator tempStart = stringStart;
    // 遍历字符串寻找'}}'
    while (stringStart != basicString.cend())
    {
      // 已开始新的{{匹配，旧的{{匹配不合法，取消标记
      if (*stringStart == '{' && *(stringStart + 1) == '{')
      {
        leftBraceOne_ = false;
        leftBraceTwo_ = false;
        break;
      }
      // 找到匹配项
      if (*stringStart == '}' && *(stringStart + 1) == '}')
      {
        // 删除第一关位置的{不加入字符串合并
        if (leftBraceOne_)
          tempStart++;
        // 合并{{后的字符串和}}前的字符串
        leftBraceAfterString_ += std::string(tempStart, stringStart);
        // 将匹配到的子字符串添加到结果向量中
        result.push_back(leftBraceAfterString_);
        // 已经匹配到结果所有取消标记
        leftBraceOne_ = false;
        leftBraceTwo_ = false;
        // 清除匹配到的子字符串
        leftBraceAfterString_.clear();
        break;
      } else
      {
        // 将搜索位置移到下一个可能的匹配位置
        stringStart++;
      }
    }
  }

  // 已遍历完所有字符串，未找到任何匹配项，没有再继续扫描的意义了，取消标记终止函数
  if (stringStart == basicString.cend())
  {
    // 没有匹配到结果，取消标记
    leftBraceOne_ = false;
    leftBraceTwo_ = false;
    // 清除匹配到的子字符串
    leftBraceAfterString_.clear();
    return result;
  }

  // 使用正则表达式进行匹配{{}}
  std::regex patternAll(R"(\{\{([^}]+)\}\})");
  // 保存匹配结果
  std::smatch match;
  // 搜索起始位置
  std::string::const_iterator searchStart(basicString.cbegin());
  // 在输入字符串中搜索{{}}匹配项
  while (std::regex_search(searchStart, basicString.cend(), match, patternAll))
  {
    // 将匹配到的子字符串添加到结果向量中
    result.push_back(match[1].str());
    // 将搜索位置移到下一个可能的匹配位置
    searchStart = match.suffix().first;
  }
  // 在剩余的字符串中搜索{{匹配项
  std::regex patternLeftTwo(R"(\{\{([^{}]+))");
  while (std::regex_search(searchStart, basicString.cend(), match, patternLeftTwo))
  {
    // 结尾有未闭合的{{
    leftBraceTwo_ = true;
    // 匹配到的子字符串后标记
    leftBraceAfterString_ = match[1].str();
    // 将搜索位置移到下一个可能的匹配位置
    searchStart = match.suffix().first;
  }
  // 在剩余的字符串中搜索{匹配项
  std::regex patternLeftOne(".*\\{$");
  if (std::regex_search(searchStart, basicString.cend(), match, patternLeftOne))
  {
    // 结尾有未闭合的{所以{{匹配项不合法，取消标记
    leftBraceTwo_ = false;
    // 清除匹配到的子字符串
    leftBraceAfterString_.clear();
    // 结尾有未闭合的{
    leftBraceOne_ = true;
  }
  return result;
}
void qi::StringExtractor::clearSpaceAndNewLine(std::string& input)
{
  // 从字符串 input 中删除所有空格和换行符
  // 使用 std::remove_if 结合 std::isspace 函数，将满足条件的字符移动到字符串末尾
  // 然后使用 std::string::erase 函数擦除末尾的这些字符，实现删除操作
  input.erase(
          std::remove_if(input.begin(), input.end(), [](char c) { return std::isspace(c); }),
          input.end());
}
void qi::StringExtractor::setClearSpaceAndNewLine(bool clearSpaceAndNewLine)
{
  clearSpaceAndNewLine_ = clearSpaceAndNewLine;
}
