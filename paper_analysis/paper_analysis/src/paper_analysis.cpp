#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/util/TransService.hpp>

#include "paper_analysis.h"

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

void analysisLabel(XERCES_CPP_NAMESPACE::DOMElement* root)
{
	
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

	// analysisLabel(root);

	const char* gXPathExpression = "//w:p";
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
			// XERCES_STD_QUALIFIER cout << XERCES_CPP_NAMESPACE::TranscodeToStr(result->getNodeValue()->getNodeName(), "ascii").str() << XERCES_STD_QUALIFIER endl;
			// XERCES_STD_QUALIFIER cout << XERCES_CPP_NAMESPACE::TranscodeToStr(result->getNodeValue()->getChildNodes()->item(3)->getNodeName(), "ascii").str() << XERCES_STD_QUALIFIER endl;
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
