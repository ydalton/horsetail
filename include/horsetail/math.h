#ifndef _HORSETAIL_MATH_H_
#define _HORSETAIL_MATH_H_

#include "horsetail/defs.h"

HT_BEGIN_DECLS

#define HT_PI           3.14159265358979
#define HT_EPSILON      0.0001

f32 HtSin(f32 x);
f32 HtCos(f32 x);
f32 HtTan(f32 x);
f32 HtSqrt(f32 x);
f32 HtAbs(f32 x);

#include "vector.h"
#include "matrix.h"

HT_END_DECLS

#endif
