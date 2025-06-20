#include "horsetail/horsetail.h"
#include "horsetail/math.h"

void Mat4Identity(mat4 *outMatrix)
{
    usize i;
    HtAssert(outMatrix != NULL);

    HtZeroMemory(outMatrix, sizeof(*outMatrix));

    for(i = 0; i < 4; i++)
    {
        outMatrix->data[i][i] = 1.0f;
    }
}

void Mat4Ortho(float left, float right, float bottom, float top, float near, float far, mat4 *outMatrix)
{
    HtAssert(outMatrix != NULL);

    HtZeroMemory(outMatrix, sizeof(*outMatrix));

    outMatrix->data[0][0] = 2 / (right - left);
    outMatrix->data[1][1] = 2 / (top - bottom);
    outMatrix->data[2][2] = -2 / (far - near);

    outMatrix->data[3][0] = -(right + left) / (right - left);
    outMatrix->data[3][0] = -(top + bottom) / (top - bottom);
    outMatrix->data[3][0] = -(far + near) / (far - near);
}
