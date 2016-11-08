// cvgate.h                                                           -*-C++-*-
#ifndef INCLUDED_CVGATE
#define INCLUDED_CVGATE

#include <mutex>
#include <condition_variable>
#include <atomic>

class CVGate
{
    std::mutex lock_;
    std::condition_variable cv_;
    bool flag_;

  public:
    CVGate();

    void wait();
    void open();
};

inline
CVGate::CVGate()
: lock_(),
  cv_(),
  flag_(true)
{}

inline
void CVGate::wait() {
    std::unique_lock<std::mutex> lk(lock_);
    cv_.wait(lk, [&](){return !flag_;});
}

inline
void CVGate::open() {
    std::unique_lock<std::mutex> lk(lock_);
    flag_ = false;
    cv_.notify_all();
}
#endif
