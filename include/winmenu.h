#ifndef WINMENU_H_
    #define WINMENU_H_

    #include "my.h"
    #include "events.h"
    #include "button.h"

    int winmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int sound);

#endif