#include "sample.h"

#include "gtest/gtest.h"

#include <tuple>
#include <functional>

using ::testing::Test;

namespace testing {

class TestState {
    int x_;
    int y_;

  public:
    typedef std::tuple<int, int, int, int> Result;
    TestState() : x_(0), y_(0) {}
    void writer1() {
        y_ = 1;
        x_ = 1;
    }
    void writer2() {
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
            [this]() {
                writer2();
            },
            [this](Result& result) {
                reader1(result);
            },
            [this](Result& result) {
                reader2(result);
            });
    }
};

template <typename Func, typename Tuple, std::size_t... I>
void tuple_for_each(Tuple const& tuple, Func&& f, std::index_sequence<I...>) {
    int swallow[] = {0, (std::forward<Func>(f)(I, std::get<I>(tuple)))...};
    (void)swallow;
}

template <typename... Args>
void print(std::ostream& os, std::tuple<Args...> const& tuple) {
    auto printer = [&os](auto i, auto el) {
        os << (i == 0 ? "" : ", ") << el;
        return 0;
    };
    return tuple_for_each(tuple, printer, std::index_sequence_for<Args...>{});
}

template<class State>
class Sample {
    void add(std::function<void(void)> f){
        batch_.add(f);
    }

    void add(std::function<void(typename State::Result&)> f){
        batch_.add(f, std::ref(result_));
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
        add(std::get<0>(actions));
        add(std::get<1>(actions));
        add(std::get<2>(actions));
        add(std::get<3>(actions));
        batch_.run();
    }
};


TEST(SampleTest, sampleTest1)
{
    std::map<TestState::Result, int> resultMap;

    for (int i = 0; i < 10000; ++i) {
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

}
