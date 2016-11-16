// spingate.h                                                       -*-C++-*-
#ifndef INCLUDED_SPINGATE
#define INCLUDED_SPINGATE

#include <atomic>
#include <thread>

class SpinGate {
    std::atomic_bool flag_;

  public:
    SpinGate();
    void wait();
    void open();
};

inline SpinGate::SpinGate() {
    // Close the gate
    flag_.store(true, std::memory_order_release);
}

inline void SpinGate::wait() {
    while (flag_.load(std::memory_order_acquire))
        ; // spin
}

inline void SpinGate::open() {
    flag_.store(false, std::memory_order_release);
    std::this_thread::yield();
}

#endif
