#include <gtest/gtest.h>
#include <cstring>

extern "C" {    
#include "circularBufferStatic.h"
}
class CircularBufferTest : public ::testing::Test {
protected:
    circularBuffStaticList_t buffer;
    uint8_t dataBuffer[7]; // Example buffer for testing

    void SetUp() override {
        memset(dataBuffer, 0, sizeof(dataBuffer));
        circularBuffStatic_create(&buffer, (void*)dataBuffer, sizeof(uint8_t), sizeof(dataBuffer));
    }
};

// Test: Buffer Creation
TEST_F(CircularBufferTest, CreateBuffer) {
    EXPECT_EQ(buffer.bufferSizeBytes, circularBuffStatic_capacity(&buffer) / buffer.dataSize);
    EXPECT_EQ(buffer.dataSize, 1);
    EXPECT_EQ(buffer.counter, 0);
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.pop_index, 0);
    EXPECT_EQ(buffer.dataBuffer, dataBuffer);
}

// Test: Buffer Is Empty
TEST_F(CircularBufferTest, IsEmpty) {
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
}

// Test: Buffer Is Full
TEST_F(CircularBufferTest, IsFull) {
    for (int i = 0; i < buffer.bufferSizeBytes; ++i) {
        uint8_t data = i;
        circularBuffStatic_put(&buffer, &data);
    }
    EXPECT_TRUE(circularBuffStatic_isFull(&buffer));
}

// Test: Put and Get Data
TEST_F(CircularBufferTest, PutAndPop) {
    uint8_t input = 42;
    uint8_t output = 0;

    EXPECT_EQ(circularBuffStatic_put(&buffer, &input), CBUFFER_STATUS_OK);
    EXPECT_FALSE(circularBuffStatic_isEmpty(&buffer));
    EXPECT_EQ(circularBuffStatic_pop(&buffer, &output), CBUFFER_STATUS_OK);
    EXPECT_EQ(output, input);
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
}

// Test: Put overflow
TEST_F(CircularBufferTest, PutOverflow) {
    uint8_t input[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t output[7] = {0};
    uint8_t expectedOutput[7] = {4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(circularBuffStatic_put(&buffer, &input[i]), CBUFFER_STATUS_OK);
    }
    EXPECT_TRUE(circularBuffStatic_isFull(&buffer));
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(circularBuffStatic_pop(&buffer, &output[i]), CBUFFER_STATUS_OK);
        EXPECT_EQ(output[i], expectedOutput[i]);
    }
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
}

// Test: Put Safe (Prevent Overwriting)
TEST_F(CircularBufferTest, PutSafe) {
    for (int i = 0; i < buffer.bufferSizeBytes; ++i) {
        uint8_t data = i;
        EXPECT_EQ(circularBuffStatic_putSafe(&buffer, &data), CBUFFER_STATUS_OK);
    }
    uint8_t extraData = 99;
    EXPECT_EQ(circularBuffStatic_putSafe(&buffer, &extraData), CBUFFER_STATUS_FULL);
}

// Test: Get from Empty Buffer
TEST_F(CircularBufferTest, GetFromEmpty) {
    uint8_t output = 0;
    EXPECT_EQ(circularBuffStatic_pop(&buffer, &output), CBUFFER_STATUS_EMPTY);
}

// Test: Reset Buffer
TEST_F(CircularBufferTest, ResetBuffer) {
    uint8_t data = 42;
    circularBuffStatic_put(&buffer, &data);
    EXPECT_FALSE(circularBuffStatic_isEmpty(&buffer));

    EXPECT_EQ(circularBuffStatic_reset(&buffer), CBUFFER_STATUS_OK);
    EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
    EXPECT_EQ(buffer.put_index, 0);
    EXPECT_EQ(buffer.pop_index, 0);
    EXPECT_EQ(buffer.counter, 0);
}


class CircularBufferLargeDataTest : public ::testing::Test {
    protected:
        #define BUFFER_SIZE 20
        #define BUFFER_DATA_SIZE sizeof(uint32_t)
        circularBuffStaticList_t buffer;
        uint32_t dataBuffer[BUFFER_SIZE]; // Example buffer for testing
    
        void SetUp() override {
            memset(dataBuffer, 0, sizeof(dataBuffer));
            circularBuffStatic_create(&buffer, (void*)dataBuffer, sizeof(uint32_t), sizeof(dataBuffer));
        }
    };
    
    // Test: Buffer Creation
    TEST_F(CircularBufferLargeDataTest, CreateBuffer) {
        EXPECT_EQ(buffer.bufferSizeBytes, circularBuffStatic_capacity(&buffer) / buffer.dataSize);
        EXPECT_EQ(buffer.dataSize, 4);
        EXPECT_EQ(buffer.counter, 0);
        EXPECT_EQ(buffer.put_index, 0);
        EXPECT_EQ(buffer.pop_index, 0);
    }

    // Test: Put and Get Data
    TEST_F(CircularBufferLargeDataTest, PutAndPop) {
        uint32_t input = 42;
        uint32_t output = 0;

        EXPECT_EQ(circularBuffStatic_put(&buffer, &input), CBUFFER_STATUS_OK);
        EXPECT_FALSE(circularBuffStatic_isEmpty(&buffer));
        EXPECT_EQ(circularBuffStatic_pop(&buffer, &output), CBUFFER_STATUS_OK);
        EXPECT_EQ(output, input);
        EXPECT_TRUE(circularBuffStatic_isEmpty(&buffer));
    }

    // Test: Get size
    TEST_F(CircularBufferLargeDataTest, getSize) {
        uint32_t input = 55;
        uint32_t testSize = BUFFER_SIZE / 2;

        for (int i = 0; i < testSize; ++i) {
            EXPECT_EQ(circularBuffStatic_put(&buffer, &input), CBUFFER_STATUS_OK);
        }

        EXPECT_EQ(circularBuffStatic_getSize(&buffer), testSize * BUFFER_DATA_SIZE);
    }