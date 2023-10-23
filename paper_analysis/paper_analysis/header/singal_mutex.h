#include <mutex>
#include <condition_variable>

#ifndef _SINGAL_MUTEX_H_
#define _SINGAL_MUTEX_H_


class CSingalMutex
{
public:
  CSingalMutex();
  ~CSingalMutex();

  std::mutex mutex_;
  std::mutex send_order_mutex_;
  std::mutex recv_order_mutex_;
  std::condition_variable cv;
  bool over_singal;

};

#endif
