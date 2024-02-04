#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_USE

int main()
{
  // 初始化Xerces-C++
  XMLPlatformUtils::Initialize();

  // 创建DOM解析器
  XercesDOMParser parser;

  // 设置解析器的选项，例如启用命名空间支持
  parser.setDoNamespaces(false);

  parser.setDoSchema(false);

  // 解析XML文件
  parser.parse("D:\\WorkSpace\\GraduationProject\\GraduationProjectQiJiaBao\\paper_analysis\\paper_analysis\\data\\Template\\Undergraduate\\test01.xml");

  // 获取文档对象
  DOMDocument* document = parser.getDocument();
  // 使用getElementById方法获取元素
  const XMLCh* elementId = XMLString::transcode("0");
  DOMElement* element = document->getElementById(elementId);

  if (element)
  {
    // 处理获取到的元素
    // 在这里可以对元素进行操作
  } else
  {
    // 未找到具有指定ID的元素
    std::cout << "Element with ID not found." << std::endl;
  }


  return 0;
}
