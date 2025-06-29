#ifndef _HORSETAIL_HASHTABLE_HPP_
#define _HORSETAIL_HASHTABLE_HPP_

#include "horsetail/horsetail.h"

template<typename T>
struct HtHashTable
{
    T *data;
    usize count;
    void Init(T *memory, usize count)
    {
        this->data = memory;
        this->count = count;
    }
    usize Hash(const char *key)
    {
        usize hash = 0;
        const int multiplier = 97;
        const unsigned char *c;

        for (c = (unsigned char *)key; *c; c++)
        {
            hash += hash * multiplier * *c;
        }

        hash %= this->count;

        return hash;
    }
    T* Get(const char *key)
    {
        usize index = 0;

        index = this->Hash(key);

        return &data[index];
    }
};

#endif
