#if !defined(BASE_MATH_H)
#define BASE_MATH_H

#include <math.h>
#include "base_types.h"

///////////////////////////////
// NOTE: Math Functions
///////////////////////////////

// TODO: replace these with functions for less bugs and better debuggability
#define MIN(a,b) (((a)<=(b))?(a):(b))
#define MAX(a,b) (((a)>=(b))?(a):(b))
#define CLAMP(a,x,b) (((x)<(a))?(a):((x)>(b))?(b):(x))
#define ABS(x) ((x)<0?-(x):(x))
#define AlignUpPow2(x,p) (((x) + (p) - 1)&~((p) - 1))
#define AlignDownPow2(x,p) ((x)&~((p) - 1))

global f32 PI_f32 = 3.14159265359f;
global f64 PI_f64 = 3.14159265359;
global f32 RAD = 0.0174533f;

static f32
degree_to_rad(f32 degree){
    f32 result = ((PI_f32/180.0f) * degree);
    return(result);
}

static f32
rad_to_degree(f32 rad){
    f32 result = ((180.0f/PI_f32) * rad);
    return(result);
}

static f32 sqrt_f32(f32 x){ return(sqrt(x)); }
static f32 sin_f32(f32 theta){
    f32 reslut = sinf(theta);
    return(sinf(theta));
}
static f32 cos_f32(f32 theta){
    f32 reslut = cosf(theta);
    return(cosf(theta));
}
static f32 tan_f32(f32 theta){
    f32 result = tanf(theta);
    f32 r = sin_f32(theta)/cos_f32(theta);
    f32 rr = rad_to_degree(r);
    return(sin_f32(theta)/cos_f32(theta));
}
static f32 cot_f32(f32 theta){ return(cos_f32(theta)/sin_f32(theta)); }
static f32 atan_f32(f32 x, f32 y){
    f32 result = atan2f(x, y);
    return(result);
}

static f64 sqrt_f64(f64 x){ return(sqrt(x)); }
static f64 sin_f64(f64 x){ return(sin(x)); }
static f64 cos_f64(f64 x){ return(cos(x)); }
static f64 tan_f64(f64 x){ return(sin_f64(x)/cos_f64(x)); }
static f64 cot_f64(f64 x){ return(cos_f64(x)/sin_f64(x)); }
static f64 atan_f64(f64 x, f64 y){ return(atan2(x, y)); }

static v2
rad_to_dir(f32 rad){
    return((v2){cos_f32(rad), sin_f32(rad)});
}

static f32
dir_to_rad(v2 dir){
    return(atan_f32(dir.y, dir.x));
}

static f32
abs_f32(f32 x){
    union{ f32 f; u32 u; } r;
    r.f = x;
    r.u &= 0x7fffffff;
    return(r.f);
}

static f64
abs_f64(f64 x){
    union{ f64 f; u64 u; } r;
    r.f = x;
    r.u &= 0x7fffffffffffffff;
    return(r.f);
}

static s32
abs_s32(s32 x){
    s32 result = ((x<0)?(-x):(x));
    return(result);
}

static s64
abs_s64(s64 x){
    s64 result = ((x<0)?(-x):(x));
    return(result);
}

static v2
round_v2(v2 value){
    v2 result = {};
    result.x = (f32)((s32)(value.x + 0.5f));
    result.y = (f32)((s32)(value.y + 0.5f));
    return(result);
}

// UNTESTED:
static v2s32
round_v2_v2s32(v2 value){
    v2s32 result = {};
    result.x = ((s32)(value.x + 0.5f));
    result.y = ((s32)(value.y + 0.5f));
    return(result);
}

static f32
round_f32(f32 value){
    f32 result = (f32)((s32)(value + 0.5f));
    return(result);
}

static s32
round_f32_s32(f32 value){
    s32 result = (s32)(value + 0.5f);
    return(result);
}

static s64
round_f64_s64(f64 value){
    s64 result = (s64)(value + 0.5f);
    return(result);
}

static u32
round_f32_u32(f32 value){
    u32 result = (u32)(value + 0.5f);
    return(result);
}

static f32
trunc_f32(f32 value){
    f32 result = (f32)(s32)value;
    return(result);
}

static s32
trunc_f32_s32(f32 value){
    s32 result = (s32)value;
    return(result);
}

static f32
floor_f32(f32 value){
    f32 result = floorf(value);
    return(result);
}

static s32
floor_f32_s32(f32 value){
    s32 result = (s32)floorf(value);
    return(result);
}

static f32
ceil_f32(f32 value){
    f32 result = ceilf(value);
    return(result);
}

static s32
ceil_f32_s32(f32 value){
    s32 result = (s32)floorf(value);
    return(result);
}

static f32
clamp_f32(f32 left, f32 value, f32 right){
    if(value < left) { value = left; }
    if(value > right) { value = right; }
    return((s32)value);
}

// UNTESTED:
static s32
clamp_f32_s32(f32 left, f32 value, f32 right){
    if(value < left) { value = left; }
    if(value > right) { value = right; }
    return(value);
}

static f32
lerp(f32 a, f32 t, f32 b){
    f32 x = ((a + ((b - a) * t)));
    return(x);
}

static f32
unlerp(f32 a, f32 at, f32 b){
    f32 t = 0.0f;
    if(a != b){
        t = (at - a) / (b - a);
    }
    return(t);
}

// UNTESTED: idk what to even test because I dont understand what this is doing
// STUDY: idk whats going on here mathematically. Study it.
// NOTE: Sphere linear interpolation
static f32
lerp_rad(f32 a, f32 t, f32 b) {
    f32 difference = fmodf(b - a, 2 * PI_f32);
    f32 distance = fmodf(2.0f * difference, 2 * PI_f32) - difference;
    return a + distance * t;
}


#endif
