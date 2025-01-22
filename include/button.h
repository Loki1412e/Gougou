#ifndef BUTTON_H
    #define BUTTON_H
    #include "my.h"
    #include "sprites.h"
    #include "events.h"

    void draw_button(sfRenderWindow *window, myButton *button);
    void destroy_button(myButton *button);
    int create_button(myButton *button, char *normal_path, char *hovered_path, char *clicked_path, sfVector2f scale, sfVector2f position);
    void handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event, int *program_step, int action);

#endif