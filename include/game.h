#ifndef GAME_VIEW_H_
    #define GAME_VIEW_H_

    #include "../include/my.h"
    #include "../include/mystructs.h"
    #include "../include/events.h"
    #include "../include/sprites.h"

    int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);
    void moove_player(sfRenderWindow* window, myWindowInfo window_info, myObject *object);

#endif