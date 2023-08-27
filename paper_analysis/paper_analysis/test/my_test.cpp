#include <iostream>
#include <fstream>
#include <json/json.h>
#include <functional>
#include <string>
#include <map>
#include <cassert>

#include "translation_label.h"

using namespace std;

class Error
{
public:
  Error(int value, const std::string& str)
  {
    m_value = value;
    m_message = str;
#ifdef _DEBUG
    ErrorMap::iterator found = GetErrorMap().find(value);
    if (found != GetErrorMap().end())
      assert(found->second == m_message);
#endif
    GetErrorMap()[m_value] = m_message;
  }

  // auto-cast Error to integer error code
  operator int() { return m_value; }

private:
  int m_value;
  std::string m_message;

  typedef std::map<int, std::string> ErrorMap;
  static ErrorMap& GetErrorMap()
  {
    static ErrorMap errMap;
    return errMap;
  }

public:

  static std::string GetErrorString(int value)
  {
    ErrorMap::iterator found = GetErrorMap().find(value);
    if (found == GetErrorMap().end())
    {
      assert(false);
      return "";
    }
    else
    {
      return found->second;
    }
  }
};

int main()
{

  std::cout << "hello test" << endl;
  const char* filePath = "D:/WorkSpace/GraduationProject/2020graduationprojectqijiabao/paper_analysis/paper_analysis/data/label_dict.json";
  // 读取文件中的数据
  std::ifstream ifs; // 创建一个 std::ifstream 对象
  ifs.open(filePath, ios::in || ios::binary);
  if (!ifs.is_open())
  {
    std::cout << "Error: open file is failed! " << endl;
  }
  else
  {
    std::cout << "Successful: file read is success! " << endl;
  }
  Json::Value root;
  Json::Reader reader = Json::Reader(Json::Features::strictMode());
  std::unique_ptr<Json::Reader> jsonReader = std::make_unique<Json::Reader>(Json::Features::strictMode());
  // 使用std::make_unique函数来创建一个std::unique_ptr对象
  if (!jsonReader) {
    std::cerr << "jsonRead is null" << std::endl;
    return -1;
  }
  // reader将Json字符串解析到root，root将包含Json里所有子元素
  bool ret = jsonReader->parse(ifs, root);
  if (!ret) {
    std::cout << "parseJsonFromString error!" << std::endl;
    return -1;
  }
  //Json::StreamWriterBuilder builder;
  //builder["emitUTF8"] = true;
  //std::string str;
  //str = Json::writeString(builder, root["document"]["Attribute"]);

  //cout << str << endl;
  //Json::Value value = root["document"]["Attribute"];

  //Json::StyledWriter swriter;
  //str = swriter.write(value);

  //std::cout << str << endl;

  qi::CTranslationLabel translationLabel;
  translationLabel.loadFile(filePath);
  /*std::string labelDescription = translationLabel.getLabelDescription("background", "Attribute");
  cout << labelDescription << endl;
  labelDescription = translationLabel.getLabelDescription("background", "Attribute1");
  cout << labelDescription << endl;
  labelDescription = translationLabel.getLabelDescription("background1", "Attribute");
  cout << labelDescription << endl;*/
  Json::StreamWriterBuilder builder;
  builder["emitUTF8"] = true;
  std::string str;
  Json::Value root1;
  root1 = translationLabel.getLabelAttribute("bottom", "Description");
  str = Json::writeString(builder, root1);
  cout << str << endl;

 /* root1 = translationLabel.getLabelAttributeValue("bottom", "Attribute","val");
  str = Json::writeString(builder, root1);
  cout << str << endl;*/
  cout << "-------------------------------------------\n";
  str = translationLabel.getLabelAttributeDescription("bottom", "Description", "single");
  cout << str << endl;
  
  return 0;
}


#if 0

#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>

#define XMLFILE "D:/WorkSpace/VSCodeFile/word/documentcopy.xml"
// #define XMLFILE "D:/WorkSpace/VSCodeFile/word/core.xml"
//#define XMLFILE "D:/WorkSpace/VSCodeFile/word/Test04/word/document.xml"
#define FGDOMNS true

