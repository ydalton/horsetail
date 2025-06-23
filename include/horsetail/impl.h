#ifndef _HORSETAIL_IMPL_H_
#define _HORSETAIL_IMPL_H_

#include "horsetail/horsetail.h"

void ImplInit(void);
void ImplShutdown(int code);
void ImplBeginLoop(void);
void ImplGetEvents(void);
void ImplFinishUpdate(void);
void ImplShowError(const char *buf);

void *ImplMemAlloc(usize size);
void ImplMemFree(void *ptr);
HtResult ImplReadFileToMemory(const char *path, void *fileMemory, usize maxSize);
HtResult ImplGetFileSize(const char *path, usize *outFileSize);

#endif
