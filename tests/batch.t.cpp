#include "batch.h"

#include "gtest/gtest.h"

using ::testing::Test;

namespace testing {

namespace {
}

class BatchTest : public Test {
  protected:
    virtual void SetUp() {
        called = 0;
    }

    virtual void TearDown() {
    }

    void incrementCalled() {
        called += 1;
    }

    std::atomic<unsigned int> called;
};

TEST_F(BatchTest, breathingTest)
{
    Batch batch;
    batch.run();
}

TEST_F(BatchTest, run1Test)
{
    Batch batch;
    batch.add([this](){incrementCalled();});

    EXPECT_EQ(0u, called);

    batch.run();

    EXPECT_EQ(1u, called);
}

TEST_F(BatchTest, run10Test)
{
    Batch batch;
    for(int i = 0; i < 10; ++i) {
        batch.add([this](){incrementCalled();});
    }

    EXPECT_EQ(0u, called);

    batch.run();

    EXPECT_EQ(10u, called);
}

TEST_F(BatchTest, run100Test)
{
    Batch batch;
    for(int i = 0; i < 100; ++i) {
        batch.add([this](){incrementCalled();});
    }

    EXPECT_EQ(0u, called);

    batch.run();

    EXPECT_EQ(100u, called);
}


}
