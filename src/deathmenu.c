
#include "../include/deathmenu.h"


int deathmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step);


int deathmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step) {

    sfVector2i mouse_position;
    sfFloatRect bounds_restart_btn;

    // Background
    myObject background;
    if (create_sprite(&background, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Btn Start
    myObject restart_btn;
    if (create_sprite(&restart_btn, "./assets/menu/quit.gif", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }


    while (sfRenderWindow_isOpen(window) && *program_step == DEATHMENU_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW };

            // Si clique sur bouton
            if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
                
                set_position_center(window, restart_btn.texture, restart_btn.sprite, *window_info);
                mouse_position = sfMouse_getPositionRenderWindow(window);

                bounds_restart_btn = sfSprite_getGlobalBounds(restart_btn.sprite);
                
                if (sfFloatRect_contains(&bounds_restart_btn, mouse_position.x, mouse_position.y))
                    *program_step = GAME_step;
            }
        }

        
        /* MAIN */

        sfRenderWindow_clear(window, sfBlack);
                
        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);
                
        // Dessine le boutton start
        set_position_center(window, restart_btn.texture, restart_btn.sprite, *window_info);
        setup_sprite(window, restart_btn.texture, restart_btn.sprite, *window_info);
        

        sfRenderWindow_display(window); // On recharge la window
        
    } // End GAME LOOP


    /* Cleanup Resources */

    sfSprite_destroy(background.sprite);
    sfTexture_destroy(background.texture);

    sfSprite_destroy(restart_btn.sprite);
    sfTexture_destroy(restart_btn.texture);

    return 0;
}