#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "horsetail/impl.h"

static usize ImplpGetFileSizeFromFD(int fd);

void *ImplMemAlloc(usize size)
{
    void *memory = NULL;

    memory = malloc(size);

    return memory;
}

void ImplMemFree(void *memory)
{
    free(memory);
}

HtResult ImplReadFileToMemory(const char *path, void *fileMemory, usize maxSize)
{
    HtResult result = HT_ERROR_GENERIC;
    int fd = 0;
    usize size = 0;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        return HT_ERROR_GENERIC;
    }

    size = ImplpGetFileSizeFromFD(fd);

    HtAssert(maxSize <= size);

    if (size > 0 && fileMemory != NULL)
    {
        isize bytesRead = 0;

        bytesRead = read(fd, fileMemory, maxSize);

        if (bytesRead != -1 && (usize) bytesRead == maxSize)
        {
            result = HT_SUCCESS;
        }
    }

    close(fd);

    return result;
}

static usize ImplpGetFileSizeFromFD(int fd)
{
    usize size = 0;
    off_t offset = 0;

    /* save the position of the fd */
    offset = lseek(fd, 0, SEEK_CUR);
    /* get the size by seeking to the end */
    size = lseek(fd, 0, SEEK_END);
    /* set the fd back to where it was */
    lseek(fd, offset, SEEK_SET);

    return size;
}

HtResult ImplGetFileSize(const char *path, usize *outFileSize)
{
    HtResult result = HT_ERROR_GENERIC;
    int fd = 0;
    isize fileSize = 0;

    HtAssert(outFileSize != NULL);

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        return HT_ERROR_GENERIC;
    }

    fileSize = ImplpGetFileSizeFromFD(fd);

    if (fileSize >= 0)
    {
        *outFileSize = (usize) fileSize;
        result = HT_SUCCESS;
    }

    close(fd);

    return result;
}

void ImplShowError(const char *buf)
{
    fputs(buf, stderr);
}
