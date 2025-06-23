#ifndef _HORSETAIL_DEFS_H_
#define _HORSETAIL_DEFS_H_

#include <stdint.h>
#include <stddef.h>

#include "horsetail/log.h"

typedef uint8_t     u8;
typedef uint32_t    u32;
typedef int8_t      i8;
typedef int32_t     i32;

typedef float       f32;
typedef size_t      usize;
typedef i32         isize;

typedef enum
{
    HT_FALSE = 0,
    HT_TRUE = 1
} HtBool;

typedef enum
{
    HT_ERROR_TOO_SMALL          = -5,
    HT_ERROR_NO_MEMORY          = -4,
    HT_ERROR_INVALID_ARGUMENT   = -3,
    HT_ERROR_NOT_FOUND          = -2,
    HT_ERROR_GENERIC            = -1,
    HT_SUCCESS                  = 0,
} HtResult;

#define HT_ENGINE_NAME          "horsetail"

#ifndef HT_DEBUG
# ifdef DEBUG
#  define HT_DEBUG
# endif
#endif

#define HT_INLINE               __inline__
#define HT_UNUSED(x)            (void)x
#define HT_TO_STRING(str)       #str
#define HT_ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))

#if defined(__i386__) || defined(__x86_64__)
# define HtDebugBreak()      __asm__ volatile("int3")
#else
# error Unknown CPU
#endif

#ifdef HT_DEBUG
# if 0
#  define HtAssert(statement)     assert((statement))
# else
#  define HtAssert(statement) \
    do                                                                                                   \
    {                                                                                                    \
        if (statement)                                                                                   \
        {                                                                                                \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            HtShowError(__FILE__ " " HT_TO_STRING(__LINE__) ": Assertion \"" #statement "\" failed.\n"); \
            HtDebugBreak();                                                                              \
        }                                                                                                \
    } while(0);
# define HtAssertNotReached() \
    do                                                                                    \
    {                                                                                     \
        HtShowError(__FILE__ " " HT_TO_STRING(__LINE__) ": unreachable code reached.\n"); \
        HtDebugBreak();                                                                   \
    } while(0);
# endif
#else
# define HtAssert(statement)
# define HtAssertNotReached()
#endif


#endif
