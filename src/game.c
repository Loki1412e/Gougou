#include <windows.h>
#include <mmsystem.h>
#include "../include/game.h"



int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);
void moove_player(sfRenderWindow* window, myWindowInfo window_info, myObject *object);


int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    // Chemin vers le fichier audio .wav
    const char* music = "./assets/music/game.wav";

    FILE* fichier = fopen(music, "r");
    if (!fichier) {
        printf("Erreur : Impossible de trouver le fichier '%s'.\n", music);
        return 1;
    }
    fclose(fichier);

    // Lecture du fichier audio
    if (PlaySound(music, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP)) {
        printf("Lecture du son...\n");
    } else {
        printf("Erreur : Impossible de lire le son.\n");
    }

    // Floor
    myObject floor;
    if (create_sprite(&floor, "./assets/game/floor.png", (sfVector2f) {0.8, 0.8})) { EXIT_DEBUG_TEXTURE };

    // Player
    myObject player;
    if (create_sprite(&player, "./assets/game/player.gif", (sfVector2f) {0.6, 0.6})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, player.texture, player.sprite, *window_info);


    // Start GAME LOOP
    while (sfRenderWindow_isOpen(window) && *program_step == GAME_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            
            switch (event_behavior(window, event, window_info, program_step)) {
            
                case 1:
                    EXIT_DEBUG_WINDOW;
                
                case 2:
                    set_position_center(window, player.texture, player.sprite, *window_info);
                    break;
            }
        }

        
        /* MAIN */
        
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le sol
        set_position_center(window, floor.texture, floor.sprite, *window_info);
        setup_sprite(window, floor.texture, floor.sprite, *window_info);

        // Dessine le Joueur
        setup_sprite(window, player.texture, player.sprite, *window_info);

        // Pour bouger le joueur
        moove_player(window, *window_info, &player);
        
        
        sfRenderWindow_display(window); // On recharge la window

    } // End GAME LOOP


    /* Cleanup Resources */

    sfSprite_destroy(floor.sprite);
    sfTexture_destroy(floor.texture);

    sfSprite_destroy(player.sprite);
    sfTexture_destroy(player.texture);

    return 0;
}


void moove_player(sfRenderWindow* window, myWindowInfo window_info, myObject *object) {

/*///////////////////////////////////////////////////////////////////////////////

    > (window_info.size.x - size.x * scale.x)
                
    - Correspond à la taille de l'écran en x moins la taille du btn en x (size * scale pour avoir la taille du sprite)
    - Ainsi on empeche le sprite de sortir de la fenetre HEHEHEHE

/*///////////////////////////////////////////////////////////////////////////////

    sfVector2u size = sfTexture_getSize(object->texture);
    sfVector2f scale = sfSprite_getScale(object->sprite);
    sfVector2f position = sfSprite_getPosition(object->sprite);
    sfVector2f SPEED = (sfVector2f) { 0.8, 0.8 };

    if (sfKeyboard_isKeyPressed(sfKeyRight) && position.x <= (window_info.size.x - size.x * scale.x) - 100)
        position.x += SPEED.x;

    if (sfKeyboard_isKeyPressed(sfKeyLeft) && position.x >= 100)
        position.x -= SPEED.x;

    if (sfKeyboard_isKeyPressed(sfKeyUp) && position.y >= 100)
        position.y -= SPEED.y;

    if (sfKeyboard_isKeyPressed(sfKeyDown) && position.y <= (window_info.size.y - size.y * scale.y) - 100)
        position.y += SPEED.y;
                
    sfSprite_setPosition(object->sprite, position);
    setup_sprite(window, object->texture, object->sprite, window_info);
}


/*
int on_collision(myObject obj1, myObject obj2) {

    sfVector2u size_obj1 = sfTexture_getSize(obj1.texture), size_obj2 = sfTexture_getSize(obj2.texture);
    sfVector2f scale_obj1 = sfSprite_getScale(obj1.sprite), scale_obj2 = sfSprite_getScale(obj2.sprite);
    sfVector2f position_obj1 = sfSprite_getPosition(obj1.sprite), position_obj2 = sfSprite_getPosition(obj2.sprite);

    if (position_obj1.x <= (size.x - size.x * scale.x) - 100)
        return 'l';

    if (position_obj1.x >= 100)
        return 

    if (position_obj1.y >= 100)
        position.y -= SPEED.y;

    if (position_obj1.y <= (window_info.size.y - size.y * scale.y) - 100)
        position.y += SPEED.y;
        
}
*/