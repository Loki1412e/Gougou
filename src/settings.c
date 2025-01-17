#include "../include/settings.h"

int settings_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);

int settings_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {
    sfVector2i mouse_position;
    sfFloatRect bounds_back_btn;

    // Background 
    myObject background;
    if (create_sprite(&background, "./assets/settings/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Back Button
    myObject back_btn;
    if (create_sprite(&back_btn, "./assets/settings/back.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }

    sfSprite_setPosition(back_btn.sprite, (sfVector2f) {50, 50});
    
    while (sfRenderWindow_isOpen(window) && *program_step == SETTINGS_step) {
        // Gestion des événements
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event_behavior(window, event, window_info, program_step) == 1) { EXIT_DEBUG_TEXTURE }

            // Si on clique sur le bouton "Retour"
            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
                mouse_position = sfMouse_getPositionRenderWindow(window);
                bounds_back_btn = sfSprite_getGlobalBounds(back_btn.sprite);

                if (sfFloatRect_contains(&bounds_back_btn, mouse_position.x, mouse_position.y)) {
                    *program_step = MENU_step; // Retour au menu principal
                }
            }
        }

        /* MAIN */
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);

        // Dessine le bouton "Retour"
        setup_sprite(window, back_btn.texture, back_btn.sprite, *window_info);

        sfRenderWindow_display(window); // On recharge la fenêtre
    }

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_object(&back_btn);
    return 0;
}