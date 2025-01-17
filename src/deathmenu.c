
#include "../include/deathmenu.h"


int deathmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step);


int deathmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step) {

    sfVector2i mouse_position;
    sfFloatRect bounds_retry_btn, bounds_menu_btn, bounds_quit_btn;

    // Background
    myObject background;
    if (create_sprite(&background, "./assets/deathmenu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Boutons
    myObject retry_btn, menu_btn, quit_btn;
  
    if(create_sprite(&retry_btn, "./assets/deathmenu/retry.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }
    if(create_sprite(&menu_btn, "./assets/deathmenu/menu.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }
    if(create_sprite(&quit_btn, "./assets/deathmenu/quit.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }

    sfSprite_setPosition(retry_btn.sprite, (sfVector2f) {100, 400});
    sfSprite_setPosition(menu_btn.sprite, (sfVector2f) {100, 500});
    sfSprite_setPosition(quit_btn.sprite, (sfVector2f) {100, 600});

    while (sfRenderWindow_isOpen(window) && *program_step == DEATHMENU_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW };

            // Si clique sur bouton
            if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
                mouse_position = sfMouse_getPositionRenderWindow(window);
               
                bounds_retry_btn = sfSprite_getGlobalBounds(retry_btn.sprite);
                bounds_menu_btn = sfSprite_getGlobalBounds(menu_btn.sprite);
                bounds_quit_btn = sfSprite_getGlobalBounds(quit_btn.sprite);

                if (sfFloatRect_contains(&bounds_retry_btn, mouse_position.x, mouse_position.y)) {
                    *program_step = GAME_step; // Recommencer le jeu
                } else if (sfFloatRect_contains(&bounds_menu_btn, mouse_position.x, mouse_position.y)) {
                    *program_step = SETTINGS_step; // Retourner au menu
                } else if (sfFloatRect_coutains(&bounds_quit_btn, mouse_position.x, mouse_position.y)) {
                    sfRenderWindow_close(window); // Quitter le jeu
                }
            }
        }

        
        /* MAIN */

        sfRenderWindow_clear(window, sfBlack);
                
        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);
                
        // Dessine les boutons
        setup_sprite(window, retry_btn.texture, retry_btn.sprite, *window_info);
        setup_sprite(window, menu_btn.texture, menu_btn.sprite, *window_info);
        setup_sprite(window, quit_btn.texture, quit_btn.sprite, *window_info);

        sfRenderWindow_display(window); // On recharge la window
        
    } // End GAME LOOP

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_object(&retry_btn);
    destroy_object(&menu_btn);
    destroy_object(&quit_btn);

    return 0;
}