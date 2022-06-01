#pragma once

#include <stdlib.h>
#include "./vec2.c"
#include "./path_buffer.c"
#include "./array.c"
#include "../ConsoleTools.c"
#include "./difficulty.c"

typedef enum Obstacle
{
    OB_GROUND = -3,
    OB_WALL = -2,
    OB_ICY = -1,
    OB_ROCK = 0,
    OB_ARROW = 1
} Obstacle;

typedef struct Map
{
    Vec2 start, end, size;
    int *data;
    int *texture;
    Difficulty diff;
} Map;

void map_print(Map map, PathBuffer pathBuffer);
void map_preFill(Map *map);

Map new_map(Vec2 size, Difficulty diff)
{
    Map map;
    map.data = calloc(sizeof(int), size.x * size.y);
    map.texture = calloc(sizeof(int), size.x * size.y);
    map.diff = diff;
    map.size = size;
    map.start.x = (rand() % (map.size.x - 2)) + 1;
    map.start.y = rand() % 2 ? 0 : map.size.y - 1;
    map.end = new_vec2(0, 0);
    array_fill(map.data, map.size.x * map.size.y, OB_ICY);
    return map;
}

void map_correction(Map *map)
{
    int startIndex = vec2_calcMapIndex(map->start, map->size.x);
    map->data[startIndex] = OB_GROUND;

    map->data[vec2_calcMapIndex(map->end, map->size.x)] = OB_GROUND;
}

void map_GeneratePath(Map *map, PathBuffer *pathBuffer)
{
    Vec2 pos = map->start;
    Vec2 dir;
    if (pos.y < (map->size.y / 2))
    {
        dir = new_vec2(0, 1);
    }
    else
    {
        dir = new_vec2(0, -1);
    }
    pathBuffer_append(pathBuffer, pos);
    pos = vec2_add(pos, dir);
    // map_print(*map, *pathBuffer);

    int nbTurn = 0, move = 1, randNb = 0;
    while (nbTurn < map->diff)
    {
        if (pathBuffer_findTest(*pathBuffer, pos))
            randNb--;
        randNb--;
        if (randNb < 0)
        {
            randNb = (rand() % ((((map->size.x + map->size.y) / 2) / 2) - (((map->size.x + map->size.y) / 2) / 8) + 1)) + (((map->size.x + map->size.y) / 2) / 8);
        }

        Vec2 posTmp = vec2_add(pos, dir);
        if (posTmp.x < 1 || posTmp.x > (map->size.x - 2) || posTmp.y < 1 || posTmp.y > (map->size.y - 1))
            randNb = 0;
        if (map->data[vec2_calcMapIndex(posTmp, map->size.x)] == OB_ROCK)
            randNb = 0;

        if (randNb == 0)
        {
            if (pathBuffer_findTest(*pathBuffer, posTmp))
            {
                map->data[vec2_calcMapIndex(pos, map->size.x)] = OB_GROUND;
            }
            else
            {
                map->data[vec2_calcMapIndex(vec2_add(pos, dir), map->size.x)] = OB_ROCK;
            }

#pragma region Code redondant
            if (dir.y < 0)
            {
                if (pos.x - (map->size.x / 2) < map->size.x / 10)
                {
                    vec2_turnRight(&dir); // Droite
                }
                else
                {
                    vec2_turnLeft(&dir); // Gauche
                }
                goto ok;
            }
            if (dir.y > 0)
            {
                if (pos.x - (map->size.x / 2) > map->size.x / 10)
                {
                    vec2_turnRight(&dir); // Droite
                }
                else
                {
                    vec2_turnLeft(&dir); // Gauche
                }
                goto ok;
            }
            if (dir.x < 0)
            {
                if (pos.y - (map->size.y / 2) > map->size.y / 10)
                {
                    vec2_turnRight(&dir); // Droite
                }
                else
                {
                    vec2_turnLeft(&dir); // Gauche
                }
                goto ok;
            }
            if (dir.x > 0)
            {
                if (pos.y - (map->size.y / 2) < map->size.y / 10)
                {
                    vec2_turnRight(&dir); // Droite
                }
                else
                {
                    vec2_turnLeft(&dir); // Gauche
                }
                goto ok;
            }
            rand() % 2 ? vec2_turnRight(&dir) : vec2_turnLeft(&dir);
#pragma endregion
        ok:
            nbTurn++;
        }
        pathBuffer_append(pathBuffer, pos);
        pos = vec2_add(pos, dir);
        move++;
        // map_print(*map, *pathBuffer);
    }
    if (pathBuffer_findTest(*pathBuffer, pos))
        pos = pathBuffer->data[pathBuffer->size - 2];
    map->end = pos;
    // map_print(*map, *pathBuffer);
}

void map_GenerateObstacle(Map *map, PathBuffer *pathBuffer)
{
    for (int i = 0; i < map->diff * 2; i++)
    {
        Vec2 randPoint = new_randVec2(new_vec2(0, 0), map->size);
        !pathBuffer_findTest(*pathBuffer, randPoint) ? map->data[vec2_calcMapIndex(randPoint, map->size.x)] = OB_ROCK : i--;
    }
}

void map_print(Map map, PathBuffer pathBuffer)
{
    for (int y = 0; y < map.size.y; y++)
    {
        for (int x = 0; x < map.size.x; x++)
        {
            if (map.start.x == x && map.start.y == y)
            {
                printf("S");
                continue;
            }
            if (map.end.x == x && map.end.y == y)
            {
                printf("E");
                continue;
            }
            char car;
            switch (map.data[vec2_calcMapIndex(new_vec2(x, y), map.size.x)])
            {
            case OB_ICY:
                car = ' ';
                break;
            case OB_GROUND:
                car = '_';
                break;
            case OB_ROCK:
                car = '@';
                break;
            default:
                car = '*';
                break;
            }
            printf("%c", car);
        }
        printf("\n");
    }
    printf("------------\n");
    pathBuffer_print(pathBuffer);
    openConsole();
    moveCursor(map.start.x, map.start.y);
    plotChar('S');
    moveCursor(map.end.x, map.end.y);
    plotChar('E');
    moveCursor(0, 0);
    closeConsole();
}
