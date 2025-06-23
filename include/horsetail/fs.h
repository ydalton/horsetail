#ifndef _HORSETAIL_FS_H_
#define _HORSETAIL_FS_H_

#include "horsetail/horsetail.h"

typedef struct
{
    usize size;
    u8 *data;
} HtFile;

HtResult FsLoadFile(const char *path, HtFile *outFile);
void FsUnloadFile(HtFile *file);

#endif
