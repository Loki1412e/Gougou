#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "my.h"
    #include "sprites.h"
    #include "map.h"

    void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, int** map, sfVector2u map_dimensions, sfSprite* map_tile);

#endif