#include "horsetail/horsetail.h"
#include "horsetail/math.h"

#include <math.h>

f32 HtSin(f32 x)
{
    return sinf(x);
}

f32 HtCos(f32 x)
{
    return cosf(x);
}

f32 HtTan(f32 x)
{
    return tanf(x);
}

f32 HtSqrt(f32 x)
{
    return sqrtf(x);
}

f32 HtAbs(f32 x)
{
    return fabs(x);
}

void Mat4Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, mat4 *outMatrix)
{
    HtAssert(outMatrix != NULL);

    HtZeroMemory(outMatrix->data, sizeof(outMatrix->data));

    outMatrix->data[0][0] = 2 / (right - left);
    outMatrix->data[1][1] = 2 / (top - bottom);
    outMatrix->data[2][2] = -2 / (far - near);

    outMatrix->data[3][0] = -(right + left) / (right - left);
    outMatrix->data[3][1] = -(top + bottom) / (top - bottom);
    outMatrix->data[3][2] = -(far + near) / (far - near);
    outMatrix->data[3][3] = 1;
}

void Mat4LookAt(vec3 position, vec3 target, vec3 up, mat4 *outMatrix)
{
    vec3 x;
    vec3 y;
    vec3 z;

    HtAssert(outMatrix != NULL);

    z = Vec3Sub(position, target);
    Vec3Normalize(&z);

    x = Vec3Cross(up, z);
    Vec3Normalize(&x);

    y = Vec3Cross(z, x);
    Vec3Normalize(&y);

    HtZeroMemory(outMatrix->data, sizeof(outMatrix->data));

    outMatrix->data[0][0] = x.x;
    outMatrix->data[1][0] = x.y;
    outMatrix->data[2][0] = x.z;
    outMatrix->data[3][0] = -Vec3Dot(x, position);

    outMatrix->data[0][1] = y.x;
    outMatrix->data[1][1] = y.y;
    outMatrix->data[2][1] = y.z;
    outMatrix->data[3][1] = -Vec3Dot(y, position);

    outMatrix->data[0][2] = z.x;
    outMatrix->data[1][2] = z.y;
    outMatrix->data[2][2] = z.z;
    outMatrix->data[3][2] = -Vec3Dot(z, position);

    outMatrix->data[0][3] = 0;
    outMatrix->data[1][3] = 0;
    outMatrix->data[2][3] = 0;
    outMatrix->data[3][3] = 1;
}

void Mat4Translate(vec3 translation, mat4 *matrix)
{
    matrix->data[3][0] += translation.x;
    matrix->data[3][1] += translation.y;
    matrix->data[3][2] += translation.z;
}

void Mat4Scale(vec3 scale, mat4 *matrix)
{
    matrix->data[0][0] *= scale.x;
    matrix->data[1][1] *= scale.y;
    matrix->data[2][2] *= scale.z;
}
