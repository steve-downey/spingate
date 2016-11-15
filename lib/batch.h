// batch.h                                                            -*-C++-*-
#ifndef INCLUDED_BATCH
#define INCLUDED_BATCH

#include "spingate.h"

#include <functional>
#include <vector>
#include <thread>

class Batch
{
  public:
    using Task = std::function<void()>;

    void add(Task task);
    void run();

  private:
    std::vector<std::thread> workers_;
    SpinGate gate_;

};

void Batch::add(Task task)
{
    workers_.emplace_back([this, task]{
            gate_.wait();
            task();
        });
}

void Batch::run()
{
    gate_.open();
    for (auto& thr : workers_) {
        thr.join();
    }
}

#endif
