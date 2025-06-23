#ifndef _HORSETAIL_MATRIX_H_
#define _HORSETAIL_MATRIX_H_

typedef struct {
    f32 data[4][4];
} mat4;

static HT_INLINE mat4 Mat4Identity()
{
    mat4 matrix = {0};

    matrix.data[0][0] = 1.0;
    matrix.data[1][1] = 1.0;
    matrix.data[2][2] = 1.0;
    matrix.data[3][3] = 1.0;

    return matrix;
}

static HT_INLINE void Mat4Copy(mat4 src, mat4 dest)
{
    usize i,j;
    HT_UNUSED(dest);

    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 4; i++)
        {
            dest.data[j][i] = src.data[j][i];
        }
    }
}

void Mat4Translate(vec3 translation, mat4 *matrix);
void Mat4Scale(vec3 scale, mat4 *matrix);

void Mat4Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far, mat4 *matrix);
void Mat4LookAt(vec3 position, vec3 target, vec3 up, mat4 *matrix);

#endif
