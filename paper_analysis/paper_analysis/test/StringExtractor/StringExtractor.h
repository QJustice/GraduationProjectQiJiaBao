//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        StringExtractor.h
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
#ifndef PAPER_ANALYSIS_STRINGEXTRACTOR_H
#define PAPER_ANALYSIS_STRINGEXTRACTOR_H


#include <string>
#include <vector>

class StringExtractor {
private:
  // 存储上一次提取的字符串结尾两个字符
public:
    StringExtractor();
    ~StringExtractor();

    std::vector<std::string> extractStrings(const std::string& input);

private:
    // 你可以在这里添加其他私有成员或方法，如果需要的话
};


#endif//PAPER_ANALYSIS_STRINGEXTRACTOR_H
