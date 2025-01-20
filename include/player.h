#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "my.h"
    #include "sprites.h"

    void applyTileGravity(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myPlayer *player, sfVector2f* position);
    void player_TileMovements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, int** map, sfVector2u map_dimensions, sfSprite* map_tile);

    void applyGravity(myPlayer *player, sfVector2f* position, myObject floor);
    void playerDash(myPlayer *player, sfVector2f *position);
    void playerMoovRL(myPlayer *player, sfVector2f *position);
    void player_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);

#endif