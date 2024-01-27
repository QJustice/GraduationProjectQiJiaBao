//
// Created by qijiabao on 1/14/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        XMLParserFactory.cpp
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
#include "XMLParserFactory.h"
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>

namespace qi {
ErrorCode::ErrorCodeEnum XMLParserFactory::createDOMParser(std::string type, xercesc_3_2::DOMLSParser **parser)
{
  if (type == "setting01")
  {
    // 转码 "LS" 字符串为 XMLCh*，XMLCh* 是 Xerces-C++ 中表示 Unicode 字符串的类型
  XMLCh *gLS = XERCES_CPP_NAMESPACE::XMLString::transcode("LS");

  // 通过 DOMImplementationRegistry 获取支持 "Load and Save" 功能的 DOMImplementationLS 实例
  // DOMImplementationRegistry 是 Xerces-C++ 提供的注册表，用于获取 DOMImplementation 实例
  // DOMImplementationLS 是 Xerces-C++ 提供的 DOMImplementation 的子类，支持 "Load and Save" 功能
  // DOMImplementation 是一个更通用的接口，用于创建各种DOM相关对象，而 DOMImplementationLS 则是它的一个具体扩展，增加了与加载和保存XML文档相关的功能。
  XERCES_CPP_NAMESPACE::DOMImplementationLS *impl = XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation(gLS);
  // 使用 DOMImplementationLS 创建 Load and Save 类型的 DOM 解析器 (LSParser)
  // MODE_SYNCHRONOUS 表示创建同步模式的解析器，即解析器会在解析完成前阻塞当前线程
  // 0 表示不使用任何特性，你可以根据需求传递适当的特性参数
  *parser = impl->createLSParser(XERCES_CPP_NAMESPACE::DOMImplementationLS::MODE_SYNCHRONOUS, 0);
  // 释放通过 transcode 分配的 XMLCh* 内存
  // XMLString::release 是 Xerces-C++ 提供的函数，用于释放通过 transcode 或其他相关操作分配的内存
  XERCES_CPP_NAMESPACE::XMLString::release(&gLS);
  // 从 parser 获取 DOMConfiguration
  // DOMConfiguration 接口提供了一种管理和查询 DOM 对象配置的机制。它允许对 DOM 对象的特定功能进行配置，并提供了一种通用的方式来检查和设置这些配置。
  XERCES_CPP_NAMESPACE::DOMConfiguration *config = (*parser)->getDomConfig();
  // 在 config 中将 XMLUni::fgDOMNamespaces 参数设置为 false，表示禁用命名空间支持
  // 命名空间支持用于处理 XML 中的命名空间定义，此处设置为 false 表示不启用命名空间支持
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMNamespaces, false);
  // 在 config 中启用数据类型规范化
  // 数据类型规范化用于将文档中的数据类型转换为规范形式，此处设置为 true 表示启用数据类型规范化
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMDatatypeNormalization, true);
  // 设置解析器验证方案为从不验证 (Val_Never)
  // Val_Never 表示从不进行验证，包括 DTD 和 XML Schema 的验证
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidateIfSchema, false);
  }

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi