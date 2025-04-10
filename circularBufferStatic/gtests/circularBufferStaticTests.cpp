#include <gtest/gtest.h>

// Dummy tests for the time being

namespace {
    int GetMeaningOfLife() { return 31; }
}

TEST(TestTopic, Triv)
{
    EXPECT_EQ(GetMeaningOfLife(), 1);
} 