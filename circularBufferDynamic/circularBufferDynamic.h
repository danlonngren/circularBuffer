#ifndef CIRCULARBUFFERDYNAMIC_H
#define CIRCULARBUFFERDYNAMIC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
CBUFFER_STATUS_OK               = 0,
CBUFFER_STATUS_NOT_INITIALISED  = -1,
CBUFFER_STATUS_FULL             = -2,
CBUFFER_STATUS_EMPTY            = -3,
CBUFFER_STATUS_FAILED           = -4,
}cBufferStatus_t;

#define LIST_INIT(cap, size) { \
    .capacity = (cap),         \
    .dataSize = (size),        \
    .put_index = (0),          \
    .get_index = (0),          \
    .counter = (0),            \
    .dataBuffer = (NULL) }

typedef struct {
    uint32_t capacity;
    uint32_t dataSize;
    uint32_t put_index;
    uint32_t get_index;
    uint32_t counter;
    void *dataBuffer;
} circularBufferDynamicList_t;

int listID = 0;


bool circularBufferDynamicIsEmpty(circularBufferDynamicList_t *pList);

bool circularBufferDynamicIsFull(circularBufferDynamicList_t *pList);

uint32_t circularBufferDynamicCapacity(circularBufferDynamicList_t *pList);

cBufferStatus_t circularBufferDynamicCreate(circularBufferDynamicList_t *config, void *dataBuffer, uint32_t dataSize, uint32_t capacity);

cBufferStatus_t circularBufferDynamicReset(circularBufferDynamicList_t *config);

cBufferStatus_t circularBufferDynamicGet(circularBufferDynamicList_t *config, void *pDataOut);

cBufferStatus_t circularBufferDynamicPut(circularBufferDynamicList_t *config, void *pData);

cBufferStatus_t circularBufferDynamicPutSafe(circularBufferDynamicList_t *config, void *pData);

#endif
