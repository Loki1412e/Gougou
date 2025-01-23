#ifndef EVENT_H_
    #define EVENT_H_

    #include "my.h"
    #include "screen.h"
    #include "sprites.h"
    #include "config.h"

    int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step);
    int handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event, int *program_step, int action,  myWindowInfo *window_info, int *sound);
    int handle_button_Sound(myButton *mute_btn, myButton *unmute_btn, sfRenderWindow *window, sfEvent *event, int *sound, char *music);

#endif