#ifndef GAME_VIEW_H_
    #define GAME_VIEW_H_

    #include "../include/my.h"
    #include "../include/events.h"
    #include "../include/sprites.h"
    #include "../include/player.h"

    int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);

#endif