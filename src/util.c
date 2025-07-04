#include <string.h>

#include "horsetail/horsetail.h"

#define RESULT_CASE(result) \
    case result: \
        message = HT_TO_STRING(result); \
            break;

const char *HtResultToString(HtResult result)
{
    const char *message = NULL;

    switch (result)
    {
    RESULT_CASE(HT_SUCCESS);
    RESULT_CASE(HT_ERROR_NO_MEMORY);
    RESULT_CASE(HT_ERROR_NOT_FOUND);
    RESULT_CASE(HT_ERROR_INVALID_ARGUMENT);
    RESULT_CASE(HT_ERROR_GENERIC);
    RESULT_CASE(HT_ERROR_TOO_SMALL);
    RESULT_CASE(HT_ERROR_UNIMPLEMENTED);
    }

    return message;
}

void HtZeroMemory(void *ptr, usize size)
{
    memset(ptr, 0, size);
}
