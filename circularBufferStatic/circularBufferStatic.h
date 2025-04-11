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
    uint32_t get_index;
    uint32_t counter;
    /* Buffer data and storage */
    uint32_t capacity;
    uint32_t dataSize;
    void *dataBuffer;
} circularBuffStaticList_t;


cBufferStatus_t circularBuffStatic_create(circularBuffStaticList_t *pBuffer, void *dataBuffer, uint32_t dataSize, uint32_t capacity);

cBufferStatus_t circularBuffStatic_reset(circularBuffStaticList_t *pBuffer);

cBufferStatus_t circularBuffStatic_put(circularBuffStaticList_t *pBuffer, void *pData);

cBufferStatus_t circularBuffStatic_putSafe(circularBuffStaticList_t *pBuffer, void *pData);

cBufferStatus_t circularBuffStatic_get(circularBuffStaticList_t *pBuffer, void *pDataOut);

bool circularBuffStatic_isFull(circularBuffStaticList_t *pBuffer);

bool circularBuffStatic_isEmpty(circularBuffStaticList_t *pBuffer);

uint32_t circularBuffStatic_capacity(circularBuffStaticList_t *pBuffer);

#endif
