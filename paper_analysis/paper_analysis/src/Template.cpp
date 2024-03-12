//
// Created by qijiabao on 1/6/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        Template.cpp
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

// Additional comments or code go here#include "Template.h"

#include "Template.h"

#include <iostream>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>

#include "CommandParser.h"
#include "EraseSpaces.h"
#include "FindElements.h"
#include "NodeToElement.h"
#include "StringExtractor.h"
#include "XMLParserFactory.h"
#include "XMLPrinter.h"

namespace qi {
Template::Template()
{
  // 初始化模板关键字
  //  keywords_ =
  //          {
  //                  {"本科毕业论文（设计", 0},
  //                  {"毕业论文原创性声明", 1},
  //                  {"目录", 2},
  //                  {"摘要", 3},
  //                  {"关键字", 4},
  //                  {"Abstract", 5},
  //                  {"Keywords", 6},
  //                  {"致谢", 7},
  //                  {"参考文献", 8}};

  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &templateParser_);
}
Template::Template(const std::string &templateFilePath)
{
  // 创建 XMLParserFactory 对象并构建 DOM 解析器
  XMLParserFactory::createDOMParser("setting01", &templateParser_);
  // 打开模板
  openTemplateFile(templateFilePath);
}
Template::~Template()
{
}
ErrorCode::ErrorCodeEnum Template::openTemplateFile(const std::string &templateFilePath)
{
  // 检查模板路径是否为空
  if (templateFilePath.empty())
  {
    std::cerr << "Template path is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 保存模板路径
  templateFilePath_ = templateFilePath;
  // 保存模板名称
  templateName_ = templateFilePath.substr(templateFilePath.find_last_of('/') + 1);
  // 解析 XML 文件并获取文档
  template_ = templateParser_->parseURI(templateFilePath.c_str());
  // 检查模板是否为空
  if (template_ == nullptr)
  {
    std::cerr << "Template is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  parseTemplateFile();
  return qi::ErrorCode::ErrorCodeEnum::SUCCESS;
}

ErrorCode::ErrorCodeEnum Template::setStyleFile(const std::string &styleFilePath)
{
  if (styleFilePath.empty())
  {
    std::cerr << "Template path is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  style_.loadStyle(styleFilePath);
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}

ErrorCode::ErrorCodeEnum Template::parseTemplateFile()
{
  // 检查模板是否为空
  if (template_ == nullptr)
  {
    std::cerr << "Template is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 关键字数量
  keywordCount_ = 0;
  // 获取模板的根节点的孩子节点，模板的根节点是<Template>
  XERCES_CPP_NAMESPACE::DOMElement *root = template_->getDocumentElement();
  XMLCh *tagName = nullptr;
  transString_.charToXMLCh("name", &tagName);
  // 获取所有的name标签
  XERCES_CPP_NAMESPACE::DOMNodeList *tagNames = root->getElementsByTagName(tagName);
  // 获取name标签的数量等同于关键字的数量
  keywordCount_ = tagNames->getLength();
  // 遍历tagNames获取关键字
  for (XMLSize_t i = 0; i < tagNames->getLength(); ++i)
  {
    // 获取name标签
    XERCES_CPP_NAMESPACE::DOMNode *name = tagNames->item(i);
    // 获取name标签的文本内容
    std::string *text = nullptr;
    transString_.xmlCharToString(name->getTextContent(), &text);
    // 清除空格工具
    EraseSpaces eraseSpaces;
    // 清除空格
    eraseSpaces.eraseSpaces(*text);
    // 清除换行
    eraseSpaces.eraseNewLine(*text);
    // 保存关键字
    keywords_.push_back(std::make_pair(*text, name));
  }
  // 重置索引,不然keyIndex_会是一个乱码
  resetStyle();
  //打印关键字
  //    for (auto &keyword: keywords_)
  //
  //      std::cout << "Keywordxxx: " << keyword.first << " Index: " << keyword.second << std::endl;
  //
  // 获取所有的div标签

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::findKeyword(const std::string keyword, int &index)
{
  // 检查关键字是否为空
  if (keyword.empty())
  {
    //std::cerr << "Keyword is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 遍历vector 找到符合关键字的索引
  for (XMLSize_t i = 0; i < keywords_.size(); i++)
  {
    // vector 结构是关键字和关键字的节点指针，所以要获取关键字的话就要用first
    if (keywords_[i].first == keyword)
    {
      // 找到关键字
      index = i;
      return qi::ErrorCode::ErrorCodeEnum::SUCCESS;
    }
  }
  // 没有找到关键字
  index = -1;
  return qi::ErrorCode::ErrorCodeEnum::FAILED;
}

ErrorCode::ErrorCodeEnum Template::getRunStyle(const XERCES_CPP_NAMESPACE::DOMNode *run, XERCES_CPP_NAMESPACE::DOMNode **rpr, XERCES_CPP_NAMESPACE::DOMElement **styleRpr)
{
  // 遍历run的所有孩子节点获取rpr样式
  XERCES_CPP_NAMESPACE::DOMNode *rprNode = nullptr;
  XERCES_CPP_NAMESPACE::DOMElement *rprStyle = nullptr;
  XERCES_CPP_NAMESPACE::DOMNode *tempNode = nullptr;
  XERCES_CPP_NAMESPACE::DOMNodeList *runChildren = run->getChildNodes();
  for (XMLSize_t i = 0; i < runChildren->getLength(); ++i)
  {
    tempNode = runChildren->item(i);
    if (tempNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
    {
      XMLCh *rprSting = nullptr;
      transString_.charToXMLCh("w:rPr", &rprSting);
      if (XERCES_CPP_NAMESPACE::XMLString::equals(tempNode->getNodeName(), rprSting))
      {
        rprNode = tempNode;
        XERCES_CPP_NAMESPACE::DOMNodeList *rPrChildren = rprNode->getChildNodes();
        for (XMLSize_t j = 0; j < rPrChildren->getLength(); ++j)
        {
          tempNode = rPrChildren->item(j);
          // XMLPrinter::printNode(tempNode);

          transString_.charToXMLCh("w:rStyle", &rprSting);
          if (XERCES_CPP_NAMESPACE::XMLString::equals(tempNode->getNodeName(), rprSting))
          {
            // 获取w:style的ID
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap *attributes = tempNode->getAttributes();
            XMLCh *styleID = nullptr;
            transString_.charToXMLCh("w:val", &styleID);
            // 获取w:style的ID的值
            XERCES_CPP_NAMESPACE::DOMNode *id = attributes->getNamedItem(styleID);
            char *styleIDStr = nullptr;
            transString_.xmlCharToChar(id->getTextContent(), &styleIDStr);
            // 根据ID获取样式
            XERCES_CPP_NAMESPACE::DOMElement *style = nullptr;
            style_.findStyleByStyleId(styleIDStr, &style);
            if (style == nullptr)
            {
              std::cout << "Style is empty!" << std::endl;
              return qi::ErrorCode::ErrorCodeEnum::FAILED;
            }
            rprStyle = style;
            break;
          }
        }
      }
    }
  }
  // 检查rpr是否为空
  if (rprNode != nullptr)
  {
    *rpr = rprNode;
  }
  if (rprStyle != nullptr)
  {
    *styleRpr = rprStyle;
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}

ErrorCode::ErrorCodeEnum Template::getParagraphStyle(const XERCES_CPP_NAMESPACE::DOMNode *paragraph, XERCES_CPP_NAMESPACE::DOMNode **ppr, XERCES_CPP_NAMESPACE::DOMNode** rpr, XERCES_CPP_NAMESPACE::DOMElement **stylePpr)
{

  // 遍历p的所有孩子节点获取rPr样式
  XERCES_CPP_NAMESPACE::DOMNode *pprNode = nullptr;
  XERCES_CPP_NAMESPACE::DOMNode *rprNode = nullptr;
  XERCES_CPP_NAMESPACE::DOMElement *pprStyle = nullptr;
  XERCES_CPP_NAMESPACE::DOMNode *tempNode = nullptr;
  XERCES_CPP_NAMESPACE::DOMNodeList *children = paragraph->getChildNodes();
  for (XMLSize_t i = 0; i < children->getLength(); ++i)
  {
    tempNode = children->item(i);
    if (tempNode->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
    {
      XMLCh *pprSting = nullptr;
      XMLCh *rprSting = nullptr;
      transString_.charToXMLCh("w:pPr", &pprSting);
      // TODO: 2024/1/7 getLocalName() 要改成 getNodeName()
      if (XERCES_CPP_NAMESPACE::XMLString::equals(tempNode->getNodeName(), pprSting))
      {
        pprNode = tempNode;
        XERCES_CPP_NAMESPACE::DOMNodeList *pPrChildren = pprNode->getChildNodes();
        for (XMLSize_t j = 0; j < pPrChildren->getLength(); ++j)
        {
          tempNode = pPrChildren->item(j);
          // XMLPrinter::printNode(tempNode);
          transString_.charToXMLCh("w:rPr", &rprSting);
          transString_.charToXMLCh("w:pStyle", &pprSting);
          if (XERCES_CPP_NAMESPACE::XMLString::equals(tempNode->getNodeName(), pprSting))
          {
            // 获取w:style的ID
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap *attributes = tempNode->getAttributes();
            XMLCh *styleID = nullptr;
            transString_.charToXMLCh("w:val", &styleID);
            // 获取w:style的ID的值
            XERCES_CPP_NAMESPACE::DOMNode *id = attributes->getNamedItem(styleID);
            char *styleIDStr = nullptr;
            transString_.xmlCharToChar(id->getTextContent(), &styleIDStr);
            // 根据ID获取样式
            XERCES_CPP_NAMESPACE::DOMElement *style = nullptr;
            style_.findStyleByStyleId(styleIDStr, &style);
            if (style == nullptr)
            {
              std::cerr << "Style is empty!" << std::endl;
              return qi::ErrorCode::ErrorCodeEnum::FAILED;
            }
            pprStyle = style;
            // 打印
            // std::cout << "Ppr Style: " << XERCES_CPP_NAMESPACE::XMLString::transcode(style->getNodeName()) << std::endl;
            break;
          }
          if (XERCES_CPP_NAMESPACE::XMLString::equals(tempNode->getNodeName(), rprSting))
          {
            rprNode = tempNode;
          }
        }
        break;
      }
    }
  }
  // 检查rpr是否为空
  if (rprNode != nullptr)
  {
    *rpr = rprNode;
  }
  if (pprNode != nullptr)
  {
    *ppr = pprNode;
  }
  if (pprStyle != nullptr)
  {
    *stylePpr = pprStyle;
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}

ErrorCode::ErrorCodeEnum Template::checkRun(const XERCES_CPP_NAMESPACE::DOMNode *run, const std::string keyword, const XERCES_CPP_NAMESPACE::DOMNode *paragraph)
{
  // 检查关键字是否为空
  if (keyword.empty())
  {
    //std::cerr << "Keyword is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 检查run是否为空
  if (run == nullptr)
  {
    std::cerr << "Run is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // 根据关键字获取样式
  XERCES_CPP_NAMESPACE::DOMNode *style = nullptr;
  getStyle(&style);
  //getStyleFromKey(keyword, &style);
  // 检查样式是否为空
  if (style == nullptr)
  {
    //std::cerr << "Style File style is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  char *text = nullptr;
  transString_.xmlCharToChar(style->getTextContent(), &text);
  if (text == nullptr)
  {
    //std::cerr << "Style File style is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // std::cout << "name1: " << text << std::endl;

  // 检测样式
  checkStyle(style, run, paragraph);


  //  // 获取run的样式
  //  XERCES_CPP_NAMESPACE::DOMNode *runStyle = nullptr;
  //  XERCES_CPP_NAMESPACE::DOMElement *runStyleElement = nullptr;
  //  getRunStyle(run, &runStyle, &runStyleElement);
  //  // 检查run样式是否为空
  //  if (runStyle == nullptr && runStyleElement == nullptr)
  //  {
  //
  //    getParagraphStyle(paragraphs, &runStyle, &runStyleElement);
  //    if (runStyle == nullptr && runStyleElement == nullptr)
  //    {
  //      style_.defaultStyle(&runStyle);
  //      if (runStyle == nullptr)
  //      {
  //        std::cerr << "Run style all is empty!" << std::endl;
  //        return qi::ErrorCode::ErrorCodeEnum::FAILED;
  //      }
  //    }
  //  }
  //  // 打印run样式
  //  if (runStyle != nullptr)
  //  {
  //    std::cout << "Run Style: " << XERCES_CPP_NAMESPACE::XMLString::transcode(runStyle->getNodeName()) << std::endl;
  //  }
  //  if (runStyleElement != nullptr)
  //  {
  //    std::cout << "Run Style Element: " << XERCES_CPP_NAMESPACE::XMLString::transcode(runStyleElement->getNodeName()) << std::endl;
  //  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::getStyleFromKey(const std::string keyword, XERCES_CPP_NAMESPACE::DOMNode **style)
{
  // 遍历模板获取符合关键字的样式
  // 更加关键字获取样式ID
  int index = -1;
  findKeyword(keyword, index);
  if (index == -1)
  {
    std::cerr << "Keyword not found!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  std::cout << "Index: " << index << std::endl;
  // TODO: 2024/1/7 把ID转换为XMLCh 有误
  // 把ID转换为XMLCh
  XMLCh *styleId = nullptr;
  transString_.xmlsize_tToXMLCh(index, &styleId);
  char *styleIdStr = nullptr;
  transString_.xmlCharToChar(styleId, &styleIdStr);

  XERCES_CPP_NAMESPACE::DOMNode *styleNode = nullptr;
  FindElements findElements;
  std::cout << XERCES_CPP_NAMESPACE::XMLString::transcode(template_->getDocumentElement()->getTagName()) << std::endl;
  findElements.FindOneElementByID(template_->getDocumentElement(), "id", styleIdStr, &styleNode);
  // 根据ID获取样式
  // 检查样式是否为空
  if (styleNode == nullptr)
  {
    std::cerr << "Style is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  *style = styleNode;

  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::getStyleIndex(int *index)
{
  // 获取style的ID
  *index = keywordIndex_;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::getStyle(xercesc_3_2::DOMNode **styleNode)
{
  // 获取当前样式只需要把当前样式的指针赋值给styleNode即可，因为Template类会一直遍历样式并把当前样式的指针赋值给currentStyle_
  *styleNode = currentStyle_;
  //  if (currentStyle_ != nullptr)
  //    std::cout << "Style: " << XERCES_CPP_NAMESPACE::XMLString::transcode(currentStyle_->getNodeName()) << std::endl;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::getNextStyle(bool isNextDiv)
{
  // 如果找到关键字那么就得从关键字开始新的样式
  if (isNextDiv)
  {
    // 从关键字开始新的样式，所有要改变currentStyle_的指针
    currentStyle_ = keywords_[keywordIndex_++].second->getNextSibling();
    // 如果currentStyle_指针不为空并且currentStyle_是文本节点那么就获取currentStyle_的下一个兄弟节点
    if (currentStyle_ && currentStyle_->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE)
    {
      currentStyle_ = currentStyle_->getNextSibling();
    }
  } else
  {
    // 如果不是从关键字开始新的样式那么就获取currentStyle_的下一个兄弟节点开始新的样式
    // 因为xml中一个节点的下一个兄弟节点可能是文本节点，所以要判断一下
    // 因为一个新的关键字开始新的样式，所以要非关键字开始的时候currentStyle_指针肯定要指向一个sub节点，也就是样式节点
    // 所以按照一个节点一个文本节点的顺序，currentStyle_指针指向的节点的下一个兄弟节点肯定是一个文本节点,所以需要获取的是下一个兄弟节点的兄弟节点
    if (currentStyle_ && currentStyle_->getNextSibling() != nullptr)
    {
      if (currentStyle_->getNextSibling()->getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE || currentStyle_->getNextSibling()->getNextSibling() != nullptr)
      {
        currentStyle_ = currentStyle_->getNextSibling()->getNextSibling();
      }
    }
    //    do
    //    {
    //      std::cout << XERCES_CPP_NAMESPACE::XMLString::transcode(currentStyle_->getNodeName());
    //      XMLCh *div = nullptr;
    //      transString_.charToXMLCh("div", &div);
    //      if (XERCES_CPP_NAMESPACE::XMLString::equals(currentStyle_->getNodeName(), div))
    //      {
    //        currentStyle_ = currentStyle_->getFirstChild()->getNextSibling();
    //      }
    //      if (currentStyle_->getNextSibling() != nullptr)
    //      {
    //        currentStyle_ = currentStyle_->getNextSibling();
    //      }
    //    } while (currentStyle_->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE);
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::getPreviousStyle()
{
  currentStyle_ = keywords_[--keywordIndex_].second;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::resetStyle()
{
  keywordIndex_ = 0;
  currentStyle_ = keywords_[keywordIndex_].second;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
void Template::printTemplate()
{
  for (auto &keyword: keywords_)
  {
    std::cout << "Keyword: " << keyword.first << " Index: " << keywordIndex_ << std::endl;
    std::cout << "Keyword: " << XERCES_CPP_NAMESPACE::XMLString::transcode(keyword.second->getTextContent()) << std::endl;
  }
}
ErrorCode::ErrorCodeEnum Template::checkStyle(const XERCES_CPP_NAMESPACE::DOMNode *style, const XERCES_CPP_NAMESPACE::DOMNode *run, const XERCES_CPP_NAMESPACE::DOMNode *paragraph)
{
  // 检查样式是否为空
  if (style == nullptr)
  {
    std::cerr << "Style is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }

  // 遍历style获取每一个子节点
  for (XERCES_CPP_NAMESPACE::DOMNode *child = style->getFirstChild(); child != nullptr; child = child->getNextSibling())
  {
    // 如果子节点不是元素节点就跳过
    if (child->getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
    {
      continue;
    }
    // 检查run是否为空
    if (run == nullptr)
    {
      std::cerr << "Run is empty!" << std::endl;
      return qi::ErrorCode::ErrorCodeEnum::FAILED;
    }
    //  XMLPrinter::printNode(style);
    //  XMLPrinter::printNode(run);
    //  XMLPrinter::print("----------------------------------------");
    //  XMLPrinter::printNode(paragraph);

    // 保存格式是否合格
    bool isOk = false;

    // 遍历run的rpr标签
    XERCES_CPP_NAMESPACE::DOMNode *rpr = nullptr;
    XERCES_CPP_NAMESPACE::DOMElement *styleRpr = nullptr;
    getRunStyle(run, &rpr, &styleRpr);
    // 检查rpr是否为空
    if (rpr == nullptr && styleRpr == nullptr)
    {
      std::cerr << "Run style is empty!" << std::endl;
    }
    if (rpr != nullptr && !isOk)
    {
      // XMLPrinter::printNode(rpr);
      // XMLPrinter::printNode(style);
      compareStyle(child, rpr, &isOk);
    }
    if (styleRpr != nullptr && !isOk)
    {
      // XMLPrinter::printNode(styleRpr);
      compareStyle(child, styleRpr, &isOk);
    }
    // 遍历paragraph的ppr标签
    XERCES_CPP_NAMESPACE::DOMNode *paragraphRpr = nullptr;
    XERCES_CPP_NAMESPACE::DOMNode *ppr = nullptr;
    XERCES_CPP_NAMESPACE::DOMElement *stylePpr = nullptr;
    getParagraphStyle(paragraph, &ppr, &paragraphRpr, &stylePpr);
    // 检查ppr是否为空
    if (ppr == nullptr && stylePpr == nullptr && paragraphRpr == nullptr)
    {
      std::cerr << "Paragraph style is empty!" << std::endl;
    }
    if (paragraphRpr != nullptr && !isOk)
    {
      // XMLPrinter::printNode(paragraphRpr);
      compareStyle(child, paragraphRpr, &isOk);
    }
    if (ppr != nullptr && !isOk)
    {
      // XMLPrinter::printNode(ppr);
      compareStyle(child, ppr, &isOk);
    }
    if (stylePpr != nullptr && !isOk)
    {
      // XMLPrinter::printNode(stylePpr);
      compareStyle(child, stylePpr, &isOk);
    }

    // 获取默认文档样式docDefaults
    XERCES_CPP_NAMESPACE::DOMNode *docDefaults = nullptr;
    style_.defaultStyle(&docDefaults);
    if (docDefaults == nullptr)
    {
      std::cerr << "DocDefaults is empty!" << std::endl;
    }

    if (docDefaults != nullptr && !isOk)
    {
      // XMLPrinter::printNode(docDefaults);
      compareStyle(child, docDefaults, &isOk);
    }
    if (!isOk)
    {
      // XMLPrinter::printNode(child);
      std::string *text = nullptr;
      transString_.xmlCharToString(run->getTextContent(), &text);
      EraseSpaces eraseSpaces;
      eraseSpaces.eraseSpaces(*text);
      eraseSpaces.eraseNewLine(*text);
      std::cout << "style is not OK, the error is near " << *text << std::endl;
    }
    // else
    //   std::cout << "Style is OK!" << std::endl;
    // 检查样式是否符合模板
    //  if (style_.checkStyle(style, rpr, ppr))
    //  {
    //    std::cout << "Style is OK!" << std::endl;
    //  } else
    //  {
    //    std::cerr << "Style is not OK!" << std::endl;
    //  }
  }
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::setCurrentParagraph(Paragraph paragraph)
{
  currentParagraph_ = paragraph;
  return ErrorCode::ErrorCodeEnum::SUCCESS;
}
ErrorCode::ErrorCodeEnum Template::compareStyle(XERCES_CPP_NAMESPACE::DOMNode *style, XERCES_CPP_NAMESPACE::DOMNode *textStyle, bool *isSame)
{
  // 检查样式是否为空
  if (style == nullptr || textStyle == nullptr)
  {
    std::cerr << "Style is empty!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }

  *isSame = false;

  // 把node转换为element
  NodeToElement nodeToElement;
  XERCES_CPP_NAMESPACE::DOMElement *textStyleElement = nullptr;
  nodeToElement.nodeToElement(textStyle, &textStyleElement);
  XERCES_CPP_NAMESPACE::DOMElement *styleElement = nullptr;
  nodeToElement.nodeToElement(style, &styleElement);

  // 获取style的标签名
  std::string *styleString = nullptr;
  transString_.xmlCharToString(styleElement->getTagName(), &styleString);
  // std::cout << "Style: " << *styleString << std::endl;

  // 在目标格式中查找style的标签名
  XERCES_CPP_NAMESPACE::DOMNodeList *resultList = nullptr;
  FindElements findElements;
  findElements.FindElementByTagName(textStyleElement, *styleString, &resultList);

  if (resultList == nullptr)
  {
    std::cerr << "Result list is nullptr!" << std::endl;
    return qi::ErrorCode::ErrorCodeEnum::FAILED;
  }
  // XMLPrinter::printNode(resultList->item(0));
  // XMLPrinter::printNode(styleElement);

  // 比较style和textStyle是否相同
  // 遍历resultList
  for (XMLSize_t i = 0; i <= resultList->getLength(); i++)
  {
    // 获取resultList的第i个节点
    XERCES_CPP_NAMESPACE::DOMNode *node = resultList->item(i);
    // 检查node是否为空
    if (node == nullptr)
    {
      std::cout << *styleString << " is not find style from target files" << std::endl;
      *isSame = false;
      return qi::ErrorCode::ErrorCodeEnum::FAILED;
    }
    // 比较style和textStyle是否相同
    //    if (styleElement->isEqualNode(node))
    //    {
    //      *isSame = true;
    //      return qi::ErrorCode::ErrorCodeEnum::SUCCESS;
    //    }
    // 遍历style的所有属性
    XERCES_CPP_NAMESPACE::DOMNamedNodeMap *styleAttributes = styleElement->getAttributes();
    // 获取待检测文档格式的属性
    XERCES_CPP_NAMESPACE::DOMNamedNodeMap *textStyleAttributes = node->getAttributes();
    for (XMLSize_t j = 0; j < styleAttributes->getLength(); j++)
    {
      // 获取style的第j个属性
      XERCES_CPP_NAMESPACE::DOMNode *styleAttribute = styleAttributes->item(j);
      // 检查styleAttribute是否为空
      if (styleAttribute == nullptr)
      {
        std::cerr << "Template Style Attribute is nullptr!" << std::endl;
        return qi::ErrorCode::ErrorCodeEnum::FAILED;
      }
      // std::cout << XMLString::transcode(styleAttribute->getNodeName()) << std::endl;
      // 从node寻找 叫styleAttribute->getNodeName() 的属性
      for (XMLSize_t k = 0; k < textStyleAttributes->getLength(); k++)
      {
        // std::cout << XMLString::transcode(styleAttribute->getNodeName()) << std::endl;
        // std::cout << XMLString::transcode(textStyleAttributes->item(k)->getNodeName()) << std::endl;
        if (XMLString::equals(styleAttribute->getNodeName(), textStyleAttributes->item(k)->getNodeName()))
        {
          // 获取styleAttribute的值
          char *styleAttributeValue = nullptr;
          transString_.xmlCharToChar(styleAttribute->getNodeValue(), &styleAttributeValue);
          // 获取textStyleAttribute的值
          char *textStyleAttributeValue = nullptr;
          transString_.xmlCharToChar(textStyleAttributes->item(k)->getNodeValue(), &textStyleAttributeValue);
          // 比较styleAttribute的值和textStyleAttribute的值是否相同
          if (strcmp(styleAttributeValue, textStyleAttributeValue) == 0)
          {
            *isSame = true;
          } else
          {
            *isSame = false;
            std::cout << "Now Check Style is " << *styleString << " Style Files in is " << styleAttributeValue << " Target Files is " << textStyleAttributeValue << std::endl;
          }
        }
      }
    }

    return ErrorCode::ErrorCodeEnum::SUCCESS;
  }
}
}// namespace qi


// 初始化模板关键字
//  keywords_ =
//  {
//    {1, "本科毕业论文（设计）"},
//    {2, "中文论文题目"},
//    {3, "EengligTitle"},
//    {4, "2024年1月7日"},
//    {5, "毕业论文原创性声明"},
//    {6, "目录"},
//    {7, "全文共xx页xxxx字"},
//    {8, "基于Python的高校教务管理系统的设计与实现"},
//    {9, "摘要"},
//    {10, "关键词"},
//    {11, "AnOrganixedTacticsofLargeDatabaseSystemforReal-timeCollectionandQuery"},
//    {12, "Abstract"},
//    {13, "Keywords"},
//    {14, "$main"},
//    {15, "致谢"},
//    {16, "参考文献"}
//  };


//  // 遍历模板的所有子节点, 模板的子节点是<div>标签，每个<div>标签是一个关键字,div的第一个孩子节点是文本节点第二个孩子节点是name标签
//  for (XERCES_CPP_NAMESPACE::DOMNode *child = root->getFirstChild()->getNextSibling(); child != nullptr; child = child->getNextSibling())
//  {
//    // 如果子节点不是元素节点就跳过
//    if (child->getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
//    {
//      continue;
//    }
//    // 获取子节点的标签名
//    char *tagName = nullptr;
//    transString_.xmlCharToChar(child->getNodeName(), &tagName);
//    // 保存div
//    XERCES_CPP_NAMESPACE::DOMNode *div = child;
//    // 获取div标签的第1个孩子节点是文本节点第二个孩子节点是name标签
//    XERCES_CPP_NAMESPACE::DOMNode *divSecondChild = div->getFirstChild()->getNextSibling();
//    // div的第一个孩子节点的文本内容就是关键字。如果div第二个孩子不是name标签，就报错
//    const XMLCh *nameString = divSecondChild->getNodeName();
//    XMLCh *name = nullptr;
//    transString_.charToXMLCh("name", &name);
//    if (!(XERCES_CPP_NAMESPACE::XMLString::equals(nameString, name)))
//    {
//      std::cerr << "First child is not name!" << std::endl;
//      return qi::ErrorCode::ErrorCodeEnum::FAILED;
//    }
//    // 获取name标签的文本内容
//    std::string *text = nullptr;
//    transString_.xmlCharToString(divSecondChild->getTextContent(), &text);
//    // 清除空格工具
//    EraseSpaces eraseSpaces;
//    // 清除空格
//    eraseSpaces.eraseSpaces(*text);
//    // 清除换行
//    eraseSpaces.eraseNewLine(*text);
//    //std::cout << "Keyword: " << *text << std::endl;
//    // 保存关键字
//    keywords_.insert(std::make_pair(*text, std::make_pair(keywordCount_, div)));
//    // 获取<div>标签数量
//    ++keywordCount_;
//  }
