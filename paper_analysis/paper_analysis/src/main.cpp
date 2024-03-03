//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        main.cpp
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

#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "Document.h"
#include "Template.h"
#include "FindElements.h"

int main()
{
  // 初始化 Xerces-C++
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();

#if 1
  {
    qi::Document document;
    document.loadDocument("D:\\WorkSpace\\GraduationProject\\word\\Template01\\word\\document01.xml");
    document.setTemplate("D:\\WorkSpace\\GraduationProject\\GraduationProjectQiJiaBao\\paper_analysis\\paper_analysis\\data\\Template\\Undergraduate\\test01.xml");
    document.setStyle("D:\\WorkSpace\\GraduationProject\\word\\Template01\\word\\styles.xml");
    document.checkDocument();


  }
#endif
#if 0
  {
    qi::Template templatedoc;
    //templatedoc.openTemplateFile("D:\\WorkSpace\\VSCodeFile\\word\\Template02\\word\\document.xml");
  }
#endif
#if 0
  {
    qi::Style style;
    style.loadStyle("D:\\WorkSpace\\VSCodeFile\\word\\Template02\\word\\style01.xml");
    XERCES_CPP_NAMESPACE::DOMElement* defaultStyleElement = nullptr;
    style.defaultStyle(&defaultStyleElement);
    // 打印默认样式
    std::cout << "defaultStyleElement: " << XERCES_CPP_NAMESPACE::XMLString::transcode(defaultStyleElement->getTagName()) << std::endl;
    XERCES_CPP_NAMESPACE::DOMElement* styleElement = nullptr;
    style.findStyleByStyleId("2", &styleElement);
    // 打印样式
    std::cout << "styleElement: " << XERCES_CPP_NAMESPACE::XMLString::transcode(styleElement->getTagName()) << std::endl;
  }
#endif
#if 0
  {
    qi::Template templatedoc;
    templatedoc.openTemplateFile("D:\\WorkSpace\\GraduationProject\\GraduationProjectQiJiaBao\\paper_analysis\\paper_analysis\\data\\Template\\Undergraduate\\test01.xml");
  }
#endif
#if 0
  {
    // 创建 DOM 解析器
    XERCES_CPP_NAMESPACE::XercesDOMParser* parser = new XERCES_CPP_NAMESPACE::XercesDOMParser;
    parser->setValidationScheme(XERCES_CPP_NAMESPACE::XercesDOMParser::Val_Never);
    parser->parse("D:\\WorkSpace\\VSCodeFile\\word\\Template01\\word\\document01.xml"); // 假设存在名为 sample.xml 的 XML 文件

    // 获取 DOM 表示
    XERCES_CPP_NAMESPACE::DOMDocument* doc = parser->getDocument();

    // 获取根元素
    XERCES_CPP_NAMESPACE::DOMElement* root = doc->getDocumentElement();
    std::cout << "Root element tag: " << XERCES_CPP_NAMESPACE::XMLString::transcode(root->getTagName()) << std::endl;
    qi::FindElements findElements;
    XERCES_CPP_NAMESPACE::DOMXPathResult* element = nullptr;
    findElements.FindElementByXPath(doc, root, "./p", &element);
  }

#endif
  // 释放 Xerces-C++
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
  return 0;
}
