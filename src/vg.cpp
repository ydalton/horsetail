#include "horsetail/horsetail.h"
#include "horsetail/vg.h"
#include "horsetail/math.h"
#include "horsetail/impl.h"
#include "horsetail/rs.h"

#include "horsetail_private.h"

#include "vgp.h"
#include "vg_gl.h"

#include "builtin.h"

float vrtSquare[] = {
    1.0, 1.0, 0.0, 1.0, 0.0,
    -1.0, 1.0, 0.0, 0.0, 0.0,
    1.0, -1.0, 0.0, 1.0, 1.0,
    1.0, -1.0, 0.0, 1.0, 1.0,
    -1.0, -1.0, 0.0, 0.0, 1.0,
    -1.0, 1.0, 0.0, 0.0, 0.0,
};

#define RED     0xff, 0x00, 0x00, 0xff
#define ORANGE  0xff, 0x7f, 0x00, 0xff
#define YELLOW  0xff, 0xff, 0x00, 0xff
#define GREEN   0x00, 0xff, 0x00, 0xff
#define BLUE    0x00, 0x00, 0xff, 0xff
#define PURPLE  0x7f, 0x00, 0xff, 0xff
#define MAGENTA 0xff, 0x00, 0xff, 0xff
#define BLACK   0x00, 0x00, 0x00, 0xff

const u8 bmpDefault[] = {
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
    MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, 
    BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA, BLACK, MAGENTA,
};

static struct
{
    VgCamera camera;
} vgState = HT_ZERO_INIT;

VgGLArrayBuffer abSquare = HT_ZERO_INIT;
VgGLProgram prgMain = HT_ZERO_INIT;
VgGLTexture txtDefault = HT_ZERO_INIT;

mat4 model = HT_ZERO_INIT;

void VgInit(void)
{
    HtResult result;
    HtResource *picto;

    abSquare.Init(vrtSquare, sizeof(vrtSquare));
    prgMain.Init((char *)simple_mvp_vert_glsl, (char *)simple_frag_glsl);
    txtDefault.Init(8, 8, bmpDefault);

    model = Mat4Identity();
    model.Scale(VEC3(0.5, 0.5, 0.5));
    Mat4LookAt(VEC3(0.0, 0.0, 5.0), VEC3(0.0, 0.0, 0.0), VEC3(0.0, 1.0, 0.0), &vgState.camera.view);

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
    VgpBeginFrame();

    prgMain.Use();

    prgMain.UniformMat4("uModel", &model);
    prgMain.UniformMat4("uView", &vgState.camera.view);
    prgMain.UniformMat4("uProjection", &vgState.camera.projection);

    txtDefault.Bind();
    abSquare.Draw();

    VgpEndFrame();
}

VgCamera *VgGetCamera(void)
{
    return &vgState.camera;
}

void VgCamera_Move(VgCamera *camera, vec3 movement)
{
    Mat4Translate(movement, &camera->view);
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
    prgMain.DeInit();
    txtDefault.DeInit();
    abSquare.DeInit();
}
