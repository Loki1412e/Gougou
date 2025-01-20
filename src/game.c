
#include "../include/game.h"
#include <SFML/Audio.h>

#define SPEED_LAYER1 1.0f
#define SPEED_LAYER2 0.5f
#define SPEED_LAYER3 0.2f

int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);
void moove_player(sfRenderWindow* window, myWindowInfo window_info, myObject *object);



int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    sfMusic* backgroundMusic = sfMusic_createFromFile("./assets/music/game.ogg");
    if (!backgroundMusic) {
        printf("Erreur: Impossible de charger la musique.\n");
        return 1; // Retourne une erreur si la musique ne se charge pas
    }
    sfMusic_play(backgroundMusic);

    
    // Floor
    myObject floor;
    if (create_sprite(&floor, "./assets/game/floor.png", (sfVector2f) {0.8, 0.8})) { EXIT_DEBUG_TEXTURE };

    // Player
    myObject player;
    if (create_sprite(&player, "./assets/game/player.gif", (sfVector2f) {0.6, 0.6})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, player.texture, player.sprite, *window_info);
 

    // Création des layers du paralax
    sfTexture* texture1 = sfTexture_createFromFile("./assets/parallax/layer1.png", NULL);
    sfTexture* texture2 = sfTexture_createFromFile("./assets/parallax/layer2.png", NULL);
    sfTexture* texture3 = sfTexture_createFromFile("./assets/parallax/layer3.png", NULL);

    if (!texture1 || !texture2 || !texture3) {
        printf("Erreur: Impossible de charger les textures du parallax.\n");
        return 1;
    }

    sfSprite* layer1 = sfSprite_create();
    sfSprite* layer2 = sfSprite_create();
    sfSprite* layer3 = sfSprite_create();

    sfSprite_setTexture(layer1, texture1, sfTrue);
    sfSprite_setTexture(layer2, texture2, sfTrue);
    sfSprite_setTexture(layer3, texture3, sfTrue);

    sfVector2f pos1 = {0, 0};
    sfVector2f pos2 = {0, 0};
    sfVector2f pos3 = {0, 0};

    sfClock* clock = sfClock_create();
    float parallax_speed = 200.0f;

    sfVector2u textureSize1 = sfTexture_getSize(texture1);
    sfVector2u textureSize2 = sfTexture_getSize(texture2);
    sfVector2u textureSize3 = sfTexture_getSize(texture3);

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

        // Update les positions du paralax
        float deltaTime = sfTime_asSeconds(sfClock_restart(clock));
        float offset = parallax_speed * deltaTime;

        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            pos1.x -= SPEED_LAYER1 * offset;
            pos2.x -= SPEED_LAYER2 * offset;
            pos3.x -= SPEED_LAYER3 * offset;
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            pos1.x += SPEED_LAYER1 * offset;
            pos2.x += SPEED_LAYER2 * offset;
            pos3.x += SPEED_LAYER3 * offset;
        }

        // Reset positions for infinite scrolling
        if (pos1.x <= -((float)textureSize1.x)) {
            // Si la position de la première couche dépasse la largeur de la texture vers la gauche
            pos1.x = pos1.x + (float)textureSize1.x; // Réinitialise la position en ajoutant la largeur de la texture
        }
        if (pos1.x > 0) {
            // Si la position de la première couche dépasse 0 vers la droite
            pos1.x = pos1.x - (float)textureSize1.x; // Réinitialise la position en soustrayant la largeur de la texture
        }

        if (pos2.x <= -((float)textureSize2.x)) {
            // Si la position de la deuxième couche dépasse la largeur de la texture vers la gauche
            pos2.x = pos2.x + (float)textureSize2.x; // Réinitialise la position en ajoutant la largeur de la texture
        }
        if (pos2.x > 0) {
            // Si la position de la deuxième couche dépasse 0 vers la droite
            pos2.x = pos2.x - (float)textureSize2.x; // Réinitialise la position en soustrayant la largeur de la texture
        }

        if (pos3.x <= -((float)textureSize3.x)) {
            // Si la position de la troisième couche dépasse la largeur de la texture vers la gauche
            pos3.x = pos3.x + (float)textureSize3.x; // Réinitialise la position en ajoutant la largeur de la texture
        }
        if (pos3.x > 0) {
            // Si la position de la troisième couche dépasse 0 vers la droite
            pos3.x = pos3.x - (float)textureSize3.x; // Réinitialise la position en soustrayant la largeur de la texture
        }

        sfSprite_setPosition(layer1, pos1);
        sfSprite_setPosition(layer2, pos2);
        sfSprite_setPosition(layer3, pos3);

        
        /* MAIN */
        
        sfRenderWindow_clear(window, sfBlack);

        // déssins du  parallax 
       sfRenderWindow_drawSprite(window, layer3, NULL);
        sfSprite_setPosition(layer3, (sfVector2f){pos3.x + (float)textureSize3.x, pos3.y});
        sfRenderWindow_drawSprite(window, layer3, NULL);
        sfSprite_setPosition(layer3, (sfVector2f){pos3.x - (float)textureSize3.x, pos3.y});
        sfRenderWindow_drawSprite(window, layer3, NULL);

        sfRenderWindow_drawSprite(window, layer2, NULL);
        sfSprite_setPosition(layer2, (sfVector2f){pos2.x + (float)textureSize2.x, pos2.y});
        sfRenderWindow_drawSprite(window, layer2, NULL);
        sfSprite_setPosition(layer2, (sfVector2f){pos2.x - (float)textureSize2.x, pos2.y});
        sfRenderWindow_drawSprite(window, layer2, NULL);

        sfRenderWindow_drawSprite(window, layer1, NULL);
        sfSprite_setPosition(layer1, (sfVector2f){pos1.x + (float)textureSize1.x, pos1.y});
        sfRenderWindow_drawSprite(window, layer1, NULL);
        sfSprite_setPosition(layer1, (sfVector2f){pos1.x - (float)textureSize1.x, pos1.y});
        sfRenderWindow_drawSprite(window, layer1, NULL);
        

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

    sfSprite_destroy(layer1);
    sfSprite_destroy(layer2);
    sfSprite_destroy(layer3);
    sfTexture_destroy(texture1);
    sfTexture_destroy(texture2);
    sfTexture_destroy(texture3);

    sfMusic_destroy(backgroundMusic);

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