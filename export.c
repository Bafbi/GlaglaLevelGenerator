#pragma once

#include <stdio.h>
#include "./class/map.c"
#include "./class/vec2.c"

FILE *open_file(FILE *file, const char *filename, char *mode)
{
    file = fopen(filename, mode);

    if (file == NULL)
    {
        perror("fopen");
        return (NULL);
    }
    return file;
}

char *int_to_char(int value)
{
    char *buffer = (char *)calloc(5, sizeof(char));

    sprintf(buffer, "%d", value);

    return buffer;
}

int export_map(Map *map, const char *fileName)
{
    if (map == NULL || fileName == NULL)
        return ERROR;

    FILE *file_data;
    file_data = open_file(file_data, fileName, "w+");

    const char *header = "{\n\t\"header\": {\n\t\"width\": %d,\n\t\"height\" : %d,\n\t \"diff\" : %2d\n\t},\n\t";
    char *header_buff = (char *)calloc(strlen(header), sizeof(char));
    sprintf(header_buff, header, map->size.x, map->size.y, map->diff);
    fprintf(file_data, "%s", header_buff);
    free(header_buff);

    const char *footer = "\"start\":{\"x\":%2d,\"y\":%2d},\"end\":{\"x\":%2d,\"y\":%2d}";
    char *footer_buff = (char *)calloc(strlen(footer), sizeof(char));
    sprintf(footer_buff, footer, map->start.x, map->start.y, map->end.x, map->end.y);

    int _data_size = 6 * map->size.x * map->size.y + 1;

    char *data_buffer = (char *)calloc(_data_size, sizeof(char));
    char *texture_buffer = (char *)calloc(_data_size, sizeof(char));
    int last_mazeblock_index = map->size.y * map->size.x;
    char *default_parsing_string = "%3s,";
    char *_default_parsing_string;

    for (int y = 0; y < map->size.y; y++)
    {
        for (int x = 0; x < map->size.x; x++)
        {
            char c_buffer[6];
            char t_buffer[6];
            _default_parsing_string = default_parsing_string;

            if ((y + 1) * (1 + x) == last_mazeblock_index)
            {
                _default_parsing_string = "%3s";
            }

            if (0 > sprintf(c_buffer, _default_parsing_string, int_to_char(map->data[vec2_calcMapIndex(new_vec2(x, y), map->size.x)])))
            {
                printf("\nerror in sprintf");
            }
            if (strcat(data_buffer, c_buffer) == NULL)
            {
                printf("\nerror data");
            }
            //////////////
            if (0 > sprintf(t_buffer, _default_parsing_string, int_to_char(map->texture[vec2_calcMapIndex(new_vec2(x, y), map->size.x)])))
            {
                printf("\nerror in sprintf");
            }
            if (strcat(texture_buffer, t_buffer) == NULL)
            {
                printf("\nerror texture");
            }
        }
    }

    char *body = "\"body\":{\n\t\t%s,\"texture\":[%s],\"data\":[%s]}}";
    int body_size = strlen(body) + 2 * strlen(data_buffer) + strlen(footer_buff);
    char *body_buff = (char *)calloc(body_size, sizeof(char));

    if (0 > sprintf(body_buff, body, footer_buff, texture_buffer, data_buffer))
    {
        printf("error in sprintf_s");
    }
    free(data_buffer);
    fprintf(file_data, "%s", body_buff);
    free(body_buff);
    free(footer_buff);

    // fprintf(file_data,"%s",footer_buff);

    printf("Done Writing in %s and in x sec!\n", fileName);
    fclose(file_data);
    return 1;
}