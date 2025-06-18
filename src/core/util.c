#include "horsetail/defs.h"
#include "horsetail/util.h"

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
    RESULT_CASE(HT_ERROR_UNKNOWN);
    /* we should not land here */
    default:
        HtDebugBreak();
        break;
    }

    return message;
}
