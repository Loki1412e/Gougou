#include "../include/settings.h"
#include "../include/button.h"

int settings_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int sound);

int settings_view(sfRenderWindow* window, sfEvent *event, myWindowInfo *window_info, int *program_step, int sound) {
    
    // Chemin vers le fichier audio .wav
    char* music = "./assets/music/menu.wav";

    FILE* fichier = fopen(music, "r");
    if (!fichier) {
        printf("Erreur : Impossible de trouver le fichier '%s'.\n", music);
        return 1;
    }
    fclose(fichier);

    // Lecture du fichier audio
    PlaySound(music, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
    // Background
    myObject background;
    if (create_sprite(&background, "./assets/settings/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Boutons
    myButton back_btn;
    if (create_button(&back_btn, "./assets/buttons/retry_normal.png", "./assets/buttons/retry_hovered.png", "./assets/buttons/retry_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {50, 50})) { EXIT_DEBUG_TEXTURE }
    
    while (sfRenderWindow_isOpen(window) && *program_step == SETTINGS_step) {
        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW }

            // Gérer les événements des boutons
            handle_button_event(&back_btn, window, event, program_step, MENU_step);  // Recommencer le jeu
        }

        // Dessin
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);

        // Dessine les boutons
        sfRenderWindow_drawSprite(window, back_btn.sprite, NULL);

        sfRenderWindow_display(window); // Affichage
    }

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_button(&back_btn);

    if (sound) PlaySound(NULL, 0, 0);

    return EXIT_SUCCESS;
}
