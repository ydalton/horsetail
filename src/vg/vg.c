#include "horsetail/core.h"
#include "horsetail/vg.h"
#include "horsetail/math.h"

#include "vgp.h"
#include "vg_gl.h"

float vrtTriangle[] = {
    0.5, 0.5, 0.0, 1.0, 0.0,
    -0.5, 0.5, 0.0, 0.0, 0.0,
    0.5, -0.5, 0.0, 1.0, 1.0,
    0.5, -0.5, 0.0, 1.0, 1.0,
    -0.5, -0.5, 0.0, 0.0, 1.0,
    -0.5, 0.5, 0.0, 0.0, 0.0,
};

const char *srcVert =
"attribute vec3 aVertex;"
"attribute vec2 aTexCoord;"
"varying vec2 vTexCoord;"
"uniform mat4 uModel;"
"uniform mat4 uView;"
"void main()"
"{"
"    gl_Position = uView * uModel * vec4(aVertex, 1.0);"
"    vTexCoord = aTexCoord;"
"}";

const char *srcFrag =
"varying vec2 vTexCoord;"
"uniform sampler2D uTexture;"
"void main()"
"{"
"    gl_FragColor = texture2D(uTexture, vTexCoord);"
"}";

#define RED     0xff, 0x00, 0x00, 0xff
#define ORANGE  0xff, 0x7f, 0x00, 0xff
#define YELLOW  0xff, 0xff, 0x00, 0xff
#define GREEN   0x00, 0xff, 0x00, 0xff
#define BLUE    0x00, 0x00, 0xff, 0xff
#define PURPLE  0x7f, 0x00, 0xff, 0xff

u8 bmpFlag[] = {
    RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE,
    RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE,
    RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE,
};

VgGLArrayBuffer abTriangle = {0};
VgGLProgram prgMain = {0};
VgGLTexture txtFlag = {0};

mat4 model = {0};
mat4 view = {0};
mat4 perspective = {0};

void VgInit(void)
{
    VgGLArrayBuffer_Init(vrtTriangle, sizeof(vrtTriangle), &abTriangle);
    VgGLProgram_Init(srcVert, srcFrag, &prgMain);
    VgGLTexture_Init(6, 3, (u8*) bmpFlag, &txtFlag);

    Mat4Identity(&model);
    Mat4Identity(&view);
    Mat4Ortho(0, 800, 0, 600, 0.1, 100, &perspective);

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void VgUpdate(void)
{
    HtBool result = HT_FALSE;
    HT_UNUSED(result);
    VgpBeginFrame();

    VgGLProgram_Use(&prgMain);
    result = VgGLProgram_UniformMat4(&prgMain, "uModel", &model);
    HtAssert(result);
    result = VgGLProgram_UniformMat4(&prgMain, "uView", &view);
    HtAssert(result);
    VgGLTexture_Bind(&txtFlag);
    VgGLArrayBuffer_Draw(&abTriangle);

    VgpEndFrame();
}

void VgpBeginFrame(void)
{
    VgGLBeginFrame();
}

void VgpEndFrame(void)
{
}

void VgShutdown(void)
{
    VgGLProgram_DeInit(&prgMain);
    VgGLArrayBuffer_DeInit(&abTriangle);
}
