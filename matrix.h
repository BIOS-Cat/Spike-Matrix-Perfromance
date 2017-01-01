#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

typedef union {
    float v[3];
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
} vec3;

typedef union {
    float v[4];
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
} vec4;

typedef struct {
    float m[9];
} mat3;

typedef struct {
    float m[16];
} mat4;

static inline float dot3(const vec3 *const u, const vec3 *const v)
{
    return u->v[0]*v->v[0] + u->v[1]*v->v[1] + u->v[2]*v->v[2];
}

static inline float dot4(const vec4 *const u, const vec4 *const v)
{
    return u->v[0]*v->v[0] + u->v[1]*v->v[1] + u->v[2]*v->v[2] + u->v[3]*v->v[3];
}

static inline vec3 *cross(vec3 *result, const vec3 *const u, const vec3 *const v)
{
    result->v[0] = u->v[1]*v->v[2] - u->v[2]*v->v[1];
    result->v[1] = u->v[2]*v->v[0] - u->v[0]*v->v[2];
    result->v[2] = u->v[0]*v->v[1] - u->v[1]*v->v[0];

    return result;
}

static inline float norm3(const vec3 *const v)
{
    return (float) sqrt(dot3(v, v));
}

static inline float norm4(const vec4 *const v)
{
    return (float) sqrt(dot4(v, v));
}

static inline vec3 *scale3(vec3 *result, float s, const vec3 *const v)
{
    result->v[0] = s * v->v[0];
    result->v[1] = s * v->v[1];
    result->v[2] = s * v->v[2];

    return result;
}
static inline vec4 *scale4(vec4 *result, float s, const vec4 *const v)
{
    result->v[0] = s * v->v[0];
    result->v[1] = s * v->v[1];
    result->v[2] = s * v->v[2];
    result->v[3] = s * v->v[3];

    return result;
}

static inline vec3 *normalize3(vec3 *result, const vec3 *const v)
{
    return scale3(result, 1.0f / norm3(v), v);
}

static inline vec4 *normalize4(vec4 *result, const vec4 *const v)
{
    return scale4(result, 1.0f / norm4(v), v);
}

static inline mat3 *mat3_mul(mat3 *result, const mat3 *const mat_A, const mat3 *const mat_B)
{
    float a00 = mat_A->m[0]; float a01 = mat_A->m[3]; float a02 = mat_A->m[6];
    float a10 = mat_A->m[1]; float a11 = mat_A->m[4]; float a12 = mat_A->m[7];
    float a20 = mat_A->m[2]; float a21 = mat_A->m[5]; float a22 = mat_A->m[8];

    float b00 = mat_B->m[0]; float b01 = mat_B->m[3]; float b02 = mat_B->m[6];
    float b10 = mat_B->m[1]; float b11 = mat_B->m[4]; float b12 = mat_B->m[7];
    float b20 = mat_B->m[2]; float b21 = mat_B->m[5]; float b22 = mat_B->m[8];

    result->m[0] = a00*b00 + a01*b10 + a02*b20;
    result->m[1] = a10*b00 + a11*b10 + a12*b20;
    result->m[2] = a20*b00 + a21*b10 + a22*b20;

    result->m[3] = a00*b01 + a01*b11 + a02*b21;
    result->m[4] = a10*b01 + a11*b11 + a12*b21;
    result->m[5] = a20*b01 + a21*b11 + a22*b21;

    result->m[6] = a00*b02 + a01*b12 + a02*b22;
    result->m[7] = a10*b02 + a11*b12 + a12*b22;
    result->m[8] = a20*b02 + a21*b12 + a22*b22;

    return result;
}

