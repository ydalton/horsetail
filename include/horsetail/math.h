#ifndef _HORSETAIL_MATH_H_
#define _HORSETAIL_MATH_H_

#include "horsetail/defs.h"

/* vectors */

typedef union
{
    f32 data[2];
    struct
    {
        union
        {
            f32 x,r,u;
        };
        union
        {
            f32 y,g,v;
        };
    };
} vec2;

typedef union
{
    f32 data[3];
    struct 
    {
        union
        {
            f32 x,r,u;
        };
        union
        {
            f32 y,g,v;
        };
        union
        {
            f32 z,b,w;
        };
    };
} vec3;

typedef union
{
    f32 data[4];
    struct 
    {
        union
        {
            f32 x,r;
        };
        union
        {
            f32 y,g;
        };
        union
        {
            f32 z,b;
        };
        union
        {
            f32 w,a;
        };
    };
} vec4;

/* matrices */

typedef struct {
    f32 data[4][4];
} mat4;

void Mat4Identity(mat4 *matrix);
void Mat4Ortho(float left, float right, float bottom, float top, float near, float far, mat4 *outMatrix);

#define MAT4_IDENTITY       mat4_identity()

#endif
