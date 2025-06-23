#include "horsetail/core.h"
#include "horsetail/vg.h"
#include "horsetail/math.h"
#include "horsetail/impl.h"

#include "vgp.h"
#include "vg_gl.h"

float vrtSquare[] = {
    1.0, 1.0, 0.0, 1.0, 0.0,
    -1.0, 1.0, 0.0, 0.0, 0.0,
    1.0, -1.0, 0.0, 1.0, 1.0,
    1.0, -1.0, 0.0, 1.0, 1.0,
    -1.0, -1.0, 0.0, 0.0, 1.0,
    -1.0, 1.0, 0.0, 0.0, 0.0,
};

const char *srcVert =
"precision mediump float;"
"attribute vec3 aVertex;"
"attribute vec2 aTexCoord;"
"varying vec2 vTexCoord;"
"uniform mat4 uModel;"
"uniform mat4 uView;"
"uniform mat4 uProjection;"
"void main()"
"{"
"    gl_Position = uProjection * uView * uModel * vec4(aVertex, 1.0);"
"    vTexCoord = aTexCoord;"
"}";

const char *srcFrag =
"precision lowp float;"
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
#define MAGENTA 0xff, 0x00, 0xff, 0xff
#define BLACK   0x00, 0x00, 0x00, 0xff

#if 0
typedef struct
{
    VgVertices *vertices;
    VgTexture *texture;
} VgObject;
#endif

u8 bmpDefault[] = {
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
};

struct
{
    mat4 projection;
    mat4 view;
} vgState = {0};

VgGLArrayBuffer abSquare = {0};
VgGLProgram prgMain = {0};
VgGLTexture txtDefault = {0};

mat4 model = {0};

void VgInit(void)
{
    VgGLArrayBuffer_Init(vrtSquare, sizeof(vrtSquare), &abSquare);
    VgGLProgram_Init(srcVert, srcFrag, &prgMain);
    VgGLTexture_Init(8, 8, (u8*) bmpDefault, &txtDefault);

    model = Mat4Identity();
    Mat4Scale(VEC3(0.1, 0.1, 0.1), &model);
    Mat4LookAt(VEC3(0.0, 0.0, 5.0), VEC3(0.0, 0.0, 0.0), VEC3(0.0, 1.0, 0.0), &vgState.view);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    HtLog("Vg: initialized\n");
    VgpLogRendererInfo();
}

void VgpLogRendererInfo(void)
{
    HtLog("Vg: renderer info:\n");
    VgGLLogRendererInfo();
}

void VgUpdate(void)
{
    float ratio = 0;
    VgDisplaySize displaySize = {0};
    HtBool result = HT_FALSE;
    HT_UNUSED(result);

    VgGetDisplaySize(&displaySize);
    ratio = (float) displaySize.width / (float) displaySize.height;
    Mat4Ortho(-ratio, ratio, -1, 1, 0.1, 100, &vgState.projection);

    Mat4Translate(VEC3(0.01, 0.0, 0.0), &model);

    VgpBeginFrame();

    VgGLProgram_Use(&prgMain);
    result = VgGLProgram_UniformMat4(&prgMain, "uModel", &model);
    HtAssert(result);
    result = VgGLProgram_UniformMat4(&prgMain, "uView", &vgState.view);
    HtAssert(result);
    result = VgGLProgram_UniformMat4(&prgMain, "uProjection", &vgState.projection);
    HtAssert(result);
    VgGLTexture_Bind(&txtDefault);
    VgGLArrayBuffer_Draw(&abSquare);

    VgpEndFrame();
}

void VgpBeginFrame(void)
{
    VgGLBeginFrame();
}

void VgpEndFrame(void)
{
}

void VgpOnResize(const VgDisplaySize *displaySize)
{
    VgGLSetViewport(displaySize);
}

void VgShutdown(void)
{
    VgGLProgram_DeInit(&prgMain);
    VgGLTexture_DeInit(&txtDefault);
    VgGLArrayBuffer_DeInit(&abSquare);
}
