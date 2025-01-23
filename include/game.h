#ifndef GAME_VIEW_H_
    #define GAME_VIEW_H_

    #include "my.h"
    #include "events.h"
    #include "sprites.h"
    #include "player.h"
    #include "enemies.h"
    #include "portal.h"

    int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);

#endif