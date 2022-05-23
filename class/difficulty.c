#pragma once

typedef enum Difficulty
{
    EASY = 3,
    MEDIUM = 6,
    HARD = 9
} Difficulty;

Difficulty str_to_diff(const char *diff)
{
    if (strcmp(diff, "EASY") == 0)
        return EASY;
    if (strcmp(diff, "MEDIUM") == 0)
        return MEDIUM;
    if (strcmp(diff, "HARD") == 0)
        return HARD;
}