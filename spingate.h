// spingate.h                                                       -*-C++-*-
#ifndef INCLUDED_SPINGATE
#define INCLUDED_SPINGATE

#include <atomic>

class Gate
{
    std::atomic_bool flag_;

  public:
    Gate();
    void wait();
    void open();
};


inline
Gate::Gate(){
    // Close the gate
    flag_.store(true, std::memory_order_release);
}

inline
void Gate::wait() {
    while (flag_.load(std::memory_order_acquire))
        ; // spin
}

inline
void Gate::open() {
    flag_.store(false, std::memory_order_release);
}


#endif
