// batch.h                                                            -*-C++-*-
#ifndef INCLUDED_BATCH
#define INCLUDED_BATCH

#include "spingate.h"

#include <functional>
#include <vector>
#include <thread>

class Batch {
  public:
    template <class Function, class... Args>
    void add(Function&& f, Args&&... args);

    void run();

  private:
    std::vector<std::thread> workers_;
    SpinGate                 gate_;
};

template <class Function, class... Args>
void Batch::add(Function&& f, Args&&... args) {
    workers_.emplace_back([ this, f = std::forward<Function>(f), args... ]() {
        gate_.wait();
        f(args...);
    });
}

inline
void Batch::run() {
    gate_.open();
    for (auto& thr : workers_) {
        thr.join();
    }
}

#endif
