#include "spingate.h"

#include "gtest/gtest.h"

using ::testing::Test;

namespace testing {

namespace {
}

class SpinGateTest : public Test {
  protected:
    virtual void SetUp() {
        called = 0;
    }

    virtual void TearDown() {
    }

    std::atomic<unsigned int> called;
};

TEST_F(SpinGateTest, breathingTest)
{
    SpinGate gate;
    gate.open();
}

TEST_F(SpinGateTest, waitTest)
{
    std::vector<std::thread> workers;
    SpinGate gate;
    auto threadCount = std::thread::hardware_concurrency();

    for (size_t n = 0; n < threadCount; ++n) {
        workers.emplace_back([this, &gate]{
                gate.wait();
                called += 1;
            });
    }

    EXPECT_EQ(0u, called);

    gate.open();

    for (auto& thr : workers) {
        thr.join();
    }

    EXPECT_EQ(threadCount, called);

}


}
