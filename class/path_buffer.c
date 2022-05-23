#pragma once

#include "./vec2.c"

typedef struct PathBuffer
{
    Vec2 *data;
    int size;
} PathBuffer;

PathBuffer new_PathBuffer(int diff)
{
    PathBuffer buffer;
    buffer.data = malloc(sizeof(Vec2) * diff * 10);
    buffer.size = 0;
    return buffer;
}

void pathBuffer_append(PathBuffer *buffer, Vec2 value)
{
    buffer->data[buffer->size] = value;
    buffer->size++;
}

bool pathBuffer_findTest(PathBuffer buffer, Vec2 vec)
{
    for (int i = 0; i < buffer.size; i++)
    {
        if (vec2_eq(buffer.data[i], vec))
        {
            return true;
        }
    }
    return false;
}

void pathBuffer_print(PathBuffer buffer)
{
    openConsole();

    for (int i = 0; i < buffer.size; i++)
    {
        moveCursor(buffer.data[i].x, buffer.data[i].y + 10);
        plotChar('#');
    }
    moveCursor(0, 0);
    closeConsole();
}