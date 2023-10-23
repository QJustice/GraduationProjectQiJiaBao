#include <iostream>

#include <xercesc/dom/DOM.hpp>

#include "paper_analysis.h"
#include "translation_label.h"


int main()
{
  qi::CTranslationLabel translation_label;
  translation_label.loadFile("D:/WorkSpace/GraduationProject/2020graduationprojectqijiabao/paper_analysis/paper_analysis/data/label_dict.json");

  qi::CPaperAnalysis paper_analysis;
  paper_analysis.analysisDocxFile(&translation_label, "docx path");
  //paper_analysis.loadXMLFile("D:/WorkSpace/VSCodeFile/word/Test05/word/document.xml");
  //paper_analysis.analysisXMLFile(&translation_label);
  //paper_analysis.getDomElement(root);
  //paper_analysis.getBodyElement(body);
  //paper_analysis.printLableProperties(dynamic_cast<XERCES_CPP_NAMESPACE::DOMNode*>(body), &translation_label);
  //paper_analysis.XPathSearch("//w:rPr");

  return 0;
}
