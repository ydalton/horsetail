#ifndef _HORSETAIL_DEFS_H_
#define _HORSETAIL_DEFS_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
#define HT_BEGIN_DECLS extern "C" {
#define HT_END_DECLS }
#else 
#define HT_BEGIN_DECLS
#define HT_END_DECLS
#endif

HT_BEGIN_DECLS

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
    HT_ERROR_UNIMPLEMENTED      = -6,
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
#define HT_CONTENTS_TO_STRING(str) HT_TO_STRING(str)
#define HT_ARRAY_SIZE(arr)      (sizeof(arr)/sizeof(arr[0]))
#ifdef __cplusplus
#define HT_ZERO_INIT        {};
#else
#define HT_ZERO_INIT        {0};
#endif

#if defined(__i386__) || defined(__x86_64__)
# define HtDebugBreak()      __asm__ volatile("int3")
#elif defined(__clang__)
# define HtDebugBreak()	     __builtin_debugtrap()
#else
# error Unknown platform
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
            HtShowError(__FILE__ ":" HT_CONTENTS_TO_STRING(__LINE__) ": Assertion \"" #statement "\" failed.\n"); \
            HtDebugBreak();                                                                              \
        }                                                                                                \
    } while(0);
# define HtAssertNotReached() \
    do                                                                                    \
    {                                                                                     \
        HtShowError(__FILE__ ":" HT_CONTENTS_TO_STRING(__LINE__) ": unreachable code reached.\n"); \
        HtDebugBreak();                                                                   \
    } while(0);
# endif
#else
# define HtAssert(statement)
# define HtAssertNotReached()
#endif


void _HtLog(const char *fmt, ...);
void HtError(const char *fmt, ...);
void HtShowError(const char *buf);

#define HtLog(...)             _HtLog(__VA_ARGS__)

HT_END_DECLS

#endif
