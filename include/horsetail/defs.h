#ifndef _HORSETAIL_DEFS_H_
#define _HORSETAIL_DEFS_H_

#include <stdint.h>
#include <stddef.h>
/* TODO: remove later */
#include <assert.h>

typedef uint8_t     u8;
typedef uint32_t    u32;
typedef int8_t      i8;
typedef int32_t     i32;

typedef float       f32;
typedef size_t      usize;

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

#ifdef DEBUG
#define HT_DEBUG
#endif

#define HT_INLINE               __attribute__((always_inline))
#define HT_UNUSED(x)            (void)x
#define HT_TO_STRING(str)       (#str)
#define HT_ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))

#if defined(__i386__) || defined(__x86_64__)
#define HtDebugBreak()      __asm__ volatile("int3")
#else
#error Unknown CPU
#endif

#ifdef HT_DEBUG
#define HtAssert(statement)     assert((statement))
#else
#define HtAssert(statement)
#endif


#endif
