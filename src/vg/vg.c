#include <GLES2/gl2.h>
#include "horsetail/vg.h"

void VgInit(void)
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void VgUpdate(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
