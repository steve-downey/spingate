#include "spingate.h"

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    std::vector<std::thread> workers;
    SpinGate                 gate;
    using time_point =
        std::chrono::time_point<std::chrono::high_resolution_clock>;
    time_point              t1;
    auto                    threadCount = std::thread::hardware_concurrency();
    std::vector<time_point> times;
    times.resize(threadCount);

    for (size_t n = 0; n < threadCount; ++n) {
        workers.emplace_back([&gate, t1, &times, n] {
            gate.wait();
            time_point t2 = std::chrono::high_resolution_clock::now();
            times[n]      = t2;
        });
    }

    std::cout << "Open the gate in 1 second: " << std::endl;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    t1 = std::chrono::high_resolution_clock::now();
    gate.open();

    for (auto& thr : workers) {
        thr.join();
    }

    int threadNum = 0;
    for (auto& time : times) {
        auto diff =
            std::chrono::duration_cast<std::chrono::nanoseconds>(time - t1);
        std::cout << "Thread " << threadNum++ << " waited " << diff.count()
                  << "ns\n";
    }
}
