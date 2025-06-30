#ifndef _HORSETAIL_VECTOR_H_
#define _HORSETAIL_VECTOR_H_

#ifndef _HORSETAIL_MATH_H_
#error Do not include thing file directly. Please include "horsetail/math.h" instead.
#endif

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

typedef union _vec3
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
#ifdef __cplusplus
    _vec3 operator * (_vec3 &other);
#endif
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

#define VEC3(x,y,z)         ((vec3){.data = {x, y, z}})
#define VEC4(x,y,z, w)      ((vec4){.data = {x, y, z, w}})

static HT_INLINE vec3 Vec3Add(vec3 a, vec3 b)
{
    vec3 result = HT_ZERO_INIT;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

static HT_INLINE vec3 Vec3Sub(vec3 a, vec3 b)
{
    vec3 result = HT_ZERO_INIT;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}


static HT_INLINE f32 Vec3Length(vec3 vec)
{
    f32 length = 0;
    f32 lengthSquared = 0;

    lengthSquared = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    length = HtSqrt(lengthSquared);

    return length;
}

static HT_INLINE void Vec3Normalize(vec3 *vec)
{
    const f32 length = Vec3Length(*vec);
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
}

static HT_INLINE void Vec3Negate(vec3 *vec)
{
    vec->x = -vec->x;
    vec->y = -vec->y;
    vec->z = -vec->z;
}

static HT_INLINE f32 Vec3Dot(vec3 a, vec3 b)
{
    f32 result = 0;

    result += a.x * b.x;
    result += a.y * b.y;
    result += a.z * b.z;

    return result;
}

static HT_INLINE vec3 Vec3Cross(vec3 a, vec3 b)
{
    f32 x;
    f32 y;
    f32 z;

    x = (a.y * b.z) - (a.z * a.y);
    y = (a.z * b.x) - (a.x * a.z);
    z = (a.x * b.y) - (a.y * a.x);

    return VEC3(x, y, z);
}

#endif
