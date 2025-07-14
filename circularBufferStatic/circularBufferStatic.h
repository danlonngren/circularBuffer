#ifndef CIRCULARBUFFERSTATIC_H
#define CIRCULARBUFFERSTATIC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
CBUFFER_STATUS_OK               = 0,
CBUFFER_STATUS_NOT_INITIALISED  = -1,
CBUFFER_STATUS_FULL             = -2,
CBUFFER_STATUS_EMPTY            = -3,
CBUFFER_STATUS_FAILED           = -4,
}cBufferStatus_t;

typedef struct {
    /* Buffer control info */
    uint32_t put_index;
    uint32_t pop_index;
    uint32_t counter;
    /* Buffer data and storage */
    uint32_t capacity;
    uint32_t dataSize;
    uint8_t *dataBuffer;
} circularBuffStaticList_t;

/** @brief Creates and initializes a static circular buffer. */
cBufferStatus_t circularBuffStatic_create(circularBuffStaticList_t *pList, void *dataBuffer, uint32_t dataSize, uint32_t capacity);

/** @brief Reset list */
cBufferStatus_t circularBuffStatic_reset(circularBuffStaticList_t *pList);

/** @brief Insert data. Will override data if list full */
cBufferStatus_t circularBuffStatic_put(circularBuffStaticList_t *pList, void *pData);

/** @brief Insert data. Prevents data from being overriden */
cBufferStatus_t circularBuffStatic_putSafe(circularBuffStaticList_t *pList, void *pData);

/** @brief Get data */
cBufferStatus_t circularBuffStatic_pop(circularBuffStaticList_t *pList, void *pDataOut);

/** @brief Returns true if list is full */
bool circularBuffStatic_isFull(circularBuffStaticList_t *pList);

/** @brief Returns true if list is empty */
bool circularBuffStatic_isEmpty(circularBuffStaticList_t *pList);

/** @brief Returns current size */
uint32_t circularBuffStatic_getSize(circularBuffStaticList_t *pList);

/** @brief Returns total capacity */
uint32_t circularBuffStatic_capacity(circularBuffStaticList_t *pList);

#endif
