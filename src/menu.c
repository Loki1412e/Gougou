
#include "../include/menu.h"


int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);


int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    sfVector2i mouse_position;
    sfFloatRect bounds_start_btn;

    // Background
    myObject background;
    if (create_sprite(&background, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Btn Start
    myObject start_btn;
    if (create_sprite(&start_btn, "./assets/menu/test.png", (sfVector2f) {1, 1})) { EXIT_DEBUG_TEXTURE }


    while (sfRenderWindow_isOpen(window) && *program_step == MENU_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event_behavior(window, event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW };

            // Si clique sur bouton
            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
                
                set_position_center(window, start_btn.texture, start_btn.sprite, *window_info);
                mouse_position = sfMouse_getPositionRenderWindow(window);

                bounds_start_btn = sfSprite_getGlobalBounds(start_btn.sprite);
                
                if (sfFloatRect_contains(&bounds_start_btn, mouse_position.x, mouse_position.y))
                    *program_step = GAME_step;
            }
        }

        
        /* MAIN */

        sfRenderWindow_clear(window, sfBlack);
                
        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);
                
        // Dessine le boutton start
        set_position_center(window, start_btn.texture, start_btn.sprite, *window_info);
        setup_sprite(window, start_btn.texture, start_btn.sprite, *window_info);
        

        sfRenderWindow_display(window); // On recharge la window
        
    } // End GAME LOOP


    /* Cleanup Resources */

    sfSprite_destroy(background.sprite);
    sfTexture_destroy(background.texture);

    sfSprite_destroy(start_btn.sprite);
    sfTexture_destroy(start_btn.texture);

    return 0;
}