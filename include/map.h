#ifndef MAP_H_
    #define MAP_H_
    
    #include "my.h"
    #include "sprites.h"
    #include "map_textures.h"

    #define BORDER_MAP_SIZE 2

    int countLWithGetC(FILE * f);
    int countCharFirstL_withoutSpace(FILE* f);
    int fileToMap(FILE* f, int **map, sfVector2u* map_dimensions);
    int** allocateMap(sfVector2u map_dimensions);
    void freeMap(int **map, int map_columns);
    int** use_map(char* file_path, sfVector2u* map_dimensions);
    void drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures);
    int check_collisionMap(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myObject object, char direction);
    int set_player_spawn(int** map, sfVector2u map_dimensions, myObject* player);    

#endif