#include "paper_analysis.h"
#include "analysis_XML_file.h"
#include "translation_label.h"



qi::CPaperAnalysis::CPaperAnalysis()
{
  this->results_.clear();
  this->threads_.clear();
  memset(this->communicationSpace_, 0, sizeof(this->communicationSpace_));
}

qi::CPaperAnalysis::~CPaperAnalysis()
{
}

qierr::error_code qi::CPaperAnalysis::createAnalysisThread(qi::CTranslationLabel* translation_lable, char const* xml_file_path)
{
  //CAnalysisXMLFile analysisXMLFile;

  //std::cout << this->results_[this->communicationSpace_] << std::endl;
  std::unique_lock<std::mutex> lock(this->mutexs_.send_order_mutex_);
  while (true)
  {
    this->mutexs_.cv.wait(lock);
    //std::cout << this->results_[this->communicationSpace_] << std::endl;
    std::cout << "Thread ID ： " << std::this_thread::get_id() << " " << this->communicationSpace_ << std::endl;
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string mystring = ss.str();
    if (!strcmp(this->communicationSpace_, "exit")) {
      this->over_singal = true;
      this->mutexs_.cv.notify_all();
      break;
    }
    std::unique_lock<std::mutex> lock_com(this->mutexs_.mutex_);
    if (!strcmp(this->communicationSpace_, "comeon") && !this->over_tasks) {

      strcpy(this->communicationSpace_, ss.str().c_str());
      std::cout << this->communicationSpace_ << std::endl;
      this->over_tasks = true;
      this->mutexs_.cv.notify_all();
    }
    lock_com.unlock();

    //auto myid = std::this_thread::get_id();
    //std::stringstream ss;
    //ss << myid;
    //std::string mystring = ss.str();
    //strcpy(this->communicationSpace_, mystring.c_str());

    //std::cout << "Thread ID ： " << "new is " << this->communicationSpace_ << std::endl;
    // 向父亲程序发送消息
    // this->mutex_.cv.notify_all();
  }
  return qierr::error_code();
}

qierr::error_code qi::CPaperAnalysis::analysisDocxFile(qi::CTranslationLabel* translation_lable, char const* docx_file_path)
{
  CAnalysisXMLFile::init();
  std::vector<std::string> xmlFiles = { "D:/WorkSpace/VSCodeFile/word/Test08/word/document.xml", "D:/WorkSpace/VSCodeFile/word/Test08/word/footer1.xml", "D:/WorkSpace/VSCodeFile/word/Test08/word/settings.xml" };
  // std::vector<std::string> xmlFiles = { "D:/WorkSpace/VSCodeFile/word/Test08/word/document.xml" };
  qierr::error_code(qi::CPaperAnalysis:: * createAnalysisThreadFun)(qi::CTranslationLabel * translation_lable, char const* xml_file_path) = &qi::CPaperAnalysis::createAnalysisThread;

  for (std::string const& xmlFile : xmlFiles)
  {
    this->threads_.push_back(std::thread(createAnalysisThreadFun,this, translation_lable, xmlFile.c_str()));
  }
    this->over_tasks = true;
    this->over_singal = false;
  while (true)
  {
    std::cout << "\nEnter a command: ";
    std::cin >> this->communicationSpace_;
    this->over_tasks = false;
    this->mutexs_.cv.notify_all();
    std::unique_lock<std::mutex> lock(this->mutexs_.recv_order_mutex_);
    this->mutexs_.cv.wait_for(lock, std::chrono::seconds(3), [this]() { return this->over_tasks || this->over_singal; });
    
    if (this->over_singal)
    {
      break;
    }
    else if (this->over_tasks)
    {
      std::cout << "IN MAIN" << this->communicationSpace_ << std::endl;
      memset(this->communicationSpace_, 0, sizeof(this->communicationSpace_));
    }
    else
    {
      std::cout << "Timeout!" << std::endl;
    }
    /*
    while (true)
    {
      std::unique_lock<std::mutex> lock(this->mutex_.recv_order_mutex_);
      this->mutex_.cv.wait(lock);
      if (this->communicationSpace_ == "over")
      {
        std::cout << "over" << std::endl;
        std::cout << "Main Thread ID ： " << std::this_thread::get_id() << " " << this->communicationSpace_ << std::endl;
        break;
      }
      else {
        std::cin >> ord;
        std::this_thread::sleep_for(std::chrono::seconds(2));
      }
    }*/
  }

  for (std::thread& t : this->threads_) {
    t.join();
  }
  //CAnalysisXMLFile analysisXMLFile1;
  //CTranslationLabel translationLabel;
  //// 在Map中查找解析结果并打印
  //for (const auto& pair : this->results_) {
  //  // 打印进程id
  // // std::cout << "\nThread ID: " << std::this_thread::get_id();
  //  std::cout << "\nKey: " << pair.first << ", Value: " << pair.second << "num" << this->results_.size();
  //  std::cout << "\n";
  //  //if (pair.first == xml_file_path)
  //  analysisXMLFile1.printXMLInfo(pair.second, &translationLabel);
  //}
  CAnalysisXMLFile::relese();
  return qierr::E_OK;
}
