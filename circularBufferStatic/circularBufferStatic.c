#include "circularBufferStatic.h"

#include <stdio.h>
#include <string.h>

/* Helper Functions */
static uint32_t getNextIndex(uint32_t index, uint32_t capacity) {
    if ((++index) > (capacity))
        index = 0;
    return index;
}

/* Public APIs */
cBufferStatus_t circularBuffStatic_create(circularBuffStaticList_t *pList, void *dataBuffer, uint32_t dataSize, uint32_t capacity) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pListInt = pList;

    if (!pListInt || !dataBuffer) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else {
        pListInt->dataBuffer = dataBuffer;
        pListInt->dataSize = dataSize;
        pListInt->capacity = (capacity / dataSize);
        pListInt->pop_index = 0;
        pListInt->put_index = 0;
        pListInt->counter = 0;
    }

    return status;
}

cBufferStatus_t circularBuffStatic_reset(circularBuffStaticList_t *pList) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pListInt = pList;

    if (!pListInt) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else {
        memset(pListInt, 0, sizeof(circularBuffStaticList_t));
    }
    return status;
}

cBufferStatus_t circularBuffStatic_put(circularBuffStaticList_t *pList, void *pData) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pListInt = pList;

    if (!pListInt || !pData) {
        status = CBUFFER_STATUS_FAILED;
    } 
    else if (!pListInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else {
        memcpy((void *)&pList->dataBuffer[pListInt->put_index * pListInt->dataSize], pData, pListInt->dataSize);
        pListInt->put_index = getNextIndex(pListInt->put_index, pListInt->capacity);
        /* Handle wraparound */
        if (++pListInt->counter > pListInt->capacity) {
            pListInt->counter = pListInt->capacity;
            pListInt->pop_index = getNextIndex(pListInt->pop_index, pListInt->capacity);
        }
        status = CBUFFER_STATUS_OK;    
    }

    return status;
}

cBufferStatus_t circularBuffStatic_putSafe(circularBuffStaticList_t *pList, void *pData) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pListInt = pList;

    if (!pListInt || !pData) {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (!pListInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBuffStatic_isFull(pListInt)) {
        status = CBUFFER_STATUS_FULL;
    }
    else {
        memcpy((void*)&pList->dataBuffer[pListInt->put_index * pListInt->dataSize], pData, pListInt->dataSize);
        pListInt->put_index = getNextIndex(pListInt->put_index, pListInt->capacity);
        if (++pListInt->counter > pListInt->capacity) {
            pListInt->counter = pListInt->capacity;
        }
        status = CBUFFER_STATUS_OK;    
    }

    return status;
}

cBufferStatus_t circularBuffStatic_pop(circularBuffStaticList_t *pList, void *pDataOut) {
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    circularBuffStaticList_t *pListInt = pList;

    if (!pListInt || !pDataOut) {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (!pListInt->dataBuffer) {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBuffStatic_isEmpty(pListInt)) {
        status = CBUFFER_STATUS_EMPTY;
    }
    else {
        uint8_t *pData = pListInt->dataBuffer;
        memcpy(pDataOut, &pData[pListInt->pop_index * pListInt->dataSize], pListInt->dataSize);
        pListInt->pop_index = getNextIndex(pListInt->pop_index, pListInt->capacity);
        pListInt->counter--;

        if (circularBuffStatic_isEmpty(pListInt)) {
            pListInt->pop_index = 0;
            pListInt->put_index = 0;
        }
    }
    return status;
}

bool circularBuffStatic_isFull(circularBuffStaticList_t *pList) {
    if (!pList) {
        return false;
    }
    return (pList->counter == (pList->capacity ));
}

bool circularBuffStatic_isEmpty(circularBuffStaticList_t *pList) {
    if (!pList) {
        return false;
    }
    return (pList->counter <= 0);
}

uint32_t circularBuffStatic_getSize(circularBuffStaticList_t *pList) {
    if (!pList) {
        return 0;
    }
    return pList->counter * pList->dataSize;
}

uint32_t circularBuffStatic_capacity(circularBuffStaticList_t *pList) {
    if (!pList) {
        return false;
    }
    return pList->capacity * pList->dataSize;
}
