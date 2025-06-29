#ifndef _HORSETAIL_ARRAY_HPP_
#define _HORSETAIL_ARRAY_HPP_

#include "horsetail/horsetail.h"
#include "horsetail/mem.h"

#define HT_ARRAY_RESIZE_FACTOR      2
#define HT_ARRAY_DEFAULT_CAPACITY   16

template <typename T>
struct HtArray
{
    T *data;
    usize length;
    usize capacity;
    HtBool initialized;

    void Init(usize capacity)
    {
        HtAssert(!this->initialized);
        this->capacity = capacity;
        data = (T *) MemAlloc(this->capacity * sizeof(T), MEM_ALLOC_TAG_ARRAY);
        length = 0;
        this->initialized = HT_TRUE;
    }

    void Init(void)
    {
        this->Init(HT_ARRAY_DEFAULT_CAPACITY);
    }

    void Resize(void)
    {
        T *tmp = NULL;

        tmp = (T*) MemAlloc(sizeof(T) * capacity * HT_ARRAY_RESIZE_FACTOR, MEM_ALLOC_TAG_ARRAY);
        HtCopyMemory(tmp, data, capacity * sizeof(T));
        MemFree(this->data);

        capacity *= HT_ARRAY_RESIZE_FACTOR;
        this->data = tmp;
    }

    void Push(T value)
    {
        HtAssert(this->initialized);
        if (this->length >= this->capacity)
        {
            this->Resize();
        }
        this->data[length] = value;
        length++;
    }

    T Pop(void)
    {
        T result;

        HtAssert(this->initialized);
        result = this->data[length - 1];
        this->length--;
        return result;
    }
    void DeInit(void)
    {
        HtAssert(this->initialized);
        MemFree(this->data);
        this->data = NULL;
    }
};

#endif
