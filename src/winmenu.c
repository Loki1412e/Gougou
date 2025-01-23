#include "../include/winmenu.h"

int winmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int *sound);

int winmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int *sound) {
    // Background
    myObject background;
    if (create_sprite(&background, "./assets/winmenu/win.png", (sfVector2f) {0.8, 0.8})) { EXIT_DEBUG_TEXTURE }

    // Boutons
    myButton retry_btn, menu_btn, quit_btn, settings_btn;
    if (create_button(&retry_btn, "./assets/buttons/retry_normal.png", "./assets/buttons/retry_hovered.png", "./assets/buttons/retry_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 100})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&menu_btn, "./assets/buttons/menu_normal.png", "./assets/buttons/menu_hovered.png", "./assets/buttons/menu_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 350})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&settings_btn, "./assets/buttons/settings_normal.png", "./assets/buttons/settings_hovered.png", "./assets/buttons/settings_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 600})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&quit_btn, "./assets/buttons/quit_normal.png", "./assets/buttons/quit_hovered.png", "./assets/buttons/quit_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 850})) { EXIT_DEBUG_TEXTURE }
    

    while (sfRenderWindow_isOpen(window) && *program_step == WINMENU_step) {
        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW }

            // Gérer les événements des boutons
            handle_button_event(&retry_btn, window, event, program_step, GAME_step, window_info, sound);  // Recommencer le jeu
            handle_button_event(&menu_btn, window, event, program_step, MENU_step, window_info, sound);  // Retour au menu
            handle_button_event(&quit_btn, window, event, program_step, QUIT_step, window_info, sound);  // Quitter
            handle_button_event(&settings_btn, window, event, program_step, SETTINGS_step, window_info, sound); // Aller dans les parametres 

        }

        // Dessin
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);

        // Dessine les boutons
        sfRenderWindow_drawSprite(window, retry_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, menu_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, settings_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, quit_btn.sprite, NULL);

        sfRenderWindow_display(window); // Affichage
    }

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_button(&retry_btn);
    destroy_button(&menu_btn);
    destroy_button(&settings_btn);
    destroy_button(&quit_btn);

    return EXIT_SUCCESS;
}   
