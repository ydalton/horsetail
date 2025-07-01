#include "horsetail/math.h"

vec3 vec3::operator * (vec3 &other)
{
    vec3 outResult = {};

    outResult.x = x + other.x;
    outResult.y = y + other.y;
    outResult.z = y + other.z;

    return outResult;
}
