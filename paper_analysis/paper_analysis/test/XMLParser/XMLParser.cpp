//
// Created by qijiabao on 1/7/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        XMLParser.cpp
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
#include "XMLParser.h"

#include <iostream>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/dom/DOMImplementation.hpp>

#define FGDOMNS true

namespace qi {

XMLParser::XMLParser()
{
  try
  {
  // 初始化XML4C2系统
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
  }
  catch (XERCES_CPP_NAMESPACE::XMLException const& toCatch)
  {
    // 处理初始化XML4C2系统时的异常
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "在Xerces-c初始化过程中发生错误。\n"
      << "  异常信息"
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return;
  }

  // 转码"LS"为XMLCh*
  XMLCh* gLS = XERCES_CPP_NAMESPACE::XMLString::transcode("LS");
  // 使用gLS获取DOMImplementationLS
  XERCES_CPP_NAMESPACE::DOMImplementationLS* impl = dynamic_cast<XERCES_CPP_NAMESPACE::DOMImplementationLS*>(XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation(gLS));
  // 释放gLS
  XERCES_CPP_NAMESPACE::XMLString::release(&gLS);
  // 使用impl以MODE_SYNCHRONOUS和NULL选项创建DOMLSParser
  XERCES_CPP_NAMESPACE::DOMLSParser* parser = impl->createLSParser(XERCES_CPP_NAMESPACE::DOMImplementationLS::MODE_SYNCHRONOUS, NULL);
  // 从parser获取DOMConfiguration
  XERCES_CPP_NAMESPACE::DOMConfiguration* config = parser->getDomConfig();
  // 在config中将XMLUni::fgDOMNamespaces参数设置为FGDOMNS
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMNamespaces, FGDOMNS);
  // 在config中启用数据类型规范化
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMDatatypeNormalization, true);
  // 创建ErrorHandler
  XERCES_CPP_NAMESPACE::ErrorHandler* errHandler = new XERCES_CPP_NAMESPACE::HandlerBase();
  // 在config中将XMLUni::fgDOMErrorHandler参数设置为errHandler
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMErrorHandler, errHandler);
  // 重置errHandler的错误计数
  errHandler->resetErrors();

  // 将parser和errHandler分配给相应的类成员
  parser_ = parser;
  errHandler_ = errHandler;
}
XMLParser::~XMLParser()
{
   // 释放解析器
  parser_->release();
  if (errHandler_)
    delete errHandler_;
  // 释放XML4C2系统
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
}
bool XMLParser::loadXMLFile(const char* file_path)
{
  XERCES_CPP_NAMESPACE::DOMDocument* doc = nullptr;
  unsigned long duration = 0;
  try
  {
    // 重置文档池
    parser_->resetDocumentPool();

    // 获取解析开始时间
    unsigned long const startMillis = XERCES_CPP_NAMESPACE::XMLPlatformUtils::getCurrentMillis();
    // 解析指定文件路径的XML文件
    doc = parser_->parseURI(file_path);
    // 获取解析结束时间
    unsigned long const endMillis = XERCES_CPP_NAMESPACE::XMLPlatformUtils::getCurrentMillis();
    // 计算解析耗时
    duration = endMillis - startMillis;
    // 将解析耗时打印到控制台
    XERCES_STD_QUALIFIER cout << "在 " << duration << " 毫秒内解析文件" << XERCES_STD_QUALIFIER endl;

  }
  catch (XERCES_CPP_NAMESPACE::OutOfMemoryException const&)
  {
    XERCES_STD_QUALIFIER cerr << "内存不足异常" << XERCES_STD_QUALIFIER endl;
    return false;
  }
  catch (XERCES_CPP_NAMESPACE::XMLException const& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "解析过程中发生错误\n   错误信息: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return false;
  }
  catch (XERCES_CPP_NAMESPACE::DOMException const& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "解析过程中发生错误\n   错误信息: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return false;
  }
  catch (...)
  {
    XERCES_STD_QUALIFIER cerr << "解析过程中发生错误\n " << XERCES_STD_QUALIFIER endl;
    return false;
  }
  // 将解析得到的文档赋值给类成员
  doc_ = doc;
}
bool XMLParser::getDOMElementPtr(xercesc_3_2::DOMElement** root)
{
  if (root_ == nullptr)
  {
    XERCES_STD_QUALIFIER cerr << "root_ is null" << XERCES_STD_QUALIFIER endl;
    return false;
  }
  *root = root_;
}
bool XMLParser::parseXMLTree()
{
  if (!doc_)
    return false;
  //char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(doc->getElementsByTagName);
  //XERCES_STD_QUALIFIER cout << "Parsed file: " << pMsg << XERCES_STD_QUALIFIER endl;
  //XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);

  // 初始化元素计数器
  size_t elementCount = 0;
  // 获取XML文档的根元素
  root_ = doc_->getDocumentElement();
  if (root_)
    root_->getChildElementCount();
  else
    XERCES_STD_QUALIFIER cerr << "无法找到根元素" << XERCES_STD_QUALIFIER endl;
  // 输出元素数量
  XERCES_STD_QUALIFIER cout << elementCount << " 个元素。" << XERCES_STD_QUALIFIER endl;
  return true;
}
}// namespace qi