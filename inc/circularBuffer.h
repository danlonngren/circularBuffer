#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
CBUFFER_STATUS_OK               = 0,
CBUFFER_STATUS_NOT_INITIALISED  = -1,
CBUFFER_STATUS_FULL             = -2,
CBUFFER_STATUS_EMPTY            = -3,
CBUFFER_STATUS_FAILED           = -4,
}cBufferStatus_t;

#define LIST_INIT() {   \
    .capacity = 0,      \
    .dataSize = 0,      \
    .put_index = 0,     \
    .get_index = 0,     \
    .counter = 0,       \
    .dataBuffer = NULL }

typedef struct {
    uint32_t capacity;
    uint32_t dataSize;
    uint32_t put_index;
    uint32_t get_index;
    uint32_t counter;
    void *dataBuffer;
} circularBufferList_t;


bool circularBufferIsEmpty(circularBufferList_t *pList);

bool circularBufferIsFull(circularBufferList_t *pList);

uint32_t circularBufferCapacity(circularBufferList_t *pList);


cBufferStatus_t circularBufferCreate(circularBufferList_t *config,  void *dataBuffer, uint32_t dataSize, uint32_t capacity);

cBufferStatus_t circularBufferReset(circularBufferList_t *config);


cBufferStatus_t circularBufferGet(circularBufferList_t *config, void *pDataOut);

/* Will override the data if full */
cBufferStatus_t circularBufferPut(circularBufferList_t *config, void *pData);

/*  */
cBufferStatus_t circularBufferPutSafe(circularBufferList_t *config, void *pData);



#endif
