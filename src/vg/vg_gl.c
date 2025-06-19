#include <GLES2/gl2.h>
#include "horsetail/defs.h"
#include "horsetail/core.h"
#include "vg_gl.h"

static i32 gVertexAttribPointers[] = {
    3,          /* vertex */
    3,          /* color */
};

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

void VgGLProgram_DeInit(VgGLProgram *program)
{
    HtAssert(program != NULL);
    if (program->hProgram != GL_NULL_OBJECT)
    {
        glUseProgram(program->hProgram);
    }
}

void VgGLBeginFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
