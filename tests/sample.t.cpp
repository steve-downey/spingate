#include "sample.h"

#include "gtest/gtest.h"

#include "litmus_tests.h"

#include "tupleutil.h"


#include <tuple>
#include <functional>
#include <new>

using ::testing::Test;

namespace testing {

class TestReadOrder {
    alignas(64) int x_;
    alignas(64) int y_;

  public:
    typedef std::tuple<int, int, int, int> Result;
    TestReadOrder() : x_(0), y_(0) {}
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



TEST(SampleTest, sampleTestRunSample)
{
    std::map<TestReadOrder::Result, int> resultMap;

    for (int i = 0; i < 20000; ++i) {
        Sample<TestReadOrder> sample;
        sample.run();
        resultMap[sample.result_]++;
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(SampleTest, sampleTestStoreBuffer)
{
    using litmus::SB;

    std::map<SB::Result, int> resultMap;

    for (int i = 0; i < 20000; ++i) {
        Sample<SB> sample;
        sample.run();
        resultMap[sample.result_]++;
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }
}

TEST(SampleTest, sampleTestGetters)
{
    std::map<TestReadOrder::Result, int> resultMap;

    for (int i = 0; i < 20000; ++i) {
        Sample<TestReadOrder> sample;
        sample.run(tupleutil::tuple_getters(sample.test_.actions()));
        resultMap[sample.result_]++;
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(SampleTest, sampleTestPermuteGetters)
{
    std::map<TestReadOrder::Result, int> resultMap;

    Sample<TestReadOrder> s;
    auto getters = tupleutil::tuple_getters(s.test_.actions());
    for (int i = 0; i < 20000; ++i) {
        Sample<TestReadOrder> sample;
        sample.run(getters);
        resultMap[sample.result_]++;
        std::next_permutation(getters.begin(), getters.end());
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(SampleTest, sampleTest2b)
{
    using litmus::SB;
    std::map<SB::Result, int> resultMap;

    Sample<SB> s;
    auto getters = tupleutil::tuple_getters(s.test_.actions());
    for (int i = 0; i < 20000; ++i) {
        Sample<SB> sample;
        sample.run(getters);
        resultMap[sample.result_]++;
        std::next_permutation(getters.begin(), getters.end());
    }

    for(auto result : resultMap)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

}
