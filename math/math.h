#ifndef MATH_H
#define MATH_H

#include "../base/base_include.h"
  
///////////////////////////////////////////////////////////
// Damian: Some regular macros
//
#define Max(x, y) (x > y ? x : y)
#define Min(x, y) (x < y ? x : y)

#define ValueToMin(value_to_min, possible_min) \
    do { if (value_to_min > possible_min) { value_to_min = possible_min; } } while(false);
#define ValueToMax(value_to_max, possible_max) \
    do { if (value_to_max > possible_max) { value_to_max = possible_max; } } while(false);

#define ValueToMinWithAction(value, possible_min, callback) \
    do { if (value > possible_min) { value = possible_min; callback; } } while(false);

#define AbsF32(x) ( (x > 0.0f ? x : -x) )
#define Square(x) ((x) * (x))

///////////////////////////////////////////////////////////
// Damian: Vec2_F32 stuff
//
struct Vec2_F32 {
    F32 x;
    F32 y;
};
Vec2_F32 vec2_f32(F32 x, F32 y);
Vec2_F32 vec2_f32(F32 x);

Vec2_F32 operator+(Vec2_F32 v1, Vec2_F32 v2);
Vec2_F32 operator-(Vec2_F32 v1, Vec2_F32 v2);
Vec2_F32 operator*(Vec2_F32 v1, Vec2_F32 v2);
Vec2_F32 operator/(Vec2_F32 v1, Vec2_F32 v2);

Vec2_F32& operator+=(Vec2_F32& v1, Vec2_F32 v2);
Vec2_F32& operator-=(Vec2_F32& v1, Vec2_F32 v2);
Vec2_F32& operator*=(Vec2_F32& v1, Vec2_F32 v2);
Vec2_F32& operator/=(Vec2_F32& v1, Vec2_F32 v2);

Vec2_F32 operator+(Vec2_F32 v, F32 mult);
Vec2_F32 operator+(F32 mult, Vec2_F32 v);
Vec2_F32 operator-(Vec2_F32 v, F32 mult);
Vec2_F32 operator-(F32 mult, Vec2_F32 v);
Vec2_F32 operator*(Vec2_F32 v, F32 mult);
Vec2_F32 operator*(F32 mult, Vec2_F32 v);
Vec2_F32 operator/(Vec2_F32 v, F32 mult);
Vec2_F32 operator/(F32 mult, Vec2_F32 v);

Vec2_F32& operator+=(Vec2_F32& v, F32 mult);
Vec2_F32& operator-=(Vec2_F32& v, F32 mult);
Vec2_F32& operator*=(Vec2_F32& v, F32 mult);
Vec2_F32& operator/=(Vec2_F32& v, F32 mult);

B32 operator==(Vec2_F32 v1, Vec2_F32 v2);
B32 operator!=(Vec2_F32 v1, Vec2_F32 v2);

F32 vec2_f32_dot(Vec2_F32 v1, Vec2_F32 v2);
F32 vec2_f32_len_sq(Vec2_F32 v);
F32 vec2_f32_len(Vec2_F32 v);
Vec2_F32 vec2_f32_unit_vec(Vec2_F32 v);


///////////////////////////////////////////////////////////
// Damian: Vec2_S32 stuff
//
struct Vec2_S32 {
    S32 x;
    S32 y;
};
Vec2_S32 vec2_s32(S32 x, S32 y);
Vec2_S32 vec2_s32(S32 x);
Vec2_S32 operator+(Vec2_S32 v1, Vec2_S32 v2);
Vec2_S32 operator-(Vec2_S32 v1, Vec2_S32 v2);
Vec2_S32 operator*(Vec2_S32 v1, Vec2_S32 v2);
Vec2_S32 operator/(Vec2_S32 v1, Vec2_S32 v2);

///////////////////////////////////////////////////////////
// Damian: Vec2_U32 stuff
//
struct Vec2_U32 {
    U32 x;
    U32 y;
};
Vec2_U32 vec2_u32(U32 x, U32 y);
Vec2_U32 vec2_u32(U32 x);

// Vec2_U32 operator+(Vec2_U32 v1, Vec2_U32 v2);
// Vec2_U32 operator-(Vec2_U32 v1, Vec2_U32 v2);
// Vec2_U32 operator*(Vec2_U32 v1, Vec2_U32 v2);
// Vec2_U32 operator/(Vec2_U32 v1, Vec2_U32 v2);

///////////////////////////////////////////////////////////
// Damian: Vec3_F32 stuff 
//
union Vec3_F32 {
    struct {
        F32 x, y, z;
    };

    struct {
        F32 r, g, b;
    };
};
Vec3_F32 vec3_f32(F32 r, F32 g, F32 b, F32 a);

///////////////////////////////////////////////////////////
// Damian: Vec4_F32 stuff
//
union Vec4_F32 {
    struct {
        F32 x, y, z, w;   
    };

    struct {
        F32 r, g, b, a;
    };

    struct {
        F32 r, g, b, a;
    };
};
// Vec4_F32 vec4_f32(F32 r, F32 g, F32 b, F32 a);


///////////////////////////////////////////////////////////
// Damian: Rect_F32
//
struct Rect_F32 {
    Vec2_F32 min; 
    Vec2_F32 dims; 
};
Rect_F32 rect_f32_from_center(Vec2_F32 center_point, Vec2_F32 dims)
{
    Rect_F32 result = {};
    result.min = center_point - (0.5f * dims);
    result.dims = dims;
    return result;
}

B32 rect_f32_does_intersect(Rect_F32 rect_1, Rect_F32 rect_2)
{
    Vec2_F32 rect1_max = rect_1.min + rect_1.dims - 1;
    Vec2_F32 rect2_max = rect_2.min + rect_2.dims - 1;
    if (   rect_1.min.y > rect2_max.y 
        || rect1_max.y < rect_2.min.y
        || rect_1.min.x > rect2_max.x
        || rect1_max.x < rect_2.min.x
    ) {
        return false;
    }
    return true;
}





#endif

























