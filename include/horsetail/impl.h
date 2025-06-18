#ifndef _HORSETAIL_IMPL_H_
#define _HORSETAIL_IMPL_H_

#define IMPL_DEFAULT_DISPLAY_NAME       "Horsetail"
#define IMPL_DEFAULT_DISPLAY_WIDTH      800
#define IMPL_DEFAULT_DISPLAY_HEIGHT     600

void ImplInit(void);
void ImplShutdown(int code);
void ImplBeginLoop(void);
void ImplFinishUpdate(void);
void ImplShowError(const char *buf);

#endif
