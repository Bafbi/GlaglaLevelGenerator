#include <stdio.h>
#include <time.h>
#include "./class/map.c"
#include "./class/vec2.c"
#include "./class/path_buffer.c"
#include "./export.c"
#include "./class/difficulty.c"

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        printf("\n[+] Usage: {height} {width} {difficulty} {filename}\n");
        printf("[+] Difficulty: \"EASY\", \"MEDIUM\", \"HARD\"\n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    printf("%s | %s | %s | %s\n", argv[1], argv[2], argv[3], argv[4]);

    Map map = new_map(new_vec2(atoi(argv[1]), atoi(argv[2])), str_to_diff(argv[3]));
    PathBuffer pathBuffer = new_PathBuffer((Difficulty)argv[3]);
    // system("clear");
    map_GeneratePath(&map, &pathBuffer);
    map_GenerateObstacle(&map, &pathBuffer);
    map_correction(&map);
    // map_print(map, pathBuffer);
    map_texturing(&map);
    export_map(&map, argv[4]);
    // system("pause");

    return 0;
}
