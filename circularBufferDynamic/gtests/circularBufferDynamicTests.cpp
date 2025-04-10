
extern "C" {    
#include "circularBufferDynamic.h"
}
#include <gtest/gtest.h>
#include <cstring>

class circularBufferDynamicTest : public ::testing::Test {
protected:
    circularBufferDynamicList_t buffer;
    uint8_t dataBuffer[128]; // Example buffer for testing

    void SetUp() override {
        memset(dataBuffer, 0, sizeof(dataBuffer));
        circularBufferDynamicCreate(&buffer, dataBuffer, sizeof(uint8_t), sizeof(dataBuffer));
    }
};

// Test: Buffer Creation
TEST_F(circularBufferDynamicTest, CreateBuffer) {
    EXPECT_EQ(buffer.capacity, 127); // Capacity should be size - 1
    EXPECT_EQ(buffer.dataSize, 1);
    EXPECT_EQ(buffer.counter, 0);
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.get_index, 0);
    EXPECT_EQ(buffer.dataBuffer, dataBuffer);
}

// Test: Buffer Is Empty
TEST_F(circularBufferDynamicTest, IsEmpty) {
    EXPECT_TRUE(circularBufferDynamicIsEmpty(&buffer));
}

// Test: Buffer Is Full
TEST_F(circularBufferDynamicTest, IsFull) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        circularBufferDynamicPut(&buffer, &data);
    }
    EXPECT_TRUE(circularBufferDynamicIsFull(&buffer));
}

// Test: Put and Get Data
TEST_F(circularBufferDynamicTest, PutAndGet) {
    uint8_t input = 42;
    uint8_t output = 0;

    EXPECT_EQ(circularBufferDynamicPut(&buffer, &input), CBUFFER_STATUS_OK);
    EXPECT_FALSE(circularBufferDynamicIsEmpty(&buffer));
    EXPECT_EQ(circularBufferDynamicGet(&buffer, &output), CBUFFER_STATUS_OK);
    EXPECT_EQ(output, input);
    EXPECT_TRUE(circularBufferDynamicIsEmpty(&buffer));
}

// Test: Put Safe (Prevent Overwriting)
TEST_F(circularBufferDynamicTest, PutSafe) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        EXPECT_EQ(circularBufferDynamicPutSafe(&buffer, &data), CBUFFER_STATUS_OK);
    }
    uint8_t extraData = 99;
    EXPECT_EQ(circularBufferDynamicPutSafe(&buffer, &extraData), CBUFFER_STATUS_FULL);
}

// Test: Get from Empty Buffer
TEST_F(circularBufferDynamicTest, GetFromEmpty) {
    uint8_t output = 0;
    EXPECT_EQ(circularBufferDynamicGet(&buffer, &output), CBUFFER_STATUS_EMPTY);
}

// Test: Reset Buffer
TEST_F(circularBufferDynamicTest, ResetBuffer) {
    uint8_t data = 42;
    circularBufferDynamicPut(&buffer, &data);
    EXPECT_FALSE(circularBufferDynamicIsEmpty(&buffer));

    EXPECT_EQ(circularBufferDynamicReset(&buffer), CBUFFER_STATUS_OK);
    EXPECT_TRUE(circularBufferDynamicIsEmpty(&buffer));
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.get_index, 0);
    EXPECT_EQ(buffer.counter, 0);
}