#define W_Body_TAG "w:body"
#define W_P_TAG "w:p"
#define W_R_TAG "w:r"
#define W_T_TAG "w:t"
#define W_TAB_TAG "w:tab"
#define W_BR_TAG "w:br"
#define W_PPR_TAG "w:pPr"
#define W_RPR_TAG "w:rPr"
#define W_SZ_TAG "w:sz"
#define W_SZCS_TAG "w:szCs"
#define W_COLOR_TAG "w:color"
#define W_VAL_TAG "w:val"
#define W_SECTPR_TAG "w:sectPr"

//#define W_Body_TAG "bookstore"
//#define W_P_TAG "book"

XERCES_CPP_NAMESPACE::DOMElement* findBodyTag(XERCES_CPP_NAMESPACE::DOMElement* root)
{
  if (root == 0)
  {
    return 0;
  }
  char* transcodeStr = XERCES_CPP_NAMESPACE::XMLString::transcode(root->getTagName());
  if (XERCES_CPP_NAMESPACE::XMLString::compareString(transcodeStr, W_Body_TAG) == 0)
  {
    XERCES_STD_QUALIFIER cout << "find body tag:" << transcodeStr << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&transcodeStr);
    return root;
  }
  else
  {
    XERCES_STD_QUALIFIER cout << "!!!now find tag:!!!" << transcodeStr << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&transcodeStr);
    if (0 == root->getChildElementCount() && nullptr == root->getNextElementSibling())
      return 0;
    if (root->getChildElementCount())
      return findBodyTag(root->getFirstElementChild());
    if (root->getNextElementSibling())
      return findBodyTag(root->getNextElementSibling());
  }
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
void printTagAnalysis(XERCES_CPP_NAMESPACE::DOMElement* root)
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
void ergodicTagAnalysis(XERCES_CPP_NAMESPACE::DOMElement* root)
{
  if (root == 0)
  {
    return;
  }
  if (0 == root->getChildElementCount())
  {
    printTagAnalysis(root);
    if (0 == root->getNextElementSibling())
      return;
    else
      ergodicTag(root->getNextElementSibling());
  }
  else
  {
    printTagAnalysis(root);
    ergodicTag(root->getFirstElementChild());
    if (0 == root->getNextElementSibling())
      return;
    else
      ergodicTag(root->getNextElementSibling());
  }
}
int main()
{
  // Initialize the XML4C2 system.
  try
  {
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
  }

  catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
      << "  Exception message:"
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return 1;
  }
  XMLCh* gLS = XERCES_CPP_NAMESPACE::XMLString::transcode("LS");
  // static const XMLCh gLS[] = { XERCES_CPP_NAMESPACE::chLatin_L, XERCES_CPP_NAMESPACE::chLatin_S, XERCES_CPP_NAMESPACE::chNull };
  XERCES_CPP_NAMESPACE::DOMImplementationLS* impl = XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation(gLS);
  XERCES_CPP_NAMESPACE::XMLString::release(&gLS);
  XERCES_CPP_NAMESPACE::DOMLSParser* parser = impl->createLSParser(XERCES_CPP_NAMESPACE::DOMImplementationLS::MODE_SYNCHRONOUS, NULL);
  XERCES_CPP_NAMESPACE::DOMConfiguration* config = parser->getDomConfig();
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMNamespaces, FGDOMNS);
  // enable datatype normalization - default is off
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMDatatypeNormalization, true);
  // And create our error handler and install it
  XERCES_CPP_NAMESPACE::ErrorHandler* errHandler = new XERCES_CPP_NAMESPACE::HandlerBase();
  config->setParameter(XERCES_CPP_NAMESPACE::XMLUni::fgDOMErrorHandler, errHandler);
  //reset error count first
  errHandler->resetErrors();
  XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* doc = nullptr;
  unsigned long duration = 0;
  try
  {
    // reset document pool
    parser->resetDocumentPool();

    const unsigned long startMillis = XERCES_CPP_NAMESPACE::XMLPlatformUtils::getCurrentMillis();
    doc = parser->parseURI(XMLFILE);
    const unsigned long endMillis = XERCES_CPP_NAMESPACE::XMLPlatformUtils::getCurrentMillis();
    duration = endMillis - startMillis;
  }
  catch (const XERCES_CPP_NAMESPACE::OutOfMemoryException&)
  {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    return -1;
  }
  catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "An error occurred during parsing\n   Message: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
    std::cerr << "An error occurred during parsing\n   Message: "
      << pMsg;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  catch (...)
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during parsing\n " << XERCES_STD_QUALIFIER endl;
    return -1;
  }

  XERCES_CPP_NAMESPACE::DOMElement* root = nullptr;

  if (doc)
  {
    //char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(doc->getElementsByTagName);
    //XERCES_STD_QUALIFIER cout << "Parsed file: " << pMsg << XERCES_STD_QUALIFIER endl;
    //XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    unsigned int elementCount = 0;
    root = doc->getDocumentElement();
    if (root)
      elementCount = root->getChildElementCount();
    else
      XERCES_STD_QUALIFIER cerr << "can not find root element" << XERCES_STD_QUALIFIER endl;
    XERCES_STD_QUALIFIER cout << "Parsed file in " << duration << " ms (" << elementCount << " elements)." << XERCES_STD_QUALIFIER endl;

  }

  /*XERCES_CPP_NAMESPACE::DOMElement* bodyTag = findBodyTag(root);
   if (bodyTag == 0)
   {
     XERCES_STD_QUALIFIER cerr << "can not find body tag" << XERCES_STD_QUALIFIER endl;
     return -1;
   }
   XMLCh* transcodeStrW_Body_TAG = XERCES_CPP_NAMESPACE::XMLString::transcode(W_Body_TAG);
   XERCES_CPP_NAMESPACE::DOMNodeList* bodyList = root->getElementsByTagName(transcodeStrW_Body_TAG);
   XERCES_CPP_NAMESPACE::XMLString::release(&transcodeStrW_Body_TAG);
   size_t length = bodyList->getLength();
   std::cout << "Hello World!\n" << length << std::endl;
   XMLCh* transcodeStrW_P_TAG = XERCES_CPP_NAMESPACE::XMLString::transcode(W_P_TAG);
   XERCES_CPP_NAMESPACE::DOMNodeList* pList = root->getElementsByTagName(transcodeStrW_P_TAG);
   XERCES_CPP_NAMESPACE::XMLString::release(&transcodeStrW_P_TAG);
   length = pList->getLength();
   std::cout << "Hello World!\n" << length << std::endl;*/

   // 遍历XML文档
  ergodicTag(root);
  const char* gXPathExpression = "//w:background";
  XMLCh* xpathStr = XERCES_CPP_NAMESPACE::XMLString::transcode(gXPathExpression);
  try
  {
    char* pMsg = nullptr;
    XMLCh* nsURI = XERCES_CPP_NAMESPACE::XMLString::transcode("http://www.w3.org/XML/1998/namespace");
    XERCES_CPP_NAMESPACE::DOMXPathNSResolver* resolver = doc->createNSResolver(root);
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

    XERCES_CPP_NAMESPACE::DOMXPathResult* result = doc->evaluate(
      xpathStr,
      root,
      resolver,
      XERCES_CPP_NAMESPACE::DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,
      NULL);

    XMLSize_t nLength = result->getSnapshotLength();
    for (XMLSize_t i = 0; i < nLength; i++)
    {
      result->snapshotItem(i);
      printTag(result->getNodeValue());
    }

    result->release();
    resolver->release();
  }
  catch (const XERCES_CPP_NAMESPACE::DOMXPathException& e)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(e.getMessage());
    XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
      << XERCES_STD_QUALIFIER endl
      << pMsg << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  catch (const XERCES_CPP_NAMESPACE::DOMException& e)
  {
    char* pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(e.getMessage());
    XERCES_STD_QUALIFIER cerr << "An error occurred during processing of the XPath expression. Msg is:"
      << XERCES_STD_QUALIFIER endl
      << pMsg << XERCES_STD_QUALIFIER endl;
    XERCES_CPP_NAMESPACE::XMLString::release(&pMsg);
    return -1;
  }
  XERCES_CPP_NAMESPACE::XMLString::release(&xpathStr);

  parser->release();

  delete errHandler;

  // And call the termination method
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();

  return 0;
}

