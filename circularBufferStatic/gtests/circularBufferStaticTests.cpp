#include <gtest/gtest.h>
#include <cstring>

extern "C" {    
#include "circularBufferStatic.h"
}
class CircularBufferTest : public ::testing::Test {
protected:
circularBuffStaticList_t buffer;
    uint8_t dataBuffer[128]; // Example buffer for testing

    void SetUp() override {
        memset(dataBuffer, 0, sizeof(dataBuffer));
        circularBuffStatic_create(&buffer, dataBuffer, sizeof(uint8_t), sizeof(dataBuffer));
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
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
}

// Test: Buffer Is Full
TEST_F(CircularBufferTest, IsFull) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        circularBuffStatic_put(&buffer, &data);
    }
    EXPECT_TRUE(circularBuffStatic_isFull(&buffer));
}

// Test: Put and Get Data
TEST_F(CircularBufferTest, PutAndGet) {
    uint8_t input = 42;
    uint8_t output = 0;

    EXPECT_EQ(circularBuffStatic_put(&buffer, &input), CBUFFER_STATUS_OK);
    EXPECT_FALSE(circularBuffStatic_isEmpty(&buffer));
    EXPECT_EQ(circularBuffStatic_get(&buffer, &output), CBUFFER_STATUS_OK);
    EXPECT_EQ(output, input);
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
}

// Test: Put Safe (Prevent Overwriting)
TEST_F(CircularBufferTest, PutSafe) {
    for (int i = 0; i < buffer.capacity; ++i) {
        uint8_t data = i;
        EXPECT_EQ(circularBuffStatic_putSafe(&buffer, &data), CBUFFER_STATUS_OK);
    }
    uint8_t extraData = 99;
    EXPECT_EQ(circularBuffStatic_putSafe(&buffer, &extraData), CBUFFER_STATUS_FULL);
}

// Test: Get from Empty Buffer
TEST_F(CircularBufferTest, GetFromEmpty) {
    uint8_t output = 0;
    EXPECT_EQ(circularBuffStatic_get(&buffer, &output), CBUFFER_STATUS_EMPTY);
}

// Test: Reset Buffer
TEST_F(CircularBufferTest, ResetBuffer) {
    uint8_t data = 42;
    circularBuffStatic_put(&buffer, &data);
    EXPECT_FALSE(circularBuffStatic_isEmpty(&buffer));

    EXPECT_EQ(circularBuffStatic_reset(&buffer), CBUFFER_STATUS_OK);
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.get_index, 0);
    EXPECT_EQ(buffer.counter, 0);
}