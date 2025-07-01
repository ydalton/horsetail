#ifndef _HORSETAIL_VG_GL_H_
#define _HORSETAIL_VG_GL_H_
    
#include <GLES2/gl2.h>
#include "horsetail/defs.h"
#include "horsetail/vg.h"

#define GL_NULL_OBJECT          0

HT_BEGIN_DECLS

typedef GLuint GLProgram;
typedef GLuint GLArrayBuffer;
typedef GLuint GLShader;
typedef GLuint GLTexture;

struct _VgGLArrayBuffer;
struct _VgGLProgram;
struct _VgGLTexture;

typedef struct _VgGLArrayBuffer VgGLArrayBuffer;
typedef struct _VgGLProgram VgGLProgram;
typedef struct _VgGLTexture VgGLTexture;


/* general */
void VgGLLogRendererInfo(void);
void VgGLBeginFrame(void);
void VgGLSetViewport(const VgDisplaySize *displaySize);

HtBool VgGLArrayBuffer_Init(f32 *vertices, usize size, VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_Bind(const VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_Draw(const VgGLArrayBuffer *arrayBuffer);
void VgGLArrayBuffer_DeInit(VgGLArrayBuffer *arrayBuffer);

HtBool VgGLProgram_Init(const char *srcVertex, const char *srcFragment, VgGLProgram *program);
void VgGLProgram_Use(const VgGLProgram *program);
HtBool VgGLProgram_UniformMat4(VgGLProgram *program, const char *name, const mat4 *data);
void VgGLProgram_DeInit(VgGLProgram *program);

HtBool VgGLTexture_Init(usize width, usize height, const u8 *data, VgGLTexture *texture);
void VgGLTexture_Bind(const VgGLTexture *texture);
void VgGLTexture_DeInit(VgGLTexture *texture);

struct _VgGLArrayBuffer
{
    GLArrayBuffer arrayBuffer;
    usize stride;
    usize vertexCount;

#ifdef __cplusplus
    inline void Init(f32 *vertices, usize size)
    {
        VgGLArrayBuffer_Init(vertices, size, this);
    }
    inline void Bind(void) const
    {
        VgGLArrayBuffer_Bind(this);
    }
    inline void Draw(void) const
    {
        VgGLArrayBuffer_Draw(this);
    }
    inline void DeInit(void)
    {
        VgGLArrayBuffer_DeInit(this);
    }
#endif
};

struct _VgGLProgram
{
    GLProgram program;
#ifdef __cplusplus
    inline HtBool Init(const char *srcVertex, const char *srcFragment)
    {
        return VgGLProgram_Init(srcVertex, srcFragment, this);
    }
    inline void Use(void) const
    {
        VgGLProgram_Use(this);
    }
    inline HtBool UniformMat4(const char *name, const mat4 *data)
    {
        return VgGLProgram_UniformMat4(this, name, data);
    }
    inline void DeInit(void)
    {
        VgGLProgram_DeInit(this);
    }
#endif
};

struct _VgGLTexture
{
    GLTexture texture;
#ifdef __cplusplus
    inline HtBool Init(usize width, usize height, const u8 *data)
    {
        return VgGLTexture_Init(width, height, data, this);
    }
    inline void Bind() const
    {
        VgGLTexture_Bind(this);
    }
    inline void DeInit(void)
    {
        VgGLTexture_DeInit(this);
    }
#endif
};

HT_END_DECLS

#endif
