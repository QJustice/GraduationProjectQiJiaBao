#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_USE

class CParagraphProperties {
public:
    CParagraphProperties(const char* xmlFilePath) : xmlFilePath(xmlFilePath) {}

    void parseXmlFile() {
        try {
            XMLPlatformUtils::Initialize();
            XercesDOMParser parser;
            parser.setValidationScheme(XercesDOMParser::Val_Always);
            parser.parse(xmlFilePath);

            DOMDocument* xmlDoc = parser.getDocument();
            if (xmlDoc != nullptr) {
                DOMElement* rootElement = xmlDoc->getDocumentElement();
                processNode(rootElement);
            }
        } catch (const XMLException& e) {
            char* message = XMLString::transcode(e.getMessage());
            std::cerr << "Error during initialization! :\n"
                      << message << std::endl;
            XMLString::release(&message);
        }
        XMLPlatformUtils::Terminate();
    }

private:
    const char* xmlFilePath;

    void processNode(DOMElement* node) {
        if (node == nullptr) {
            return;
        }

        std::cout << "Element: " << XMLString::transcode(node->getTagName()) << std::endl;

        // Process attributes
        DOMNamedNodeMap* attributes = node->getAttributes();
        const XMLSize_t attributeCount = attributes->getLength();

        for (XMLSize_t i = 0; i < attributeCount; ++i) {
            DOMNode* attributeNode = attributes->item(i);
            const XMLCh* attributeName = attributeNode->getNodeName();
            const XMLCh* attributeValue = attributeNode->getNodeValue();

            std::cout << "  Attribute: " << XMLString::transcode(attributeName)
                      << " = " << XMLString::transcode(attributeValue) << std::endl;
        }

        // Process child nodes
        DOMNodeList* children = node->getChildNodes();
        const XMLSize_t childCount = children->getLength();

        for (XMLSize_t i = 0; i < childCount; ++i) {
            DOMNode* child = children->item(i);
            if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
                processNode(dynamic_cast<DOMElement*>(child));
            }
        }
    }
};

int main() {
    const char* xmlFilePath = R"(yD:\WorkSpace\GraduationProject\2020graduationprojectqijiabao\paper_analysis\paper_analysis\test\ParagraphPropertiesTest\file.xml)";
    CParagraphProperties paragraphProperties(xmlFilePath);
    paragraphProperties.parseXmlFile();

    return 0;
}
