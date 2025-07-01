#include <GLES2/gl2.h>

#include "horsetail/horsetail.h"
#include "horsetail/math.h"
#include "horsetail/vg.h"

#include "vg_gl.h"

static i32 gVertexAttribPointers[] = {
    3,          /* vertex */
    2,          /* texture coordinates */
};

struct VgGLRendererProperty
{
    const char *name;
    i32 property;
};

static struct VgGLRendererProperty gRendererProperties[] =
{
    { "vendor", GL_VENDOR},
    { "renderer", GL_RENDERER},
    { "version", GL_VERSION},
    { "GLSL version", GL_SHADING_LANGUAGE_VERSION},
};

void VgGLLogRendererInfo(void)
{
    usize i = 0;

    for(i = 0; i < HT_ARRAY_SIZE(gRendererProperties); i++)
    {
        struct VgGLRendererProperty *rendererProperty = &gRendererProperties[i];

        HtLog("Vg:   %s: %s\n", rendererProperty->name, glGetString(rendererProperty->property));
    }
}

void VgGLSetViewport(const VgDisplaySize *displaySize)
{
    glViewport(0, 0, displaySize->width, displaySize->height);
}

HtBool VgGLArrayBuffer_Init(f32 *vertices, usize sizeVertex, VgGLArrayBuffer *arrayBuffer)
{
    GLArrayBuffer hArrayBuffer = 0;
    usize stride = 0;
    usize vertexCount = 0;
    usize i = 0;

    HtAssert(arrayBuffer != NULL);

    glGenBuffers(1, &hArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, hArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeVertex, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NULL_OBJECT);

    for (i = 0; i < HT_ARRAY_SIZE(gVertexAttribPointers); i++)
    {
        stride += gVertexAttribPointers[i] * sizeof(f32);
    }
    
    vertexCount = sizeVertex / stride;

    arrayBuffer->arrayBuffer = hArrayBuffer;
    arrayBuffer->stride = stride;
    arrayBuffer->vertexCount = vertexCount;

    HtLog("Vg: created vertex buffer id %u, vertex count %u\n", arrayBuffer->arrayBuffer, arrayBuffer->vertexCount);

    return HT_TRUE;
}

void VgGLArrayBuffer_Bind(const VgGLArrayBuffer *arrayBuffer)
{
    GLArrayBuffer hArrayBuffer;

    if (arrayBuffer == NULL)
    {
        hArrayBuffer = GL_NULL_OBJECT;
    }
    else
    {
        hArrayBuffer = arrayBuffer->arrayBuffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, hArrayBuffer);
}

void VgGLArrayBuffer_Draw(const VgGLArrayBuffer *arrayBuffer)
{
    usize i;
    usize offset = 0;

    HtAssert(arrayBuffer != NULL);
    HtAssert(arrayBuffer->arrayBuffer != GL_NULL_OBJECT);
    HtAssert(arrayBuffer->stride != 0);
    HtAssert(arrayBuffer->vertexCount != 0);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer->arrayBuffer);
    for(i = 0; i < HT_ARRAY_SIZE(gVertexAttribPointers); i++)
    {
        usize size = gVertexAttribPointers[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, arrayBuffer->stride, (void*) offset);

        offset += size * sizeof(f32);
    }

    glDrawArrays(GL_TRIANGLES, 0, arrayBuffer->vertexCount);
}

void VgGLArrayBuffer_DeInit(VgGLArrayBuffer *arrayBuffer)
{
    HtAssert(arrayBuffer != NULL);

    glDeleteBuffers(1, &arrayBuffer->arrayBuffer);
}

HtBool VgGLProgram_Init(const char *srcVertex, const char *srcFragment, VgGLProgram *program)
{
    GLShader shdVert = 0;
    GLShader shdFrag = 0;
    GLProgram hProgram = 0;
    GLint succeeded = 0;

    shdVert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shdVert, 1, &srcVertex, NULL);
    glCompileShader(shdVert);
    glGetShaderiv(shdVert, GL_COMPILE_STATUS, &succeeded);
    if (succeeded == 0)
    {
        char buf[512];
        glGetShaderInfoLog(shdVert, HT_ARRAY_SIZE(buf), NULL, buf);
        HtError("Vertex shader compilation error: %s\n", buf);
    }

    shdFrag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shdFrag, 1, &srcFragment, NULL);
    glCompileShader(shdFrag);
    glGetShaderiv(shdFrag, GL_COMPILE_STATUS, &succeeded);
    if (succeeded == 0)
    {
        char buf[512];
        glGetShaderInfoLog(shdFrag, HT_ARRAY_SIZE(buf), NULL, buf);
        HtError("Fragment shader compilation error: %s\n", buf);
    }

    hProgram = glCreateProgram();
    glAttachShader(hProgram, shdVert);
    glAttachShader(hProgram, shdFrag);
    glLinkProgram(hProgram);
    /* TODO: error handling for program linking */

    glDetachShader(hProgram, shdFrag);
    glDetachShader(hProgram, shdVert);
    glDeleteShader(shdFrag);
    glDeleteShader(shdVert);

    program->program = hProgram;

    return HT_TRUE;
}

void VgGLProgram_Use(const VgGLProgram *program)
{
    GLProgram hProgram;

    if (program == NULL)
    {
        hProgram = GL_NULL_OBJECT;
    }
    else
    {
        hProgram = program->program;
    }

    glUseProgram(hProgram);
}

HtBool VgGLProgram_UniformMat4(VgGLProgram *program, const char *name, const mat4 *mat)
{
    GLint location = 0;

    HtAssert(program != NULL);
    HtAssert(name != NULL);
    HtAssert(mat != NULL);
    HtAssert(program->program != GL_NULL_OBJECT);

    VgGLProgram_Use(program);

    location = glGetUniformLocation(program->program, name);
    if (location == -1)
    {
        return HT_FALSE;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, (float *) mat->data);

    return HT_TRUE;
}

void VgGLProgram_DeInit(VgGLProgram *program)
{
    HtAssert(program != NULL);
    if (program->program != GL_NULL_OBJECT)
    {
        glDeleteProgram(program->program);
    }
    glUseProgram(0);
}

HtBool VgGLTexture_Init(usize width, usize height, const u8 *data, VgGLTexture *texture)
{
    GLTexture hTexture;

    HtAssert(data != NULL);
    HtAssert(texture != NULL);

    glGenTextures(1, &hTexture);
    glBindTexture(GL_TEXTURE_2D, hTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, GL_NULL_OBJECT);

    texture->texture = hTexture;

    return HT_TRUE;
}

void VgGLTexture_Bind(const VgGLTexture *texture)
{
    GLTexture hTexture;

    if (texture == NULL)
    {
        hTexture = GL_NULL_OBJECT;
    }
    else
    {
        hTexture = texture->texture;
    }

    glBindTexture(GL_TEXTURE_2D, hTexture);
}

void VgGLTexture_DeInit(VgGLTexture *texture)
{
    HtAssert(texture != NULL);

    glBindTexture(GL_TEXTURE_2D, GL_NULL_OBJECT);
    glDeleteTextures(1, &texture->texture);
}

void VgGLBeginFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
