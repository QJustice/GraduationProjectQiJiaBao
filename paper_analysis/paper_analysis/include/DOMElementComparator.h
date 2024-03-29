//
// Created by qijiabao on 1/14/2024.
//
/*************************************************************************
 * @Project:     paper_analysis
 * @File:        DOMElementComparator.h
 * @Brief:       Brief description of the file
 * @Author:      qijiabao
 * @Contact:     Your Contact Information (e.g., email)
 * @Date:        1/14/2024
 * @Description: 
 *               This file is generated by CLion to provide a
 *               template for C/C++ source or header files. You can modify
 *               this template according to your project's needs.
 * @Note:        Additional notes or important points related to the file.
 * @License:     License information if applicable.
 * @Version:     Version number or other version information.
 * @TODO:        List of tasks or things to be done in the file (if any).
 * @Bug:         List of known issues or bugs (if any).
 * @IDE:         CLion
 ************************************************************************/
// Include necessary headers, if any

// Additional comments or code go here
#ifndef PAPER_ANALYSIS_DOMELEMENTCOMPARATOR_H
#define PAPER_ANALYSIS_DOMELEMENTCOMPARATOR_H

#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "ErrorCode.h"
namespace qi {

class DOMElementComparator {
public:
  DOMElementComparator();
  ~DOMElementComparator();
static ErrorCode::ErrorCodeEnum compareDOMElements(XERCES_CPP_NAMESPACE::DOMElement* element1, XERCES_CPP_NAMESPACE::DOMElement* element2, bool& result);
};

}// namespace qi

#endif//PAPER_ANALYSIS_DOMELEMENTCOMPARATOR_H
