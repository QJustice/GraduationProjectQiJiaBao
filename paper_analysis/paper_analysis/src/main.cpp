#include <iostream>

#include <xercesc/dom/DOM.hpp>

#include "paper_analysis.h"


int main()
{
  XERCES_CPP_NAMESPACE::DOMElement* root = nullptr;
  XERCES_CPP_NAMESPACE::DOMElement* body = nullptr;
  
  qi::CTranslationLabel translation_label;
  translation_label.loadFile(DICTFILE);

  qi::CPaperAnalysis paper_analysis;
  paper_analysis.init();
  paper_analysis.loadXMLFile(XMLFILE);
  paper_analysis.getDomElement(root);
  paper_analysis.getBodyElement(body);
  paper_analysis.printLableProperties(dynamic_cast<XERCES_CPP_NAMESPACE::DOMNode*>(body), &translation_label);
  //paper_analysis.XPathSearch("//w:rPr");

  paper_analysis.relese();
  return 0;
}
