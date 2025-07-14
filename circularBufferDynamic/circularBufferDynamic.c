#include "circularBufferDynamic.h"

#include <stdio.h>
#include <string.h>

/* Helper Functions */
static uint32_t getNextIndex(uint32_t index, uint32_t capacity)
{
    if ((++index) >= (capacity + 1))
        index = 0;
    return index;
}

/* Public APIs */
uint32_t circularBufferDynamicCapacity(circularBufferDynamicList_t *pList)  
{ 
    return pList->capacity; 
}

bool circularBufferDynamicIsEmpty(circularBufferDynamicList_t *pList)
{ 
    return (pList->counter <= 0);
}

bool circularBufferDynamicIsFull(circularBufferDynamicList_t *pList)
{ 
    uint32_t nextIndex = getNextIndex(pList->put_index, pList->capacity);
    return (nextIndex == pList->get_index);
}

cBufferStatus_t circularBufferDynamicCreate(circularBufferDynamicList_t *pList, void *dataBuffer, uint32_t dataSize, uint32_t capacity)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (pList == NULL || dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else
    {
        pList->dataBuffer = dataBuffer;
        pList->dataSize = dataSize;
        pList->capacity = (capacity / dataSize) - 1;
        pList->get_index = 0;
        pList->put_index = 0;
        pList->counter = 0;
    }
    
    return status;
}

cBufferStatus_t circularBufferDynamicReset(circularBufferDynamicList_t *pList)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    if (pList == NULL)
    {
         status = CBUFFER_STATUS_FAILED;
    }
    else
    {
        
        memset(pList, 0, sizeof(circularBufferDynamicList_t));
    }
    return status;
}

static cBufferStatus_t circularBufferDynamicPut_internal(circularBufferDynamicList_t *pList, void *pData)
{
    uint8_t *pTarget = pList->dataBuffer;

    memcpy(&pTarget[pList->put_index * pList->dataSize], pData, pList->dataSize);
    pList->put_index = getNextIndex(pList->put_index, pList->capacity);
    if (++pList->counter > pList->capacity)
    {
        pList->counter = pList->capacity;
        pList->get_index = getNextIndex(pList->get_index, pList->capacity);
    }

    return CBUFFER_STATUS_OK;
}

cBufferStatus_t circularBufferDynamicPut(circularBufferDynamicList_t *pList, void *pData)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (pList == NULL || pData == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (pList->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else
    {
        status = circularBufferDynamicPut_internal(pList, pData);
    }
    
    return status;
}

cBufferStatus_t circularBufferDynamicPutSafe(circularBufferDynamicList_t *pList, void *pData)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (pList == NULL || pData == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (pList->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBufferDynamicIsFull(pList))
    {
        status = CBUFFER_STATUS_FULL;
    }
    else
    {
        status = circularBufferDynamicPut_internal(pList, pData);
    }

    return status;
}


cBufferStatus_t circularBufferDynamicGet(circularBufferDynamicList_t *pList, void *pDataOut)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (pList == NULL || pDataOut == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (pList->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBufferDynamicIsEmpty(pList))
    {
        status = CBUFFER_STATUS_EMPTY;
    }
    else
    {
        uint8_t *pData = pList->dataBuffer;

        memcpy(pDataOut, &pData[pList->get_index * pList->dataSize], pList->dataSize);
        pList->get_index = getNextIndex(pList->get_index, pList->capacity);
        pList->counter--;
    }

    return status;
}

