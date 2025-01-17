#ifndef MAP_H_
    #define MAP_H_
    
    #include "my.h"
    #include "map_textures.h"

    int countLWithGetC(FILE * f);
    int countCharFirstL_withoutSpace(FILE* f);
    int fileToMap(FILE* f, int **map, sfVector2u* map_dimensions);
    int** allocateMap(sfVector2u map_dimensions);
    void freeMap(int **map, int map_columns);
    int** use_map(char* file_path, sfVector2u* map_dimensions);
    int drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures);

#endif