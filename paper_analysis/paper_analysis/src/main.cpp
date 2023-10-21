#include <iostream>

#include <xercesc/dom/DOM.hpp>

#include "paper_analysis.h"


int main()
{
  qi::CTranslationLabel translation_label;
  translation_label.loadFile("D:/WorkSpace/GraduationProject/2020graduationprojectqijiabao/paper_analysis/paper_analysis/data/label_dict.json");

  qi::CPaperAnalysis paper_analysis;
  paper_analysis.init();
  paper_analysis.loadXMLFile("D:/WorkSpace/VSCodeFile/word/documentcopy.xml");
  paper_analysis.analysisXMLFile(&translation_label);
  //paper_analysis.getDomElement(root);
  //paper_analysis.getBodyElement(body);
  //paper_analysis.printLableProperties(dynamic_cast<XERCES_CPP_NAMESPACE::DOMNode*>(body), &translation_label);
  //paper_analysis.XPathSearch("//w:rPr");

  paper_analysis.relese();
  return 0;
}
