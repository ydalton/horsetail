#include "horsetail/horsetail.h"
#include "horsetail/impl.h"
#include "horsetail/mem.h"
#include "horsetail/fs.h"

HtResult FsLoadFile(const char *path, HtFile *outFile)
{
    HtResult result;
    void *fileMemory = NULL;
    usize size = 0;

    HtAssert(outFile != NULL);

    result = ImplGetFileSize(path, &size);
    if (result != HT_SUCCESS)
    {
        HtError("Failed to load file \"%s\": %s", path, HtResultToString(result));
    }

    if (size < 1)
    {
        return HT_ERROR_TOO_SMALL;
    }

    fileMemory = MemAlloc(size, MEM_ALLOC_TAG_FILE);
    if (fileMemory == NULL)
    {
        return HT_ERROR_NO_MEMORY;
    }

    result = ImplReadFileToMemory(path, fileMemory, size);
    if (result != HT_SUCCESS)
    {
        goto fail;
    }

    outFile->size = size;
    outFile->data = fileMemory;

    HtLog("Fs: loaded file %s, %u bytes\n", path, size);

    return result;
fail:
    MemFree(fileMemory);
    return result;
}

void FsUnloadFile(HtFile *file)
{
    file->size = 0;
    if (file->data != NULL)
    {
        MemFree(file->data);
        file->data = NULL;
    }
}
