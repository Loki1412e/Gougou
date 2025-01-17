#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "my.h"
    #include "sprites.h"

    #define GRAVITY 9.81
    #define JUMP_FORCE  80
    #define TIME 1.0/FPS

    void player_basics_movements(sfRenderWindow *window, myWindowInfo window_info, myPlayer *player, myObject floor);

#endif