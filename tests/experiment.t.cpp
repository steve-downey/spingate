#include "experiment.h"

#include "gtest/gtest.h"

#include "litmus_tests.h"

#include <tupleutil.h>

using ::testing::Test;

namespace testing {

TEST(ExperimentTest, SBTest1)
{
    using litmus::SB;
    Experiment<SB> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, MPTest1)
{
    using litmus::MP;
    Experiment<MP> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, IRIWTest1)
{
    using litmus::IRIW;
    Experiment<IRIW> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

}
