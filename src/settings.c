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
    myButton back_btn, btn_1920x1200,  btn_1280x800, btn_1680x1050, music_btn;
     
    if (create_button(&back_btn, "./assets/buttons/retry_normal.png", "./assets/buttons/retry_hovered.png", "./assets/buttons/retry_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {50, 50})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&btn_1680x1050, "./assets/buttons/1680_normal.png", "./assets/buttons/1680_hovered.png", "./assets/buttons/1680_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {750, 150})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&btn_1920x1200, "./assets/buttons/1920_normal.png", "./assets/buttons/1920_hovered.png", "./assets/buttons/1920_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {1050, 150})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&btn_1280x800, "./assets/buttons/1280_normal.png", "./assets/buttons/1280_hovered.png", "./assets/buttons/1280_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {450, 150})) { EXIT_DEBUG_TEXTURE }
    if (create_button(&music_btn, "./assets/buttons/music_normal.png", "./assets/buttons/music_hovered.png", "./assets/buttons/music_clicked.png", (sfVector2f) {8., 8.}, (sfVector2f) {50, 750})) { EXIT_DEBUG_TEXTURE }
    

    while (sfRenderWindow_isOpen(window) && *program_step == SETTINGS_step) {
        // Process events
        while (sfRenderWindow_pollEvent(window, event)) {
            if (event_behavior(window, *event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW }

            // Gérer les événements des boutons
            handle_button_event(&back_btn, window, event, program_step, MENU_step); // Recommencer le jeu
            handle_button_event(&btn_1680x1050, window, event, program_step, _1680); 
            handle_button_event(&btn_1920x1200, window, event, program_step, _1920); 
            handle_button_event(&btn_1280x800, window, event, program_step, _1280);
            handle_button_event(&music_btn, window, event, program_step, MENU_step); 
        }

        // Dessin
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);

        // Dessine les boutons
        sfRenderWindow_drawSprite(window, back_btn.sprite, NULL);
        sfRenderWindow_drawSprite(window, btn_1680x1050.sprite, NULL);
        sfRenderWindow_drawSprite(window, btn_1920x1200.sprite, NULL);
        sfRenderWindow_drawSprite(window, btn_1280x800.sprite, NULL);
        sfRenderWindow_drawSprite(window, music_btn.sprite, NULL);

        sfRenderWindow_display(window); // Affichage
    }

    /* Cleanup Resources */
    destroy_object(&background);
    destroy_button(&back_btn);
    destroy_button(&btn_1680x1050);
    destroy_button(&btn_1920x1200);
    destroy_button(&btn_1280x800);
    destroy_button(&music_btn);

    if (sound) PlaySound(NULL, 0, 0);

    return EXIT_SUCCESS;
}
