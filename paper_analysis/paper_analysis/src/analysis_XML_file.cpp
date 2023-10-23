#include "analysis_XML_file.h"

#include <iostream>
#include <stack>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/util/TransService.hpp>
#include "translation_label.h"

qi::CAnalysisXMLFile::CAnalysisXMLFile()
{
  // 转码"LS"为XMLCh*
  XMLCh* gLS = XERCES_CPP_NAMESPACE::XMLString::transcode("LS");
  // 使用gLS获取DOMImplementationLS
  XERCES_CPP_NAMESPACE::DOMImplementationLS* impl = XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation(gLS);
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
  this->parser_ = parser;
  this->errHandler_ = errHandler;
}

qi::CAnalysisXMLFile::~CAnalysisXMLFile()
{
  // 释放解析器
  this->parser_->release();
  if (this->errHandler_)
    delete this->errHandler_;
}


qierr::error_code qi::CAnalysisXMLFile::init()
{
  // 初始化XML4C2系统。
  try
  {
    // 初始化XML4C2系统
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
  }
  catch (XERCES_CPP_NAMESPACE::XMLException const& toCatch)
  {
    // 处理初始化XML4C2系统时的异常
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "在Xerces-c初始化过程中发生错误。\n"
      << "  异常信息"
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return qierr::E_INITFAIL;
  }

  return qierr::E_OK;
}
 qierr::error_code qi::CAnalysisXMLFile::relese()
{
  // 调用XML4C2系统的终止方法
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::loadXMLFile(char const* file_path)
{
  XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = nullptr;
  unsigned long duration = 0;
  try
  {
    // 重置文档池
    this->parser_->resetDocumentPool();

    // 获取解析开始时间
    unsigned long const startMillis = XERCES_CPP_NAMESPACE::XMLPlatformUtils::getCurrentMillis();
    // 解析指定文件路径的XML文件
    doc = this->parser_->parseURI(file_path);
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
    return qierr::E_OUTOFMEM;
  }
  catch (XERCES_CPP_NAMESPACE::XMLException const& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "解析过程中发生错误\n   错误信息: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return qierr::E_XMLEXCEPTION;
  }
  catch (XERCES_CPP_NAMESPACE::DOMException const& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "解析过程中发生错误\n   错误信息: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return qierr::E_DOMEXCEPTTON;
  }
  catch (...)
  {
    XERCES_STD_QUALIFIER cerr << "解析过程中发生错误\n " << XERCES_STD_QUALIFIER endl;
    return qierr::E_UNKNOWN;
  }
  // 将解析得到的文档赋值给类成员
  this->doc_ = doc;
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::parseXMLTree()
{
  if (!this->doc_)
    return qierr::E_EMPTY;
  //char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(doc->getElementsByTagName);
  //XERCES_STD_QUALIFIER cout << "Parsed file: " << pMsg << XERCES_STD_QUALIFIER endl;
  //XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);

  // 初始化元素计数器
  size_t elementCount = 0;
  // 获取XML文档的根元素
  this->root_ = this->doc_->getDocumentElement();
  if (this->root_)
    elementCount = this->root_->getChildElementCount();
  else
    XERCES_STD_QUALIFIER cerr << "无法找到根元素" << XERCES_STD_QUALIFIER endl;
  // 输出元素数量
  XERCES_STD_QUALIFIER cout << elementCount << " 个元素。" << XERCES_STD_QUALIFIER endl;
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::analysisXMLFile(qi::CTranslationLabel* translation_lable)
{
  this->parseXMLTree();
  // 对XML树进行深度优先遍历，并调用printNodeInfo方法输出节点信息
  this->dfsTraverseXMLTree(this->root_, &qi::CAnalysisXMLFile::printNodeInfo, translation_lable);

  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::analysisXMLFile(qi::CTranslationLabel* translation_lable, char const* xml_file_path, XERCES_STD_QUALIFIER map<std::string, xercesc::DOMElement*>* results, XERCES_STD_QUALIFIER mutex* mtx)
{
  XERCES_STD_QUALIFIER cout << xml_file_path << XERCES_STD_QUALIFIER endl;

  this->loadXMLFile(xml_file_path);
  this->parseXMLTree();
  // this->analysisXMLFile(translation_lable);
  mtx->lock();
  results->insert(std::make_pair(xml_file_path, this->root_));
  mtx->unlock();
  
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::getDOMElementPtr(XERCES_CPP_NAMESPACE::DOMElement** root)
{
  if (this->root_ == nullptr)
  {
    XERCES_STD_QUALIFIER cerr << "root_ is null" << XERCES_STD_QUALIFIER endl;
    return qierr::E_EMPTY;
  }
  *root = this->root_;
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::printXMLInfo(XERCES_CPP_NAMESPACE::DOMElement* root, qi::CTranslationLabel* translation_lable)
{
  std::cout << root << std::endl;
  dfsTraverseXMLTree(root, &qi::CAnalysisXMLFile::printNodeInfo, translation_lable);
  return qierr::E_OK;
}

qierr::error_code qi::CAnalysisXMLFile::XPathSearch(char const* XPathString)
{
  if (this->doc_ == nullptr)
  {
    XERCES_STD_QUALIFIER cerr << "doc_ is null" << XERCES_STD_QUALIFIER endl;
    return qierr::E_EMPTY;
  }
  if (this->root_ == nullptr)
  {
    XERCES_STD_QUALIFIER cerr << "root_ is null" << XERCES_STD_QUALIFIER endl;
    return qierr::E_EMPTY;
  }
  if (XPathString == nullptr)
  {
    XERCES_STD_QUALIFIER cerr << "XPathString is null" << XERCES_STD_QUALIFIER endl;
    return qierr::E_EMPTY;
  }
  char const* gXPathExpression = XPathString;
  XMLCh* xpathStr = XERCES_CPP_NAMESPACE::XMLString::transcode(gXPathExpression);
  try
  {
    char* pMsg = nullptr;
    XMLCh* nsURI = XERCES_CPP_NAMESPACE::XMLString::transcode("http://www.w3.org/XML/1998/namespace");
    XERCES_CPP_NAMESPACE::DOMXPathNSResolver* resolver = this->doc_->createNSResolver(this->root_);
    if (nullptr != resolver->lookupPrefix(nsURI))
    {
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(resolver->lookupPrefix(nsURI));
      XERCES_STD_QUALIFIER cout << pMsg << XERCES_STD_QUALIFIER endl;
    }
    else
    {
      XERCES_STD_QUALIFIER cout << "lookupPrefix failed" << XERCES_STD_QUALIFIER endl;
    }
    if (nullptr != resolver->lookupNamespaceURI(XERCES_CPP_NAMESPACE::XMLUni::fgXMLString))
    {
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(resolver->lookupNamespaceURI(XERCES_CPP_NAMESPACE::XMLUni::fgXMLString));
      XERCES_STD_QUALIFIER cout << pMsg << XERCES_STD_QUALIFIER endl;
    }
    else
    {
      XERCES_STD_QUALIFIER cout << "lookupNamespaceURI failed" << XERCES_STD_QUALIFIER endl;
    }

    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    XERCES_CPP_NAMESPACE::XMLString::release(&nsURI);

    XERCES_CPP_NAMESPACE::DOMXPathResult* result = this->doc_->evaluate(
      xpathStr,
      this->root_,
      resolver,
      XERCES_CPP_NAMESPACE::DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,
      NULL);

    XMLSize_t nLength = result->getSnapshotLength();
    for (XMLSize_t i = 0; i < nLength; ++i)
    {
      result->snapshotItem(i);
      // printTag(result->getNodeValue());
      // XERCES_STD_QUALIFIER cout << XERCES_CPP_NAMESPACE::TranscodeToStr(result->getNodeValue()->getNodeName(), "ascii").str() << XERCES_STD_QUALIFIER endl;
      // XERCES_STD_QUALIFIER cout << XERCES_CPP_NAMESPACE::TranscodeToStr(result->getNodeValue()->getChildNodes()->item(3)->getNodeName(), "ascii").str() << XERCES_STD_QUALIFIER endl;
    }
    result->release();
    resolver->release();
  }
  catch (XERCES_CPP_NAMESPACE::DOMXPathException const& e)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(e.getMessage());
    XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
      << XERCES_STD_QUALIFIER endl
      << pMsg << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  catch (XERCES_CPP_NAMESPACE::DOMException const& e)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(e.getMessage());
    XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
      << XERCES_STD_QUALIFIER endl
      << pMsg << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  XERCES_CPP_NAMESPACE::XMLString::release(&xpathStr);

  return qierr::E_OK;
}

qierr::errorcode qi::CAnalysisXMLFile::printNodeInfo(XERCES_CPP_NAMESPACE::DOMNode* node, std::string& path, qi::CTranslationLabel* translation_lable)
{
  std::string fullPath = path;

  // 获取节点名称
  char* pNodeName = XERCES_CPP_NAMESPACE::XMLString::transcode(node->getLocalName());
  XERCES_STD_QUALIFIER cout << "Node Name: " << pNodeName << " -> " << translation_lable->findValueByKey(fullPath) << XERCES_STD_QUALIFIER endl;

  // 释放字符串内存
  XERCES_CPP_NAMESPACE::XMLString::release(&pNodeName);

  // 判断节点类型
  if (node->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
  {
    // 获取节点属性
    XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = node->getAttributes();
    char* pAttrName = nullptr;
    char* pAttrValue = nullptr;
    if (attributes && attributes->getLength() > 0)
    {
      XERCES_STD_QUALIFIER cout << "Attributes: \n";

      // 遍历节点属性
      for (XMLSize_t i = 0; i < attributes->getLength(); ++i)
      {
        XERCES_CPP_NAMESPACE::DOMNode* attribute = attributes->item(i);

        // 获取属性名称和属性值
        pAttrName = XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getLocalName());
        pAttrValue = XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getNodeValue());

        // 打印属性名称和属性值
        XERCES_STD_QUALIFIER cout << "now path: " << fullPath << "$" << pAttrName << XERCES_STD_QUALIFIER endl;
        XERCES_STD_QUALIFIER cout << pAttrName << "=\"" << pAttrValue << "\n";
        XERCES_STD_QUALIFIER cout << pAttrName << "->" << "***翻译为：" << translation_lable->findValueByKey(fullPath + "$" + pAttrName) << "=" << pAttrValue << "***\n";

        // 释放字符串内存
        XERCES_CPP_NAMESPACE::XMLString::release(&pAttrName);
        XERCES_CPP_NAMESPACE::XMLString::release(&pAttrValue);
      }
      XERCES_STD_QUALIFIER cout << XERCES_STD_QUALIFIER endl;
    }
  }
  // 返回错误码
  return qierr::errorcode();
}

qierr::errorcode qi::CAnalysisXMLFile::dfsTraverseXMLTree(XERCES_CPP_NAMESPACE::DOMNode* root, qierr::errorcode(qi::CAnalysisXMLFile::* printNodeFun)(XERCES_CPP_NAMESPACE::DOMNode* node, XERCES_STD_QUALIFIER string& labelPath, qi::CTranslationLabel* translation_lable), qi::CTranslationLabel* translation_lable)
{
  XERCES_STD_QUALIFIER stack<std::pair<XERCES_CPP_NAMESPACE::DOMNode*, std::string>> nodeStack;

  // 获取根节点名称
  char* NodeName = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getLocalName());
  XERCES_STD_QUALIFIER string xmlLablePath = XERCES_STD_QUALIFIER string(NodeName);
  nodeStack.push(std::make_pair(root, xmlLablePath));

  // 遍历节点栈
  while (!nodeStack.empty())
  {
    XERCES_CPP_NAMESPACE::DOMNode* node = nodeStack.top().first;
    std::string path = nodeStack.top().second;
    nodeStack.pop();

    // 调用打印节点信息函数
    // (this->*printNodeFun)(node, path, translation_lable);

    // 获取子节点列表
    XERCES_CPP_NAMESPACE::DOMNodeList* children = node->getChildNodes();
    XMLSize_t const numChildren = children->getLength();
    for (int i = numChildren - 1; i > 0; --i)
    {
      XERCES_CPP_NAMESPACE::DOMNode* child = children->item(i);
      if (child && child->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
      {
        // 获取子节点名称
        char* pNodeName = XERCES_CPP_NAMESPACE::XMLString::transcode(child->getLocalName());

        // 将子节点和路径压入节点栈
        nodeStack.push(std::make_pair(child, path + "$" + XERCES_STD_QUALIFIER string(pNodeName)));

        // 释放字符串内存
        XERCES_CPP_NAMESPACE::XMLString::release(&pNodeName);
      }
    }

    XERCES_STD_QUALIFIER cout << XERCES_STD_QUALIFIER endl;
    XERCES_STD_QUALIFIER cout << XERCES_STD_QUALIFIER endl;
  }

  return qierr::errorcode();
}


/*
void printTag(XERCES_CPP_NAMESPACE::DOMNode* root)
{
  char* pMsg = nullptr;
  XERCES_STD_QUALIFIER cout << "------------------------------------------------" << XERCES_STD_QUALIFIER endl;
  pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNodeName());
  XERCES_STD_QUALIFIER cout << "NodeName:" << pMsg << XERCES_STD_QUALIFIER endl;
  if (root->getNodeType())
  {
    XERCES_STD_QUALIFIER cout << "NodeType:" << root->getNodeType() << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NodeType: null" << XERCES_STD_QUALIFIER endl;
  if (root->getNodeValue())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNodeValue());
    XERCES_STD_QUALIFIER cout << "NodeValue:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NodeValue: null" << XERCES_STD_QUALIFIER endl;
  if (root->getPrefix())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getPrefix());
    XERCES_STD_QUALIFIER cout << "Prefix:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "Prefix: null" << XERCES_STD_QUALIFIER endl;
  if (root->getLocalName())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getLocalName());
    XERCES_STD_QUALIFIER cout << "LocalName:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "LocalName: null" << XERCES_STD_QUALIFIER endl;
  if (root->getAttributes()->getLength())
  {
    for (int i = 0; i < root->getAttributes()->getLength(); i++)
    {
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getAttributes()->item(i)->getNodeName());
      XERCES_STD_QUALIFIER cout << "AttributeNodeName:" << pMsg << XERCES_STD_QUALIFIER endl;
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getAttributes()->item(i)->getNodeValue());
      XERCES_STD_QUALIFIER cout << "AttributeNodeValue:" << pMsg << XERCES_STD_QUALIFIER endl;
    }
  }
  else
    XERCES_STD_QUALIFIER cout << "Attribute: null" << XERCES_STD_QUALIFIER endl;
  if (root->getTextContent())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getTextContent());
    // XERCES_STD_QUALIFIER cout << "TextContent:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "TextContent: null" << XERCES_STD_QUALIFIER endl;

  if (root->getNamespaceURI())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNamespaceURI());
    XERCES_STD_QUALIFIER cout << "NamespaceURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NamespaceURI: null" << XERCES_STD_QUALIFIER endl;
  if (root->getBaseURI())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getBaseURI());
    XERCES_STD_QUALIFIER cout << "BaseURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "BaseURI: null" << XERCES_STD_QUALIFIER endl;
  if (root->getOwnerDocument())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getOwnerDocument()->getDocumentURI());
    XERCES_STD_QUALIFIER cout << "DocumentURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "DocumentURI: null" << XERCES_STD_QUALIFIER endl;
  XERCES_STD_QUALIFIER cout << "------------------------------------------------" << XERCES_STD_QUALIFIER endl;
  XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
}

void printTag(XERCES_CPP_NAMESPACE::DOMElement* root)
{
  char* pMsg = nullptr;
  XERCES_STD_QUALIFIER cout << "------------------------------------------------" << XERCES_STD_QUALIFIER endl;
  pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNodeName());
  XERCES_STD_QUALIFIER cout << "NodeName:" << pMsg << XERCES_STD_QUALIFIER endl;
  if (root->getTagName())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getTagName());
    XERCES_STD_QUALIFIER cout << "TagName:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "TagName: null" << XERCES_STD_QUALIFIER endl;
  if (root->getNodeType())
  {
    XERCES_STD_QUALIFIER cout << "NodeType:" << root->getNodeType() << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NodeType: null" << XERCES_STD_QUALIFIER endl;
  if (root->getNodeValue())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNodeValue());
    XERCES_STD_QUALIFIER cout << "NodeValue:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NodeValue: null" << XERCES_STD_QUALIFIER endl;
  if (root->getPrefix())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getPrefix());
    XERCES_STD_QUALIFIER cout << "Prefix:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "Prefix: null" << XERCES_STD_QUALIFIER endl;
  if (root->getLocalName())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getLocalName());
    XERCES_STD_QUALIFIER cout << "LocalName:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "LocalName: null" << XERCES_STD_QUALIFIER endl;
  if (root->getAttributes()->getLength())
  {
    for (int i = 0; i < root->getAttributes()->getLength(); i++)
    {
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getAttributes()->item(i)->getNodeName());
      XERCES_STD_QUALIFIER cout << "AttributeNodeName:" << pMsg << XERCES_STD_QUALIFIER endl;
      pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getAttributes()->item(i)->getNodeValue());
      XERCES_STD_QUALIFIER cout << "AttributeNodeValue:" << pMsg << XERCES_STD_QUALIFIER endl;
    }
  }
  else
    XERCES_STD_QUALIFIER cout << "Attribute: null" << XERCES_STD_QUALIFIER endl;
  if (root->getTextContent())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getTextContent());
    // XERCES_STD_QUALIFIER cout << "TextContent:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "TextContent: null" << XERCES_STD_QUALIFIER endl;

  if (root->getNamespaceURI())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getNamespaceURI());
    XERCES_STD_QUALIFIER cout << "NamespaceURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "NamespaceURI: null" << XERCES_STD_QUALIFIER endl;
  if (root->getBaseURI())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getBaseURI());
    XERCES_STD_QUALIFIER cout << "BaseURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "BaseURI: null" << XERCES_STD_QUALIFIER endl;
  if (root->getOwnerDocument())
  {
    pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getOwnerDocument()->getDocumentURI());
    XERCES_STD_QUALIFIER cout << "DocumentURI:" << pMsg << XERCES_STD_QUALIFIER endl;
  }
  else
    XERCES_STD_QUALIFIER cout << "DocumentURI: null" << XERCES_STD_QUALIFIER endl;
  XERCES_STD_QUALIFIER cout << "------------------------------------------------" << XERCES_STD_QUALIFIER endl;
  XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
}

void ergodicTag(XERCES_CPP_NAMESPACE::DOMElement* root)
{
  if (root == 0)
  {
    return;
  }
  if (0 == root->getChildElementCount())
  {
    printTag(root);
    if (0 == root->getNextElementSibling())
      return;
    else
      ergodicTag(root->getNextElementSibling());
  }
  else
  {
    printTag(root);
    ergodicTag(root->getFirstElementChild());
    if (0 == root->getNextElementSibling())
      return;
    else
      ergodicTag(root->getNextElementSibling());
  }
}
*/
/*
qierr::errorcode qi::CPaperAnalysis::dfsTraverseXMLTree(XERCES_CPP_NAMESPACE::DOMNode* root, qierr::errorcode(qi::CPaperAnalysis::*printNodeFun)(XERCES_CPP_NAMESPACE::DOMNode* node))
{
  XERCES_STD_QUALIFIER stack<XERCES_CPP_NAMESPACE::DOMNode*> nodeStack;
  nodeStack.push(root);

  while (!nodeStack.empty()) {
    XERCES_CPP_NAMESPACE::DOMNode* node = nodeStack.top();
    nodeStack.pop();

    printNodeInfo(node);

    XERCES_CPP_NAMESPACE::DOMNodeList* children = node->getChildNodes();
    const XMLSize_t numChildren = children->getLength();
    //XERCES_STD_QUALIFIER cout << "Children: " << numChildren << XERCES_STD_QUALIFIER endl;
    for (XMLSize_t i = numChildren - 1; i < numChildren; --i) {
      XERCES_CPP_NAMESPACE::DOMNode* child = children->item(i);
      //XERCES_STD_QUALIFIER cout << "Child: " << i << XERCES_CPP_NAMESPACE::XMLString::transcode(child->getNodeName()) << XERCES_STD_QUALIFIER endl;
      if (child && child->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE) {
        nodeStack.push(child);
      }
    }
  }
  return qierr::errorcode();
}
*/
/*
qierr::errorcode qi::CPaperAnalysis::printNodeInfo(XERCES_CPP_NAMESPACE::DOMNode* node)
{
  XERCES_STD_QUALIFIER cout << "Node Name: " << XERCES_CPP_NAMESPACE::XMLString::transcode(node->getNodeName()) << XERCES_STD_QUALIFIER endl;
  if (node->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE) {
    XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = node->getAttributes();
    if (attributes && attributes->getLength() > 0) {
      XERCES_STD_QUALIFIER cout << "Attributes: ";
      for (XMLSize_t i = 0; i < attributes->getLength(); ++i) {
        XERCES_CPP_NAMESPACE::DOMNode* attribute = attributes->item(i);
        XERCES_STD_QUALIFIER cout << XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getNodeName()) << "=\""
          << XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getNodeValue()) << "\n" ;
      }
      XERCES_STD_QUALIFIER cout << XERCES_STD_QUALIFIER endl;
    }
  }
  char* nodeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(node->getNodeValue());
  if (nodeValue && XERCES_CPP_NAMESPACE::XMLString::stringLen(nodeValue) > 0) {
    XERCES_STD_QUALIFIER cout << "Node Value: " << nodeValue << XERCES_STD_QUALIFIER endl;
  }
  XERCES_CPP_NAMESPACE::XMLString::release(&nodeValue);
  return qierr::errorcode();
}
*/
//
//
//qierr::error_code qi::CPaperAnalysis::getDomElement(XERCES_CPP_NAMESPACE::DOMElement* root)
//{
//  if (!this->doc_)
//    return qierr::E_EMPTY;
//  //char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(doc->getElementsByTagName);
//  //XERCES_STD_QUALIFIER cout << "Parsed file: " << pMsg << XERCES_STD_QUALIFIER endl;
//  //XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
//  size_t elementCount = 0;
//  root = this->doc_->getDocumentElement();
//  if (root)
//    elementCount = root->getChildElementCount();
//  else
//    XERCES_STD_QUALIFIER cerr << "can not find root element" << XERCES_STD_QUALIFIER endl;
//  XERCES_STD_QUALIFIER cout << elementCount << " elements." << XERCES_STD_QUALIFIER endl;
//  this->root_ = root;
//  return qierr::E_OK;
//}
//
//qierr::error_code qi::CPaperAnalysis::getBodyElement(XERCES_CPP_NAMESPACE::DOMElement* body)
//{
//  if (!this->root_)
//    return qierr::E_EMPTY;
//  XMLCh* lable_name = XERCES_CPP_NAMESPACE::XMLString::transcode("w:body");
//  XERCES_CPP_NAMESPACE::DOMNodeList* bodyList = this->root_->getElementsByTagName(lable_name);
//  XERCES_CPP_NAMESPACE::XMLString::release(&lable_name);
//  if (!bodyList)
//  {
//    XERCES_STD_QUALIFIER cerr << "can not find body element" << XERCES_STD_QUALIFIER endl;
//    return qierr::E_EMPTY;
//  }
//  if (bodyList->getLength() > 1)
//  {
//    XERCES_STD_QUALIFIER cerr << "more than one body element" << XERCES_STD_QUALIFIER endl;
//    return qierr::E_ILLEGAL;
//  }
//  if (bodyList->getLength() == 0)
//  {
//    XERCES_STD_QUALIFIER cerr << "can not find body element" << XERCES_STD_QUALIFIER endl;
//    return qierr::E_EMPTY;
//  }
//  body = dynamic_cast<XERCES_CPP_NAMESPACE::DOMElement*>(bodyList->item(0));
//  this->body_ = body;
//  return qierr::E_OK;
//}
/*
qierr::error_code qi::CPaperAnalysis::printLableProperties(XERCES_CPP_NAMESPACE::DOMNode* node, qi::CTranslationLabel* translation_lable)
{
  static int level = 0;
  ++level;

  if (!this->body_)
    return qierr::E_EMPTY;
  if (!node)
    node = this->body_;
  XERCES_CPP_NAMESPACE::DOMNode* current_child = node->getFirstChild();
  while (current_child)
  {
    if (current_child->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE)
    {
      if (!(level - 1))
        XERCES_STD_QUALIFIER cout << "\n\n***** New Lable Properties *****\n\n" << XERCES_STD_QUALIFIER endl;
      char* lable_name = XERCES_CPP_NAMESPACE::XMLString::transcode(current_child->getLocalName());
      XERCES_STD_QUALIFIER cout << "\n" << lable_name << "->";
      //XERCES_STD_QUALIFIER cout << translation_lable->getLabelDescription(lable_name, "Description") << XERCES_STD_QUALIFIER endl;
      XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_child->getAttributes();
      if (attributes)
      {
        XERCES_STD_QUALIFIER cout << "Attributes:" << XERCES_STD_QUALIFIER endl;
        for (XMLSize_t i = 0; i < attributes->getLength(); ++i)
        {
          XERCES_CPP_NAMESPACE::DOMNode* attribute = attributes->item(i);
          char* attribute_name = XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getLocalName());
          //XERCES_STD_QUALIFIER cout << attribute_name << "->" << translation_lable->getLabelAttributeDescription(lable_name, attribute_name, "Description") << ":";
          char* attribute_value = XERCES_CPP_NAMESPACE::XMLString::transcode(attribute->getNodeValue());
          //XERCES_STD_QUALIFIER cout << attribute_value << "->" << translation_lable->getLabelAttributeDescription(lable_name, attribute_name, attribute_value) << XERCES_STD_QUALIFIER endl;
          XERCES_CPP_NAMESPACE::XMLString::release(&attribute_name);
          XERCES_CPP_NAMESPACE::XMLString::release(&attribute_value);
        }
      }
      else
      {
        XERCES_STD_QUALIFIER cout << "No attributes" << XERCES_STD_QUALIFIER endl;
      }
      XERCES_CPP_NAMESPACE::XMLString::release(&lable_name);
      if (current_child->hasChildNodes())
        printLableProperties(current_child, translation_lable);
    }
    current_child = current_child->getNextSibling();
  }
  --level;
  return qierr::E_OK;
}
*/
