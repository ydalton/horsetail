#ifndef _HORSETAIL_ARRAY_H_
#define _HORSETAIL_ARRAY_H_

#include "horsetail/horsetail.h"

HT_BEGIN_DECLS

struct _HtArray;

typedef struct _HtArray HtArray;

HtArray *_HtArray_Create(usize capacity, usize stride);
void *HtArray_GetData(HtArray *array);
void _HtArray_Push(HtArray **array, const void *value);
usize HtArray_GetLength(HtArray *array);
void _HtArray_Resize(HtArray **array);
void _HtArray_Destroy(HtArray *array);

#define HT_ARRAY_DEFAULT_LENGTH     4
#define HT_ARRAY_RESIZE_FACTOR      2

#define HtArray_Create(type)        _HtArray_Create(HT_ARRAY_DEFAULT_LENGTH, sizeof(type))

#define HtArray_Push(array, value)  \
    {                                   \
        __typeof__(value) tmp = value;       \
        _HtArray_Push(array, &tmp);    \
    }

HT_END_DECLS

#endif
