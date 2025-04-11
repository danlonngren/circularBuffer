#include "circularBufferStatic.h"

#include <stdio.h>
#include <string.h>

/* Helper Functions */
static uint32_t getNextIndex(uint32_t index, uint32_t capacity) {
    if ((++index) >= (capacity + 1))
        index = 0;
    return index;
}

/* Public APIs */
uint32_t circularBuffStatic_capacity(circularBuffStaticList_t *pBuffer) {
    return pBuffer->capacity;
}

bool circularBuffStatic_isEmpty(circularBuffStaticList_t *pBuffer) {
    return (pBuffer->counter <= 0);
}

bool circularBuffStatic_isFull(circularBuffStaticList_t *pBuffer) {
    circularBuffStaticList_t *pBufferInt = pBuffer;
    uint32_t nextIndex = getNextIndex(pBufferInt->put_index, pBufferInt->capacity);
    return (nextIndex == pBufferInt->get_index);
}

cBufferStatus_t circularBuffStatic_create(circularBuffStaticList_t *pBuffer, void *dataBuffer, uint32_t dataSize, uint32_t capacity) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pBufferInt = pBuffer;

    if (!pBufferInt || !dataBuffer) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else {
        pBufferInt->dataBuffer = dataBuffer;
        pBufferInt->dataSize = dataSize;
        pBufferInt->capacity = (capacity / dataSize) - 1;
        pBufferInt->get_index = 0;
        pBufferInt->put_index = 0;
        pBufferInt->counter = 0;
    }

    return status;
}

cBufferStatus_t circularBuffStatic_reset(circularBuffStaticList_t *pBuffer) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pBufferInt = pBuffer;

    if (!pBufferInt) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else {
        memset(pBufferInt, 0, sizeof(circularBuffStaticList_t));
    }
    return status;
}

static cBufferStatus_t circularBuffStaticPut_internal(circularBuffStaticList_t *pBuffer, void *pData) {
    circularBuffStaticList_t *pBufferInt = pBuffer;
    uint8_t *pTarget = pBuffer->dataBuffer;

    if (!pBuffer || !pData) {
        return CBUFFER_STATUS_FAILED;
    } 
    else {
        memcpy(&pTarget[pBufferInt->put_index * pBufferInt->dataSize], pData, pBufferInt->dataSize);
        pBufferInt->put_index = getNextIndex(pBufferInt->put_index, pBufferInt->capacity);
        if (++pBufferInt->counter > pBufferInt->capacity) {
            pBufferInt->counter = pBufferInt->capacity;
            pBufferInt->get_index = getNextIndex(pBufferInt->get_index, pBufferInt->capacity);
        }
    }

    return CBUFFER_STATUS_OK;
}

cBufferStatus_t circularBuffStatic_put(circularBuffStaticList_t *pBuffer, void *pData) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pBufferInt = pBuffer;

    if (!pBufferInt || !pData) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else if (!pBufferInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else {
        status = circularBuffStaticPut_internal(pBufferInt, pData);
    }

    return status;
}

cBufferStatus_t circularBuffStatic_putSafe(circularBuffStaticList_t *pBuffer, void *pData) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pBufferInt = pBuffer;

    if (!pBufferInt || !pData) {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (!pBufferInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBuffStatic_isFull(pBufferInt)) {
        status = CBUFFER_STATUS_FULL;
    }
    else {
        status = circularBuffStaticPut_internal(pBufferInt, pData);
    }

    return status;
}

cBufferStatus_t circularBuffStatic_get(circularBuffStaticList_t *pBuffer, void *pDataOut) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pBufferInt = pBuffer;

    if (!pBufferInt || !pDataOut) {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (!pBufferInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBuffStatic_isEmpty(pBufferInt)) {
        status = CBUFFER_STATUS_EMPTY;
    }
    else {
        uint8_t *pData = pBufferInt->dataBuffer;

        memcpy(pDataOut, &pData[pBufferInt->get_index * pBufferInt->dataSize], pBufferInt->dataSize);
        pBufferInt->get_index = getNextIndex(pBufferInt->get_index, pBufferInt->capacity);
        pBufferInt->counter--;
    }
    return status;
}
