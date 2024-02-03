#include <xercesc/dom/DOMXPathEvaluator.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMDocument.hpp>

int main() {
  XERCES_CPP_NAMESPACE::DOMNode* parentElement = nullptr;
  XERCES_CPP_NAMESPACE::DOMXPathEvaluator *evaluator = parentElement->getOwnerDocument()->createDOMXPathEvaluator();
}