#endif

#if 0
#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <string>
#include <vector>


using namespace xercesc;
using namespace std;
#define STUDENTS_TAG  "Students"
#define STUDENT_TAG   "Student"
#define NAME_TAG      "Name"
#define AGE_TAG       "Age"
#define SEX_TAG       "Sex"

struct Student {
  string  Name;
  int     Age;
  string  Sex;
};

enum ErrorCode
{
  LACK_BEGIN = 1,     // 缺少<Students>标记
  LACK_NAME = 2,     // 缺少姓名
  LACK_AGE = 3,     // 缺少年龄
  LACK_SEX = 4      // 缺少性别
};

DOMElement* findStudentsTag(DOMElement* root)
{
  if (root == 0)
    return 0;
  if (XMLString::compareString(XMLString::transcode(root->getTagName()), STUDENTS_TAG) == 0)
  {
    cout << "find students tag:" << XMLString::transcode(root->getTagName()) << endl;
    return root;
  }
  else
  {
    return findStudentsTag(root->getNextElementSibling());
  }
}

int visitDom2GetStudents(DOMElement* root, vector<Student>& students)
{
  DOMElement* stustag = findStudentsTag(root);
  if (stustag == 0)
    return LACK_BEGIN;
  DOMNodeList* stulist = root->getElementsByTagName(XMLString::transcode(STUDENT_TAG));
  size_t length = stulist->getLength();
  for (size_t index = 0; index < length; ++index)
  {
    DOMElement* elems = dynamic_cast<DOMElement*>(stulist->item(index));
    DOMElement* name = elems->getFirstElementChild();
    Student stu;
    if (name == 0)
      return LACK_NAME;
    if (XMLString::compareString(XMLString::transcode(name->getTagName()), NAME_TAG) == 0)
    {
      DOMNode* n = dynamic_cast<DOMNode*>(name);
      stu.Name = static_cast<string>(XMLString::transcode(n->getTextContent()));
    }
    else
      return LACK_NAME;

    DOMElement* age = name->getNextElementSibling();
    if (age == 0)
      return LACK_AGE;
    if (XMLString::compareString(XMLString::transcode(age->getTagName()), AGE_TAG) == 0)
    {
      DOMNode* n = dynamic_cast<DOMNode*>(age);
      stu.Age = atoi(XMLString::transcode(n->getTextContent()));
    }
    else
      return LACK_AGE;
    DOMElement* sex = age->getNextElementSibling();
    if (sex == 0)
    {
      return LACK_SEX;
    }
    if (XMLString::compareString(XMLString::transcode(sex->getTagName()), SEX_TAG) == 0)
    {
      DOMNode* n = dynamic_cast<DOMNode*>(sex);
      stu.Sex = static_cast<string>(XMLString::transcode(n->getTextContent()));
    }
    else
      return LACK_SEX;
    students.emplace_back(stu);
  }
  return 0;
}

