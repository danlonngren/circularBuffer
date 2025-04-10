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

cBufferStatus_t circularBufferDynamicCreate(circularBufferDynamicList_t *config, void *dataBuffer, uint32_t dataSize, uint32_t capacity)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (config == NULL || dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else
    {
        // config->dataBuffer = dataBuffer;
        config->dataSize = dataSize;
        config->capacity = (capacity / dataSize) - 1;
        config->get_index = 0;
        config->put_index = 0;
        config->counter = 0;
    }
    
    return status;
}

cBufferStatus_t circularBufferDynamicReset(circularBufferDynamicList_t *config)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;
    if (config == NULL)
    {
         status = CBUFFER_STATUS_FAILED;
    }
    else
    {
        
        memset(config, 0, sizeof(circularBufferDynamicList_t));
    }
    return status;
}

static cBufferStatus_t circularBufferDynamicPut_internal(circularBufferDynamicList_t *config, void *pData)
{
    uint8_t *pTarget = config->dataBuffer;

    memcpy(&pTarget[config->put_index * config->dataSize], pData, config->dataSize);
    config->put_index = getNextIndex(config->put_index, config->capacity);
    if (++config->counter > config->capacity)
    {
        config->counter = config->capacity;
        config->get_index = getNextIndex(config->get_index, config->capacity);
    }

    return CBUFFER_STATUS_OK;
}

cBufferStatus_t circularBufferDynamicPut(circularBufferDynamicList_t *config, void *pData)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (config == NULL || pData == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (config->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else
    {
        status = circularBufferDynamicPut_internal(config, pData);
    }
    
    return status;
}

cBufferStatus_t circularBufferDynamicPutSafe(circularBufferDynamicList_t *config, void *pData)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (config == NULL || pData == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (config->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBufferDynamicIsFull(config))
    {
        status = CBUFFER_STATUS_FULL;
    }
    else
    {
        status = circularBufferDynamicPut_internal(config, pData);
    }

    return status;
}


cBufferStatus_t circularBufferDynamicGet(circularBufferDynamicList_t *config, void *pDataOut)
{
    cBufferStatus_t status = CBUFFER_STATUS_OK;

    if (config == NULL || pDataOut == NULL)
    {
        status = CBUFFER_STATUS_FAILED;
    }
    else if (config->dataBuffer == NULL)
    {
        status = CBUFFER_STATUS_NOT_INITIALISED;
    }
    else if (circularBufferDynamicIsEmpty(config))
    {
        status = CBUFFER_STATUS_EMPTY;
    }
    else
    {
        uint8_t *pData = config->dataBuffer;

        memcpy(pDataOut, &pData[config->get_index * config->dataSize], config->dataSize);
        config->get_index = getNextIndex(config->get_index, config->capacity);
        config->counter--;
    }

    return status;
}

