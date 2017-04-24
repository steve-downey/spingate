// litmus_tests.h                                                     -*-C++-*-
#ifndef INCLUDED_LITMUS_TESTS
#define INCLUDED_LITMUS_TESTS

#include <atomic>
#include <tuple>

namespace litmus {

class MP { // Message Passing
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int> Result;
    MP() : x_(0), y_(0) {}
    void t1() {
        x_.store(1, std::memory_order_relaxed);
        y_.store(1, std::memory_order_relaxed);
    }
    void t2(Result& read) {
        while (!y_.load(std::memory_order_relaxed)){}
        std::get<0>(read) = x_.load(std::memory_order_relaxed);
    }

    auto actions() {
        return std::make_tuple(
            [this]() {
                t1();
            },
            [this](Result& result) {
                t2(result);
            });
    }
};

class SB { // Store Buffering
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int, int> Result;
    SB() : x_(0), y_(0) {}
    void t1(Result& read) {
        std::get<0>(read) = x_.load(std::memory_order_relaxed);
        y_.store(1, std::memory_order_relaxed);
    }
    void t2(Result& read) {
        std::get<1>(read) = y_.load(std::memory_order_relaxed);
        x_.store(1, std::memory_order_relaxed);
    }

    auto actions() {
        return std::make_tuple(
            [this](Result& result) {
                t1(result);
            },
            [this](Result& result) {
                t2(result);
            });
    }
};


class LB { // Load Buffering
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int, int> Result;
    LB() : x_(0), y_(0) {}
    void t1(Result& read) {
        y_.store(1, std::memory_order_relaxed);
        std::get<0>(read) = x_.load(std::memory_order_relaxed);
    }
    void t2(Result& read) {
        x_.store(1, std::memory_order_relaxed);
        std::get<1>(read) = y_.load(std::memory_order_relaxed);
    }

    auto actions() {
        return std::make_tuple(
            [this](Result& result) {
                t1(result);
            },
            [this](Result& result) {
                t2(result);
            });
    }
};


class IRIW { // Independent Reads of Independent Writes
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int, int, int, int> Result;

    IRIW() : x_(0), y_(0) {}
    void t1() {
        x_.store(1, std::memory_order_relaxed);
    }

    void t2() {
        y_.store(1, std::memory_order_relaxed);
    }

    void t3(Result& read) {
        std::get<0>(read) = x_.load(std::memory_order_relaxed);
        std::get<1>(read) = y_.load(std::memory_order_relaxed);
    }

    void t4(Result& read) {
        std::get<2>(read) = y_.load(std::memory_order_relaxed);
        std::get<3>(read) = x_.load(std::memory_order_relaxed);
    }

    auto actions() {
        return std::make_tuple(
            [this]() {
                t1();
            },
            [this]() {
                t2();
            },
            [this](Result& read) {
                t3(read);
            },
            [this](Result& read) {
                t4(read);
            });
    }
};


}  // close namespace litmus

#endif
