#ifndef EVENT_H_
    #define EVENT_H_

    #include "../include/my.h"
    #include "../include/screen.h"

    int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step);

#endif