#include "experiment.h"

#include "gtest/gtest.h"

#include "litmus_tests.h"

#include <tupleutil.h>

using ::testing::Test;

namespace testing {

TEST(ExperimentTest, BreathTest1)
{
    using Test = litmus::Breath1;
    Experiment<Test> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, BreathTest2)
{
    using Test = litmus::Breath2;
    Experiment<Test> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, SBTest1)
{
    using Test = litmus::SB;
    Experiment<Test> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, MPaTest1)
{
    using Test = litmus::MPa;
    Experiment<Test> exp;
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
    using Test = litmus::MP;
    Experiment<Test> exp;
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
    using Test = litmus::IRIW;
    Experiment<Test> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

TEST(ExperimentTest, LBTest1)
{
    using Test = litmus::LB;
    Experiment<Test> exp;
    exp.run(2000000);

    for(auto result : exp.resultMap_)
    {
        std::cout << '(' ;
        tupleutil::print(std::cout, result.first);
        std::cout << ") : " << result.second << "\n";
    }

}

}
