
#include "../include/menu.h"
#include "../include/sprites.h"

int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);


int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    sfVector2i mouse_position;
    sfFloatRect bounds_play_btn, bounds_settings_btn, bounds_quit_btn;

    // Background
    myObject background;
    if (create_sprite(&background, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Buttons 
    myObject play_btn, settings_btn, quit_btn;

    if (create_sprite(&play_btn, "./assets/menu/play.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE } 
    if (create_sprite(&settings_btn, "./assets/menu/settings.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }
    if (create_sprite(&quit_btn, "./assets/menu/quit.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }

    sfSprite_setPosition(play_btn.sprite, (sfVector2f) {80, 200});
    sfSprite_setPosition(settings_btn.sprite, (sfVector2f) {80, 450});
    sfSprite_setPosition(quit_btn.sprite, (sfVector2f) {80, 700});

    while (sfRenderWindow_isOpen(window) && *program_step == MENU_step) {

        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event_behavior(window, event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW };

            // Si clique sur bouton
            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
                mouse_position = sfMouse_getPositionRenderWindow(window);

                bounds_play_btn = sfSprite_getGlobalBounds(play_btn.sprite);
                bounds_settings_btn = sfSprite_getGlobalBounds(settings_btn.sprite) ;
                bounds_quit_btn = sfSprite_getGlobalBounds(quit_btn.sprite);

                if (sfFloatRect_contains(&bounds_play_btn, mouse_position.x, mouse_position.y)) {
                    *program_step = GAME_step; // Aller au jeu
                } else if (sfFloatRect_contains(&bounds_settings_btn, mouse_position.x, mouse_position.y)) {
                    *program_step = SETTINGS_step; // Page des paramètres
                } else if (sfFloatRect_contains(&bounds_quit_btn, mouse_position.x, mouse_position.y)) {
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
        setup_sprite(window, play_btn.texture, play_btn.sprite, *window_info);
        setup_sprite(window, settings_btn.texture, settings_btn.sprite, *window_info);
        setup_sprite(window, quit_btn.texture, quit_btn.sprite, *window_info);
        
        sfRenderWindow_display(window); // On recharge la window
    } // End GAME LOOP


    /* Cleanup Resources */

    destroy_object(&background);
    destroy_object(&play_btn);
    destroy_object(&settings_btn);
    destroy_object(&quit_btn);

    return 0;
}