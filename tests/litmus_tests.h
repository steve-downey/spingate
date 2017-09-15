// litmus_tests.h                                                     -*-C++-*-
#ifndef INCLUDED_LITMUS_TESTS
#define INCLUDED_LITMUS_TESTS

#include <atomic>
#include <tuple>

namespace litmus {
class Breath1 {
    alignas(64) std::atomic<int> x_;
  public:
    typedef std::tuple<int> Result;
    Breath1();
    void t1(Result& read);

    auto actions() {
        return std::make_tuple(
            [this](Result& result) {
                t1(result);
            });
    }
};

class Breath2 {
    alignas(64) std::atomic<int> x_;
  public:
    typedef std::tuple<int> Result;
    Breath2();
    void t1();
    void t2(Result& read);

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

class MPa { // Message Passing
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int,int> Result;
    MPa();
    void t1();
    void t2(Result& read);

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

class MP { // Message Passing
    alignas(64) std::atomic<int> x_;
    alignas(64) std::atomic<int> y_;

  public:
    typedef std::tuple<int> Result;
    MP();
    void t1();
    void t2(Result& read);

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
    SB();
    void t1(Result& read);
    void t2(Result& read);

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
    LB();
    void t1(Result& read);
    void t2(Result& read);

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

    IRIW();

    void t1();

    void t2();

    void t3(Result& read);

    void t4(Result& read);

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
