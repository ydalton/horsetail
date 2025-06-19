#include "horsetail/core.h"
#include "horsetail/vg.h"

#include "vgp.h"
#include "vg_gl.h"

float vrtTriangle[] = {
    0.5, 0.5, 0.0, 1.0, 0.0, 0.0,
    -0.5, 0.5, 0.0, 0.0, 1.0, 0.0,
    0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
    0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
    -0.5, -0.5, 0.0, 1.0, 0.0, 1.0,
    -0.5, 0.5, 0.0, 0.0, 1.0, 0.0,
};

const char *srcVert =
"attribute vec3 aVertex;"
"attribute vec3 aColor;"
"varying vec3 vColor;"
"void main()"
"{"
"    gl_Position = vec4(aVertex, 1.0);"
"    vColor = aColor;"
"}";

const char *srcFrag =
"varying vec3 vColor;"
"void main()"
"{"
"    gl_FragColor = vec4(vColor, 1.0);"
"}";

VgGLArrayBuffer abTriangle = {0};
VgGLProgram prgMain = {0};

void VgInit(void)
{
    VgGLArrayBuffer_Init(vrtTriangle, sizeof(vrtTriangle), &abTriangle);
    VgGLProgram_Init(srcVert, srcFrag, &prgMain);

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void VgpBeginFrame(void)
{
    VgGLBeginFrame();
}

void VgpEndFrame(void)
{
}

void VgUpdate(void)
{
    VgpBeginFrame();

    VgGLProgram_Use(&prgMain);
    VgGLArrayBuffer_Draw(&abTriangle);

    VgpEndFrame();
}

void VgShutdown(void)
{
    VgGLProgram_DeInit(&prgMain);
    VgGLArrayBuffer_DeInit(&abTriangle);
}
