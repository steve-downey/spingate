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

TEST_F(BatchTest, runArgTest)
{
    Batch batch;
    int i = 0;
    batch.add([&i](int k){ i = k;}, 1);

    EXPECT_EQ(i, 0);

    batch.run();

    EXPECT_EQ(i, 1);
}

TEST_F(BatchTest, runRefArgTest)
{
    Batch batch;
    int i = 0;
    batch.add([](int& k){ k = 2;}, std::ref(i));

    EXPECT_EQ(i, 0);

    batch.run();

    EXPECT_EQ(i, 2);
}

TEST_F(BatchTest, runRefArgTest2)
{
    Batch batch;
    int i = 0;
    batch.add([](int& k, int j){ k = j;}, std::ref(i), 3);

    EXPECT_EQ(0, i);

    batch.run();

    EXPECT_EQ(3, i);
}

std::string someString() {
    return std::string("four");
}

TEST_F(BatchTest, runRefArgTest3)
{
    Batch batch;
    int i = 0;
    batch.add([](int& k, std::string j){ k = j.length();}, std::ref(i), someString());

    EXPECT_EQ(0, i);

    batch.run();

    EXPECT_EQ(4, i);
}

}
