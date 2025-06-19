#include <GLES2/gl2.h>

#include "horsetail/core.h"
#include "horsetail/vg.h"

GLuint bufCube = 0;
GLuint prgMain = 0;

float vrtCube[] = {
    0.0, 0.5, 0.0, 1.0, 0.0, 0.0,
    0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
    -0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
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

static void _InitShaders(void)
{
    GLuint shdVert = 0;
    GLuint shdFrag = 0;
    GLint succeeded = 0;

    shdVert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shdVert, 1, &srcVert, NULL);
    glCompileShader(shdVert);
    glGetShaderiv(shdVert, GL_COMPILE_STATUS, &succeeded);
    if (succeeded == 0)
    {
        char buf[512];
        glGetShaderInfoLog(shdVert, HT_ARRAY_SIZE(buf), NULL, buf);
        HtError("Vertex shader compilation error: %s\n", buf);
    }

    shdFrag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shdFrag, 1, &srcFrag, NULL);
    glCompileShader(shdFrag);
    glGetShaderiv(shdFrag, GL_COMPILE_STATUS, &succeeded);
    if (succeeded == 0)
    {
        char buf[512];
        glGetShaderInfoLog(shdFrag, HT_ARRAY_SIZE(buf), NULL, buf);
        HtError("Fragment shader compilation error: %s\n", buf);
    }

    prgMain = glCreateProgram();
    glAttachShader(prgMain, shdVert);
    glAttachShader(prgMain, shdFrag);
    glLinkProgram(prgMain);
}

void VgInit(void)
{
    /* create buffer */
    glGenBuffers(1, &bufCube);
    glBindBuffer(GL_ARRAY_BUFFER, bufCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vrtCube), vrtCube, GL_STATIC_DRAW);

    _InitShaders();

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void VgUpdate(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(prgMain);
    glBindBuffer(GL_ARRAY_BUFFER, bufCube);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void VgShutdown(void)
{
    if (prgMain != 0)
    {
        glDeleteProgram(prgMain);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (bufCube != 0)
    {
        glDeleteBuffers(1, &bufCube);
    }
}
