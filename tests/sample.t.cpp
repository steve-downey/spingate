#include "sample.h"

#include "gtest/gtest.h"

#include <tuple>
#include <functional>
#include <new>

using ::testing::Test;

namespace testing {

class TestState {
    alignas(64) int x_;
    alignas(64) int y_;

  public:
    typedef std::tuple<int, int, int, int> Result;
    TestState() : x_(0), y_(0) {}
    void writer1() {
        y_ = 1;
        x_ = 1;
    }
    void reader1(Result& read) {
        std::get<0>(read) = x_;
        std::get<1>(read) = y_;
    }
    void reader2(Result& read) {
        std::get<2>(read) = y_;
        std::get<3>(read) = x_;
    }

    auto actions() {
        return std::make_tuple(
            [this]() {
                writer1();
            },
            [this](Result& result) {
                reader1(result);
            },
            [this](Result& result) {
                reader2(result);
            });
    }
};

class SB {
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

template <typename Func, typename Tuple, std::size_t... I>
void tuple_for_each_impl(Tuple const& tuple,
                         Func&&       f,
                         std::index_sequence<I...>) {
    auto swallow = {0, (std::forward<Func>(f)(I, std::get<I>(tuple)))...};
    (void)swallow;
}

template <typename Func, typename... Args>
void tuple_for_each(std::tuple<Args...> const& tuple, Func&& f) {
    tuple_for_each_impl(tuple, f, std::index_sequence_for<Args...>{});
}

template <typename... Args>
void print(std::ostream& os, std::tuple<Args...> const& tuple) {
    auto printer = [&os](auto i, auto el) {
        os << (i == 0 ? "" : ", ") << el;
        return 0;
    };
    return tuple_for_each(tuple, printer);
}

template <class State> class Sample {
    void add(size_t, std::function<void(void)> f){
        batch_.add(f);
    }

    void add(size_t, std::function<void(typename State::Result&)> f){
        batch_.add(f, std::ref(result_));
    }

    template <typename... Args>
    void add(std::tuple<Args...> const& tuple) {
        auto adder = [this](auto i, auto el) {
            this->add(i, el);
          return 0;
        };
        return tuple_for_each(tuple, adder);
    }

  public:
    Batch batch_;
    State state_;
    typename State::Result result_;

    Sample() : batch_(),
               state_(),
               result_()
    {}

    void run() {
        auto const& actions = state_.actions();
        add(actions);
        batch_.run();
    }
};


TEST(SampleTest, sampleTest1)
{
    std::map<TestState::Result, int> resultMap;

    for (int i = 0; i < 1000000; ++i) {
        Sample<TestState> sample;
        sample.run();
        resultMap[sample.result_]++;
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(SampleTest, sampleTest2)
{
    std::map<SB::Result, int> resultMap;

    for (int i = 0; i < 10000000; ++i) {
        Sample<SB> sample;
        sample.run();
        resultMap[sample.result_]++;
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }
}

}
