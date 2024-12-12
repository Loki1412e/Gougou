/*
    Sujet : Projet en C / ESGI 2i1 / 2024-2025
    Auteur : JAIEL FERRO Milhane
    Date de création : 09/11/2024 (c'est pas vrai oof mais tqt)
*/


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

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_display(window);

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            // Close window
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* PROGRAM STEPS */
        switch (program_step) {

            case MENU_step:
                if (menu_view(window, event, &window_info, &program_step)) return EXIT_FAILURE;
                break;
            
            case GAME_step:
                if (game_view(window, event, &window_info, &program_step)) return EXIT_FAILURE;
                break;
        }

    } // End GAME LOOP

    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
