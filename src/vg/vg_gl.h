#ifndef _HORSETAIL_VG_GL_H_
#define _HORSETAIL_VG_GL_H_
    
#include <GLES2/gl2.h>
#include "horsetail/defs.h"
#include "horsetail/vg.h"

#define GL_NULL_OBJECT          0

typedef GLuint hProgram;
typedef GLuint hArrayBuffer;
typedef GLuint hShader;
typedef GLuint hTexture;

typedef struct
{
    hArrayBuffer hArrayBuffer;
    usize stride;
    usize vertexCount;
} VgGLArrayBuffer;

typedef struct
{
    hProgram hProgram;
} VgGLProgram;

typedef struct
{
    hTexture hTexture;
} VgGLTexture;

/* general */
void VgGLLogRendererInfo(void);
void VgGLBeginFrame(void);
void VgGLSetViewport(const VgDisplaySize *displaySize);

HtBool VgGLArrayBuffer_Init(f32 *vertices, usize size, VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_Bind(VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_Draw(VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_DeInit(VgGLArrayBuffer *arrayBuffer);

HtBool VgGLProgram_Init(const char *srcVertex, const char *srcFragment, VgGLProgram *program);
void VgGLProgram_Use(VgGLProgram *program);
HtBool VgGLProgram_UniformMat4(VgGLProgram *program, const char *name, const mat4 *data);
void VgGLProgram_DeInit(VgGLProgram *program);

HtBool VgGLTexture_Init(usize width, usize height, u8 *data, VgGLTexture *texture);
void VgGLTexture_Bind(VgGLTexture *texture);
void VgGLTexture_DeInit(VgGLTexture *texture);

#endif