static inline mat4 *mat4_mul(mat4 *result, const mat4 *const mat_A, const mat4 *const mat_B)
{
    float a00 = mat_A->m[0]; float a01 = mat_A->m[4]; float a02 = mat_A->m[8];  float a03 = mat_A->m[12];
    float a10 = mat_A->m[1]; float a11 = mat_A->m[5]; float a12 = mat_A->m[9];  float a13 = mat_A->m[13];
    float a20 = mat_A->m[2]; float a21 = mat_A->m[6]; float a22 = mat_A->m[10]; float a23 = mat_A->m[14];
    float a30 = mat_A->m[3]; float a31 = mat_A->m[7]; float a32 = mat_A->m[11]; float a33 = mat_A->m[15];

    float b00 = mat_B->m[0]; float b01 = mat_B->m[4]; float b02 = mat_B->m[8];  float b03 = mat_B->m[12];
    float b10 = mat_B->m[1]; float b11 = mat_B->m[5]; float b12 = mat_B->m[9];  float b13 = mat_B->m[13];
    float b20 = mat_B->m[2]; float b21 = mat_B->m[6]; float b22 = mat_B->m[10]; float b23 = mat_B->m[14];
    float b30 = mat_B->m[3]; float b31 = mat_B->m[7]; float b32 = mat_B->m[11]; float b33 = mat_B->m[15];

    result->m[0] = a00*b00 + a01*b10 + a02*b20 + a03*b30;
    result->m[1] = a10*b00 + a11*b10 + a12*b20 + a13*b30;
    result->m[2] = a20*b00 + a21*b10 + a22*b20 + a23*b30;
    result->m[3] = a30*b00 + a31*b10 + a32*b20 + a33*b30;

    result->m[4] = a00*b01 + a01*b11 + a02*b21 + a03*b31;
    result->m[5] = a10*b01 + a11*b11 + a12*b21 + a13*b31;
    result->m[6] = a20*b01 + a21*b11 + a22*b21 + a23*b31;
    result->m[7] = a30*b01 + a31*b11 + a32*b21 + a33*b31;

    result->m[8]  = a00*b02 + a01*b12 + a02*b22 + a03*b32;
    result->m[9]  = a10*b02 + a11*b12 + a12*b22 + a13*b32;
    result->m[10] = a20*b02 + a21*b12 + a22*b22 + a23*b32;
    result->m[11] = a30*b02 + a31*b12 + a32*b22 + a33*b32;

    result->m[12] = a00*b03 + a01*b13 + a02*b23 + a03*b33;
    result->m[13] = a10*b03 + a11*b13 + a12*b23 + a13*b33;
    result->m[14] = a20*b03 + a21*b13 + a22*b23 + a23*b33;
    result->m[15] = a30*b03 + a31*b13 + a32*b23 + a33*b33;

    return result;
}

static inline vec3 *mat3_vec3_mul(vec3 *result, const mat3 *const mat, const vec3 *const v)
{
    float m00 = mat->m[0]; float m01 = mat->m[3]; float m02 = mat->m[6];
    float m10 = mat->m[1]; float m11 = mat->m[4]; float m12 = mat->m[7];
    float m20 = mat->m[2]; float m21 = mat->m[5]; float m22 = mat->m[8];

    float v0 = v->v[0]; float v1 = v->v[1]; float v2 = v->v[2];

    result->v[0] = m00*v0 + m01*v1 + m02*v2;
    result->v[1] = m10*v0 + m11*v1 + m12*v2;
    result->v[2] = m20*v0 + m21*v1 + m22*v2;

    return result;
}

static inline vec4 *mat4_vec4_mul(vec4 *result, const mat4 *const mat, const vec4 *const v)
{
    float m00 = mat->m[0]; float m01 = mat->m[4]; float m02 = mat->m[8];  float m03 = mat->m[12];
    float m10 = mat->m[1]; float m11 = mat->m[5]; float m12 = mat->m[9];  float m13 = mat->m[13];
    float m20 = mat->m[2]; float m21 = mat->m[6]; float m22 = mat->m[10]; float m23 = mat->m[14];
    float m30 = mat->m[3]; float m31 = mat->m[7]; float m32 = mat->m[11]; float m33 = mat->m[15];

    float v0 = v->v[0]; float v1 = v->v[1]; float v2 = v->v[2]; float v3 = v->v[3];

    result->v[0] = m00*v0 + m01*v1 + m02*v2 + m03*v3;
    result->v[1] = m10*v0 + m11*v1 + m12*v2 + m13*v3;
    result->v[2] = m20*v0 + m21*v1 + m22*v2 + m23*v3;
    result->v[3] = m30*v0 + m31*v1 + m32*v2 + m33*v3;

    return result;
}

mat4 *orthographic_projection_matrix(mat4 *result, float left, float right, float bottom, float top, float near, float far);

mat4 *perspection_projection_matrix(mat4 *result, float aspect_ratio, float field_of_view_angle, float near, float far);

#endif /* MATRIX_H */
