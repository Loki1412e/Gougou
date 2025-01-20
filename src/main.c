
#include "../include/main.h"


int main(int argc, char **argv) {

    myWindowInfo window_info = _1920x1200;
    sfRenderWindow* window;
    sfEvent event;

    int program_step = MENU_step;


    /* Create the main window */
    window = sfRenderWindow_create((sfVideoMode) {window_info.size.x, window_info.size.y, 32}, "Googoo Gagaga", sfClose, NULL);
    if (!window) { EXIT_DEBUG_WINDOW }


    /* Start GAME LOOP */
    while (sfRenderWindow_isOpen(window)) {

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Close window
            if (event.type == sfEvtClosed || (sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyEnter)))
                sfRenderWindow_close(window);
        }

        /* PROGRAM STEPS */
        switch (program_step) {

            case MENU_step:
                if (menu_view(window, &event, &window_info, &program_step)) return EXIT_FAILURE;
                break;
            
            case GAME_step:
                if (game_view(window, event, &window_info, &program_step)) return EXIT_FAILURE;
                break;
            
            case TMP_game:
                if (tmp_game(window, event, &window_info, &program_step)) return EXIT_FAILURE;
                break;

            case SETTINGS_step:
                if (settings_view(window, &event, &window_info, &program_step)) return EXIT_FAILURE;
                break;

            case DEATHMENU_step:
                if (deathmenu_view(window, &event, &window_info, &program_step)) return EXIT_FAILURE;
                break;
        }
    
    } // End GAME LOOP

    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}