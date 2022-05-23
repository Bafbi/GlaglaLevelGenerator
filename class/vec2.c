#pragma once

#include "../ConsoleTools.c"

typedef struct Vec2
{
    int x, y;
} Vec2;

Vec2 new_vec2(int x, int y)
{
    Vec2 vec = {x, y};
    return vec;
}

Vec2 new_randVec2(Vec2 min, Vec2 max)
{
    Vec2 vec;
    vec.x = (rand() % (max.x - min.x + 1)) + min.x;
    vec.y = (rand() % (max.y - min.y + 1)) + min.y;
    return vec;
}

int vec2_calcMapIndex(Vec2 vec, int width)
{
    return vec.y * width + vec.x;
}

Vec2 vec2_add(Vec2 vecA, Vec2 vecB)
{
    Vec2 vec;
    vec.x = vecA.x + vecB.x;
    vec.y = vecA.y + vecB.y;
    return vec;
}

Vec2 vec2_sub(Vec2 vecA, Vec2 vecB)
{
    Vec2 vec;
    vec.x = vecA.x - vecB.x;
    vec.y = vecA.y - vecB.y;
    return vec;
}

bool vec2_eq(Vec2 vecA, Vec2 vecB)
{
    return (vecA.x == vecB.x && vecA.y == vecB.y);
}

#include "./mat2.c"

void vec2_turnLeft(Vec2 *vec)
{
    Mat2 matA;
    mat2_set(matA, new_vec2(0, -1), new_vec2(1, 0));
    *vec = mat2_multiByVec2(matA, *vec);
}

void vec2_turnRight(Vec2 *vec)
{
    Mat2 matA;
    mat2_set(matA, new_vec2(0, 1), new_vec2(-1, 0));
    *vec = mat2_multiByVec2(matA, *vec);
}

void vec2_print(Vec2 vec)
{
    printf("[%d, %d]\n", vec.x, vec.y);
}