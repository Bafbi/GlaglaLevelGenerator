#pragma once

#include "./vec2.c"

typedef Vec2 Mat2[2];
// {
//     Vec2 data[2];
// } Mat2;

void mat2_set(Mat2 mat, Vec2 a, Vec2 b)
{
    mat[0] = a;
    mat[1] = b;
}

Vec2 mat2_multiByVec2(Mat2 mat, Vec2 vec)
{
    Vec2 newVec;
    newVec.x = mat[0].x * vec.x + mat[1].x * vec.y;
    newVec.y = mat[0].y * vec.x + mat[1].y * vec.y;
    return newVec;
}
