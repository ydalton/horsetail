#include <GLES2/gl2.h>
#include "horsetail/defs.h"
#include "horsetail/core.h"
#include "horsetail/math.h"
#include "horsetail/vg.h"
#include "vg_gl.h"

static i32 gVertexAttribPointers[] = {
    3,          /* vertex */
    2,          /* texture coordinates */
};

void VgGLSetViewport(const VgDisplaySize *displaySize)
{
    glViewport(0, 0, displaySize->width, displaySize->height);
}

HtBool VgGLArrayBuffer_Init(f32 *vertices, usize sizeVertex, VgGLArrayBuffer *arrayBuffer)
{
    hArrayBuffer hArrayBuffer = 0;
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
        stride += gVertexAttribPointers[i];
    }
    
    vertexCount = sizeVertex / stride;

    arrayBuffer->hArrayBuffer = hArrayBuffer;
    arrayBuffer->stride = stride;
    arrayBuffer->vertexCount = vertexCount;

    return HT_TRUE;
}

void VgGLArrayBuffer_Bind(VgGLArrayBuffer *arrayBuffer)
{
    hArrayBuffer hArrayBuffer;

    if (arrayBuffer == NULL)
    {
        hArrayBuffer = GL_NULL_OBJECT;
    }
    else
    {
        hArrayBuffer = arrayBuffer->hArrayBuffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, hArrayBuffer);
}

void VgGLArrayBuffer_Draw(VgGLArrayBuffer *arrayBuffer)
{
    usize i;
    usize offset = 0;

    HtAssert(arrayBuffer != NULL);
    HtAssert(arrayBuffer->hArrayBuffer != GL_NULL_OBJECT);
    HtAssert(arrayBuffer->stride != 0);
    HtAssert(arrayBuffer->vertexCount != 0);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer->hArrayBuffer);
    for(i = 0; i < HT_ARRAY_SIZE(gVertexAttribPointers); i++)
    {
        usize size = gVertexAttribPointers[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, arrayBuffer->stride * sizeof(f32), (void*) offset);

        offset += size * sizeof(f32);
    }

    glDrawArrays(GL_TRIANGLES, 0, arrayBuffer->vertexCount);
}

void VgGLArrayBuffer_DeInit(VgGLArrayBuffer *arrayBuffer)
{
    HtAssert(arrayBuffer != NULL);

    glDeleteBuffers(1, &arrayBuffer->hArrayBuffer);
}

HtBool VgGLProgram_Init(const char *srcVertex, const char *srcFragment, VgGLProgram *program)
{
    hShader shdVert = 0;
    hShader shdFrag = 0;
    hProgram hProgram = 0;
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

    program->hProgram = hProgram;

    return HT_TRUE;
}

void VgGLProgram_Use(VgGLProgram *program)
{
    hProgram hProgram;

    if (program == NULL)
    {
        hProgram = GL_NULL_OBJECT;
    }
    else
    {
        hProgram = program->hProgram;
    }

    glUseProgram(hProgram);
}

HtBool VgGLProgram_UniformMat4(VgGLProgram *program, const char *name, const mat4 *mat)
{
    GLint location = 0;

    HtAssert(program != NULL);
    HtAssert(name != NULL);
    HtAssert(mat != NULL);
    HtAssert(program->hProgram != GL_NULL_OBJECT);

    VgGLProgram_Use(program);

    location = glGetUniformLocation(program->hProgram, name);
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
    if (program->hProgram != GL_NULL_OBJECT)
    {
        glUseProgram(program->hProgram);
    }
}

HtBool VgGLTexture_Init(usize width, usize height, u8 *data, VgGLTexture *texture)
{
    hTexture hTexture;

    HtAssert(data != NULL);
    HtAssert(texture != NULL);

    glGenTextures(1, &hTexture);
    glBindTexture(GL_TEXTURE_2D, hTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, GL_NULL_OBJECT);

    texture->hTexture = hTexture;

    return HT_TRUE;
}

void VgGLTexture_Bind(VgGLTexture *texture)
{
    hTexture hTexture;

    if (texture == NULL)
    {
        hTexture = GL_NULL_OBJECT;
    }
    else
    {
        hTexture = texture->hTexture;
    }

    glBindTexture(GL_TEXTURE_2D, hTexture);
}

void VgGLBeginFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
