
extern "C" {    
#include "circularBufferStatic.h"
}
#include <gtest/gtest.h>
#include <cstring>

class CircularBufferTest : public ::testing::Test {
protected:
    circularBufferList_t buffer;
    uint8_t dataBuffer[128]; // Example buffer for testing

    void SetUp() override {
        memset(dataBuffer, 0, sizeof(dataBuffer));
        circularBufferCreate(&buffer, dataBuffer, sizeof(uint8_t), sizeof(dataBuffer));
    }
};

// Test: Buffer Creation
TEST_F(CircularBufferTest, CreateBuffer) {
    EXPECT_EQ(buffer.capacity, 127); // Capacity should be size - 1
    EXPECT_EQ(buffer.dataSize, 1);
    EXPECT_EQ(buffer.counter, 0);
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.get_index, 0);
    EXPECT_EQ(buffer.dataBuffer, dataBuffer);
}

// Test: Buffer Is Empty
TEST_F(CircularBufferTest, IsEmpty) {
    EXPECT_TRUE(circularBufferIsEmpty(&buffer));
}

// Test: Buffer Is Full
TEST_F(CircularBufferTest, IsFull) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        circularBufferPut(&buffer, &data);
    }
    EXPECT_TRUE(circularBufferIsFull(&buffer));
}

// Test: Put and Get Data
TEST_F(CircularBufferTest, PutAndGet) {
    uint8_t input = 42;
    uint8_t output = 0;

    EXPECT_EQ(circularBufferPut(&buffer, &input), CBUFFER_STATUS_OK);
    EXPECT_FALSE(circularBufferIsEmpty(&buffer));
    EXPECT_EQ(circularBufferGet(&buffer, &output), CBUFFER_STATUS_OK);
    EXPECT_EQ(output, input);
    EXPECT_TRUE(circularBufferIsEmpty(&buffer));
}

// Test: Put Safe (Prevent Overwriting)
TEST_F(CircularBufferTest, PutSafe) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        EXPECT_EQ(circularBufferPutSafe(&buffer, &data), CBUFFER_STATUS_OK);
    }
    uint8_t extraData = 99;
    EXPECT_EQ(circularBufferPutSafe(&buffer, &extraData), CBUFFER_STATUS_FULL);
}

// Test: Get from Empty Buffer
TEST_F(CircularBufferTest, GetFromEmpty) {
    uint8_t output = 0;
    EXPECT_EQ(circularBufferGet(&buffer, &output), CBUFFER_STATUS_EMPTY);
}

// Test: Reset Buffer
TEST_F(CircularBufferTest, ResetBuffer) {
    uint8_t data = 42;
    circularBufferPut(&buffer, &data);
    EXPECT_FALSE(circularBufferIsEmpty(&buffer));

    EXPECT_EQ(circularBufferReset(&buffer), CBUFFER_STATUS_OK);
    EXPECT_TRUE(circularBufferIsEmpty(&buffer));
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.get_index, 0);
    EXPECT_EQ(buffer.counter, 0);
}