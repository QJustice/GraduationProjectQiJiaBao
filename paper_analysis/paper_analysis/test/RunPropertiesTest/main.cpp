//
// Created by qijiabao on 11/11/2023.
//

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include "run_properties.h"

XERCES_CPP_NAMESPACE_USE

int main() {
    const char* xmlFilePath = R"(D:\WorkSpace\GraduationProject\2020graduationprojectqijiabao\paper_analysis\paper_analysis\test\ParagraphPropertiesTest\file.xml)";

    try {
        XMLPlatformUtils::Initialize();
        XercesDOMParser parser;
        parser.parse(xmlFilePath);

        DOMDocument* xmlDoc = parser.getDocument();
        if (!xmlDoc) {
            std::cerr << "Empty XML document" << std::endl;
            return 1;
        }
        DOMNodeList* runPropertiesNodes = xmlDoc->getElementsByTagName(XMLString::transcode("w:rPr"));
        // 注意：根据实际的命名空间和标签名进行替换

        const XMLSize_t runPropertiesCount = runPropertiesNodes->getLength();
        for (XMLSize_t i = 0; i < runPropertiesCount; ++i) {
            DOMNode* runPropertiesNode = runPropertiesNodes->item(i);

            CRunProperties runProperties;
            runProperties.parseRunProperties(runPropertiesNode);

            // 将运行段属性保存为 JSON 字符串并打印
            std::cout << "JSON Format: " << runProperties.toJsonString() << std::endl;
        }
    } catch (const XMLException& e) {
        char* message = XMLString::transcode(e.getMessage());
        std::cerr << "Error parsing file: " << message << std::endl;
        XMLString::release(&message);
    } catch (const DOMException& e) {
        char* message = XMLString::transcode(e.getMessage());
        std::cerr << "DOM Error parsing file: " << message << std::endl;
        XMLString::release(&message);
    } catch (...) {
        std::cerr << "Unexpected Exception" << std::endl;
    }

    XMLPlatformUtils::Terminate();
    return 0;
}
