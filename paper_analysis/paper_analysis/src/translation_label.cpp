#include "translation_label.h"

#include <iostream>

#include <json/json.h>

qi::CTranslationLabel::CTranslationLabel()
{
  this->root_ptr_ = nullptr;
  this->reader_ptr_ = nullptr;

  this->reader_ptr_ = new Json::Reader(Json::Features::strictMode());
  if (!reader_ptr_)
  {
    std::cerr << "reader_ptr_ is null" << std::endl;
  }
}

qi::CTranslationLabel::~CTranslationLabel()
{
  if (this->root_ptr_)
  {
    delete this->root_ptr_;
    this->root_ptr_ = nullptr;
  }
  if (this->reader_ptr_)
  {
    delete this->reader_ptr_;
    this->reader_ptr_ = nullptr;
  }
}
