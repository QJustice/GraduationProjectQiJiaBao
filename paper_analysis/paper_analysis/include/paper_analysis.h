#include <map>
#include <thread>
#include <mutex>
#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "error_code.h"
#include "translation_label.h"
#include "singal_mutex.h"

#ifndef PAPER_ANALYSIS_PAPER_ANALYSIS_H
#define PAPER_ANALYSIS_PAPER_ANALYSIS_H



namespace qi {


class CPaperAnalysis
{
 public:
   CPaperAnalysis();
  ~CPaperAnalysis();
  // 创建解析子线程
  qierr::error_code createAnalysisThread(qi::CTranslationLabel* translation_lable, char const* xml_file_path);
  qierr::error_code analysisDocxFile(qi::CTranslationLabel* translation_lable, char const* docx_file_path);

private:
  CSingalMutex mutexs_;  // 信号量
  bool over_tasks;      // 任务是否完成
  bool over_singal;     // 结束信号
  char communicationSpace_[1024];  // 通信空间
  XERCES_STD_QUALIFIER vector<XERCES_STD_QUALIFIER thread> threads_;    // 线程池
  XERCES_STD_QUALIFIER map<std::string, XERCES_CPP_NAMESPACE::DOMElement*> results_;  // 保存解析结果的Map
};

} // namespace qi

#endif //PAPER_ANALYSIS_PAPER_ANALYSIS_H
