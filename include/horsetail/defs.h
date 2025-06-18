#ifndef _HORSETAIL_H_
#define _HORSETAIL_H_

#include <stdint.h>
#include <stddef.h>
/* TODO: remove later */
#include <assert.h>

typedef int32_t HtInt;
typedef size_t HtSize;

typedef enum
{
    HT_FALSE = 0,
    HT_TRUE = 1
} HtBool;

typedef enum
{
    HT_ERROR_NO_MEMORY          = -4,
    HT_ERROR_INVALID_ARGUMENT   = -3,
    HT_ERROR_NOT_FOUND          = -2,
    HT_ERROR_UNKNOWN            = -1,
    HT_SUCCESS                  = 0,
} HtResult;

#define HT_TO_STRING(str)       (#str)
#define HT_ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))

#define HtAssert(statement)     assert((statement))

#if defined(__i386__) || defined(__x86_64__)
#define HtDebugBreak()      __asm__ volatile("int3")
#else
#error Unknown CPU
#endif

#endif
