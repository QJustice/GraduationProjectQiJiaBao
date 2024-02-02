//
// Created by qijiabao on 2/2/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        NodeToElement.cpp
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        2/2/2024
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
#include "NodeToElement.h"

#include <iostream>
#include <xercesc/util/XMLString.hpp>

namespace qi {
ErrorCode::ErrorCodeEnum NodeToElement::nodeToElement(xercesc_3_2::DOMNode *node, xercesc_3_2::DOMElement **element)
{
  XERCES_CPP_NAMESPACE::DOMElement *convertedElement = nullptr;
  // 检测节点是否为空
  if (node == nullptr)
  {
    std::cerr << "Node is empty!" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  if (node->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
  {
    // 将 DOMNode 转换为 DOMElement
    // 在Xerces-C++中，DOMElement是DOM节点的一种，它表示XML文档中的元素, DOMElement继承自DOMNode
    // 有些DOM节点是DOMElement，但不是所有的DOM节点都是DOMElement，所以先要判断节点类型再转换避免出错
    // 因为有些方法返回的是 DOMNodeList，其中的节点类型可能是 DOMElement，也可能是其他类型的节点
    // A new DOMNodeList object containing all the matched DOMElement(s).(Xerces-C++ API Document for  DOMDocument Class -> getElementsByTagName())
    // 使用 dynamic_cast 进行向下转型，以确保 paragraphNode 实际上是 DOMElement 类型的节点
    convertedElement = dynamic_cast<XERCES_CPP_NAMESPACE::DOMElement *>(node);
  } else
  {
    std::cerr << "类型错误" << std::endl;
    return ErrorCode::ErrorCodeEnum::FAILED;
  }
  *element = convertedElement;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
}// namespace qi