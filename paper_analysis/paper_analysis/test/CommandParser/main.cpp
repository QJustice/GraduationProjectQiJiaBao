//
// Created by qijiabao on 1/7/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        main.cpp
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        1/7/2024
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

#include <iostream>

#include "CommandParser.h"

int main()
{
  // 创建 CommandParser 对象
  CommandParser commandParser;
  // 测试命令字符串
  std::string commandString = "This is a $space test $line string wit";
  // 解析命令字符串
  std::string result = commandParser.parseCommand(commandString);
  // 输出解析结果
  std::cout << result << std::endl;

  return 0;
}
