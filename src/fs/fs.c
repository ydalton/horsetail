#include "horsetail/horsetail.h"
#include "horsetail/impl.h"
#include "horsetail/mem.h"
#include "horsetail/fs.h"

HtResult FsLoadFile(const char *path, HtFile *outFile)
{
    HtResult result;
    usize size = 0;

    HtAssert(outFile != NULL);

    result = ImplGetFileSize(path, &size);
    if (result == HT_SUCCESS)
    {
        void *fileMemory = NULL;

        if (size < 1)
        {
            return HT_ERROR_TOO_SMALL;
        }

        fileMemory = MemAlloc(size, MEM_ALLOC_TAG_FILE);

        result = ImplReadFileToMemory(path, fileMemory, size);
        if (result == HT_SUCCESS)
        {
            outFile->size = size;
            outFile->data = fileMemory;

            HtLog("Fs: loaded file %s, %u bytes", path, size);
        }
    }

    return result;
}
