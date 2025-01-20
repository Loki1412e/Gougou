#include "../include/deathmenu.h"
#include "../include/button.h"

int deathmenu_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step) {
    // Background
    myObject background;
    if (create_sprite(&background, "./assets/deathmenu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Boutons
    myButton retry_btn, menu_btn, quit_btn, settings_btn;
    if (create_button(&retry_btn, "./assets/deathmenu/retry_normal.png", "./assets/deathmenu/retry_hovered.png", "./assets/deathmenu/retry_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 100})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&menu_btn, "./assets/deathmenu/menu_normal.png", "./assets/deathmenu/menu_hovered.png", "./assets/deathmenu/menu_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 350})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&settings_btn, "./assets/deathmenu/settings_normal.png", "./assets/deathmenu/settings_hovered.png", "./assets/deathmenu/settings_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 600})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&quit_btn, "./assets/deathmenu/quit_normal.png", "./assets/deathmenu/quit_hovered.png", "./assets/deathmenu/quit_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {100, 850})) { EXIT_DEBUG_TEXTURE }
    


    while (sfRenderWindow_isOpen(window) && *program_step == DEATHMENU_step) {
        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW }
            printf("Current program step: %d\n", *program_step);


            // Gérer les événements des boutons
            handle_button_event(&retry_btn, window, event, program_step, GAME_step);  // Recommencer le jeu
            handle_button_event(&menu_btn, window, event, program_step, MENU_step);  // Retour au menu
            handle_button_event(&quit_btn, window, event, program_step, QUIT_step);  // Quitter
            handle_button_event(&settings_btn, window, event, program_step, SETTINGS_step); // Aller dans les parametres 
        }

        // Si l'utilisateur veut quitter
        if (*program_step == QUIT_step) {
            sfRenderWindow_close(window);
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

    return 0;
}
