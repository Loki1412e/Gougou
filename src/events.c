
#include "../include/events.h"


int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step);


// return 1 => EXIT_DEBUG_WINDOW
// return 2 => SUCCESS : Window Update
int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step) {
    
    if (event.type == sfEvtClosed || (sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyEnter)))
        sfRenderWindow_close(window);

    if (event.type == sfEvtKeyPressed) {

        switch (event.key.code) {

            case sfKeyNum1:
                *program_step = MENU_step;
                break;
                
            case sfKeyNum2:
                *program_step = GAME_step;
                break;
            
            case sfKeyNum3:
                *program_step = TMP_game;
                break;
                
            case sfKeyNum4:
                *program_step = DEATHMENU_step;
                break;

        }
                
        // NUMP PAD -> voir screen.c
        if (resize_screen(event.key.code, window_info)) {
            sfRenderWindow_destroy(window);
            window = sfRenderWindow_create((sfVideoMode) {window_info->size.x, window_info->size.y, 32}, "Googoo Gagaga", sfClose, NULL);
            if (!window) return 1;
            return 2;
        }
    }

    return 0;
}

void handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event) {
    sfVector2i m
}