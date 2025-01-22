#ifndef EVENT_H_
    #define EVENT_H_

    #include "my.h"
    #include "screen.h"
    #include "settings.h"

    int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step);
    void handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event, int *program_step, int action);;

#endif