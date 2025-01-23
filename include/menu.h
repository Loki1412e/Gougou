#ifndef MENU_H_
    #define MENU_H_

    #include "my.h"
    #include "events.h"
    #include "sprites.h"
    #include "button.h"

    int menu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int sound);

#endif