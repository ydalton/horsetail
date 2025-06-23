#include "horsetail/array.h"
#include "horsetail/mem.h"

typedef struct
{
    usize length;
    usize capacity;
    usize stride;
} HtArrayHeader;

static HtArrayHeader *_HtArray_GetHeader(HtArray *array)
{
    return (HtArrayHeader *) array;
}

HtArray *_HtArray_Create(usize capacity, usize stride)
{
    HtArray *array = NULL;
    usize arraySize = (capacity * stride);
    HtArrayHeader *header = NULL;

    array = MemAlloc(sizeof(HtArrayHeader) + arraySize, MEM_ALLOC_TAG_ARRAY);
    if (array == NULL)
    {
        return NULL;
    }

    header = _HtArray_GetHeader(array);

    header->length = 0;
    header->capacity = capacity;
    header->stride = stride;

    return array;
}

void *HtArray_GetData(HtArray *array)
{
    void *data = NULL;

    data = (void *) array + sizeof(HtArrayHeader);

    return data;
}

usize HtArray_GetLength(HtArray *array)
{
    return _HtArray_GetHeader(array)->length;
}

void HtArray_Resize(HtArray **array)
{
    HtArrayHeader *header = NULL;
    HtArray *tmp = NULL;
    usize stride = 0;
    usize length = 0;
    usize capacity = 0;

    HtAssert(array != NULL);
    HtAssert(*array != NULL);

    header = _HtArray_GetHeader(*array);
    stride = header->stride;
    length = header->length;
    capacity = header->capacity;

    tmp = _HtArray_Create(HT_ARRAY_RESIZE_FACTOR * capacity, stride);
    /* copy the existing data */
    HtCopyMemory(HtArray_GetData(tmp), HtArray_GetData(*array), capacity * length);

    header = _HtArray_GetHeader(tmp);
    header->length = length;
    _HtArray_Destroy(*array);

    *array = tmp;
}

void _HtArray_Push(HtArray **array, const void *value)
{
    HtArrayHeader *header = NULL;
    void *arrayEnd = NULL;
    usize capacity = 0;
    usize stride = 0;
    usize length = 0;

    HtAssert(array != NULL);
    HtAssert(*array != NULL);

    header = _HtArray_GetHeader(*array);

    length = header->length;
    capacity = header->capacity;
    stride = header->stride;

    if (length >= capacity)
    {
        HtArray_Resize(array);
    }

    arrayEnd = HtArray_GetData(*array) + (length * stride);
    HtCopyMemory(arrayEnd, value, stride);

    header = _HtArray_GetHeader(*array);
    header->length++;
}

void _HtArray_Destroy(HtArray *array)
{
    MemFree(array);
}
