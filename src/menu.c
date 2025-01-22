#include "../include/menu.h"
#include "../include/button.h"
#include "../include/sprites.h"

int menu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step);

int menu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step) {
    // Background
    myObject background;
    if (create_sprite(&background, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Boutons
    myButton play_btn, settings_btn, quit_btn;

    if (create_button(&play_btn, "./assets/buttons/play_normal.png", "./assets/buttons/play_hovered.png", "./assets/buttons/play_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {80, 200})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&settings_btn, "./assets/buttons/settings_normal.png", "./assets/buttons/settings_hovered.png", "./assets/buttons/settings_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {80, 450})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&quit_btn, "./assets/buttons/quit_normal.png", "./assets/buttons/quit_hovered.png", "./assets/buttons/quit_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {80, 700})) { EXIT_DEBUG_TEXTURE }

    while (sfRenderWindow_isOpen(window) && *program_step == MENU_step) {
        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW }

            // Gérer les événements des boutons
            handle_button_event(&play_btn, window, event, program_step, GAME_step);      // Aller au jeu
            handle_button_event(&settings_btn, window, event, program_step, SETTINGS_step); // Aller aux paramètres
            handle_button_event(&quit_btn, window, event, program_step, QUIT_step);     // Quitter
        }
        // Dessin
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);

        // Dessine les boutons
        sfRenderWindow_drawSprite(window, play_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, settings_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, quit_btn.sprite, NULL);

        sfRenderWindow_display(window); // Affichage
    }

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_button(&play_btn);
    destroy_button(&settings_btn);
    destroy_button(&quit_btn);

    return 0;
}