int main()
{
  // Initialize the XML4C2 system.
  try
  {
    XMLPlatformUtils::Initialize();
  }

  catch (const XMLException& toCatch)
  {
    char* pMsg = XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
      << "  Exception message:"
      << pMsg;
    XMLString::release(&pMsg);
    return 1;
  }
  XercesDOMParser* parser = new XercesDOMParser();
  ErrorHandler* errHandler = new HandlerBase();
  parser->setErrorHandler(errHandler);
  try
  {
    parser->parse("test.xml");
  }
  catch (const OutOfMemoryException&)
  {
    XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    return -1;
  }
  catch (const XMLException& toCatch)
  {
    std::cerr << XMLString::transcode(toCatch.getMessage());
    return -1;
  }
  catch (const DOMException& toCatch)
  {
    std::cerr << XMLString::transcode(toCatch.getMessage());
    return -1;
  }
  catch (const SAXException& toCatch)
  {
    std::cerr << XMLString::transcode(toCatch.getMessage());
    return -1;
  }
  catch (...)
  {
    XERCES_STD_QUALIFIER cerr << "An error occurred during parsing\n " << XERCES_STD_QUALIFIER endl;
    return -1;
  }
  DOMDocument* doc = parser->getDocument();
  DOMElement* root = doc->getDocumentElement();
  vector<Student> students;
  int ret = visitDom2GetStudents(root, students);
  if (ret != 0)
    std::cerr << "Parse error\n";
  else
  {
    for (auto stu : students)
    {
      std::cout << "Name: " << stu.Name << "\n"
        << " Age: " << stu.Age << "\n"
        << " Sex: " << stu.Sex << "\n";
    }
  }
  doc->release();
  XMLPlatformUtils::Terminate();
  return 0;
}
#endif
