
#include "../include/game.h"


int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step, int *sound);


int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step, int *sound) {

    if (sound) {
        // Chemin vers le fichier audio .wav
        char* music = "./assets/music/game.wav";

        FILE* fichier = fopen(music, "r");
        if (!fichier) {
            printf("Erreur : Impossible de trouver le fichier '%s'.\n", music);
            return 1;
        }
        fclose(fichier);

        // Lecture du fichier audio
        PlaySound(music, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    sfVector2u size;
    sfVector2f scale;
    sfVector2f position;

    // Camera (view)
    sfView* view = sfView_create();
    sfView_setSize(view, (sfVector2f) { window_info->size.x , window_info->size.y });

    // Floor
    myObject floor;
    if (create_sprite(&floor, "./assets/game/terre.png", (sfVector2f) {30., 1.5})) { EXIT_DEBUG_TEXTURE };

    // Player
    myPlayer player = {
        .on_jump = 1,
        .dash_cooldown = 0,
        .direction = RIGHT,
        .speed = (sfVector2f) { SPEED_X_player , 0 },
        .hp = HP_player
    };
    if (create_sprite(&(player.object), "./assets/player/tmp.png", (sfVector2f) {6, 6})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, player.object.texture, player.object.sprite, *window_info);

    // Enemy
    myEnemy enemy = {
        .on_jump = 1,
        .direction = LEFT,
        .speed = (sfVector2f) { SPEED_X_player * 0.8 , 0 },
        .hp = HP_player,
        .isAlive = 1
    };
    if (create_sprite(&(enemy.object), "./assets/enemy/dino-idle1.png", (sfVector2f) {6., 6.})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, enemy.object.texture, enemy.object.sprite, *window_info);
    position = sfSprite_getPosition(enemy.object.sprite);
    sfSprite_setPosition(enemy.object.sprite, (sfVector2f) { position.x + 200 , position.y });


    // Création des layers du parallax
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


    // Portal
    myPortal portal = {
        .speed = (sfVector2f) { SPEED_X_player * 0.8 , 0 }
    };
    if (create_sprite(&(portal.object), "./assets/game/portal.png", (sfVector2f) {6., 6.})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, portal.object.texture, portal.object.sprite, *window_info);


    // Start GAME LOOP
    while (sfRenderWindow_isOpen(window) && *program_step == GAME_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            
            switch (event_behavior(window, event, window_info, program_step)) {
            
                case 1:
                    EXIT_DEBUG_WINDOW;
                
                case 2:
                    position = sfSprite_getPosition(player.object.sprite);
                    sfSprite_setPosition(player.object.sprite, (sfVector2f) { position.x / window_info->scale.x, position.y / window_info->scale.y });
                    break;
            }
        }

        // Update les positions du parallax
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

        // Reset pos pour le scrolling infini
        if (pos1.x <= -((float)textureSize1.x)) {
            // Si la position de la première couche dépasse la largeur de la texture vers la gauche
            // Réinitialise la position en ajoutant la largeur de la texture
            pos1.x = pos1.x + (float)textureSize1.x; 
        }
        if (pos1.x > 0) {
            pos1.x = pos1.x - (float)textureSize1.x; 
        }
        if (pos2.x <= -((float)textureSize2.x)) {
            pos2.x = pos2.x + (float)textureSize2.x; 
        }
        if (pos2.x > 0) {
            pos2.x = pos2.x - (float)textureSize2.x;
        }
        if (pos3.x <= -((float)textureSize3.x)) {
            pos3.x = pos3.x + (float)textureSize3.x;
        }
        if (pos3.x > 0) {
            pos3.x = pos3.x - (float)textureSize3.x;
        }

        sfSprite_setPosition(layer1, pos1);
        sfSprite_setPosition(layer2, pos2);
        sfSprite_setPosition(layer3, pos3);



        /* PLAYER */
        player_movements(window, *window_info, &player, floor);
        
        // Mort par vide
        size = sfTexture_getSize(player.object.texture);
        scale = sfSprite_getScale(player.object.sprite);
        position = sfSprite_getPosition(player.object.sprite);
        if (position.y + (size.y * scale.y) > window_info->size.y + 100)
            player.hp = 0;
        
        // fin de partie :/
        if (player.hp <= 0) *program_step = DEATHMENU_step;
        
        
        /* ENEMY */
        if (enemy.hp > 0 && player.hp > 0) interactWithPlayer(&enemy, &player, *window_info);
        if (enemy.isAlive) applyGravityEnemy(window, &enemy, floor, *window_info);


        /* PORTAL if not enemy */
        if (!enemy.isAlive) {
            applyGravityPortal(window, &portal, floor, *window_info);
            endLvlPortal(&portal, &player, program_step);
        }


        /* MAIN */

        // Recharge la camera a partir du Player
        sfView_setSize(view, (sfVector2f) { window_info->size.x , window_info->size.y });
        sfView_setCenter(view, (sfVector2f) { sfSprite_getPosition(player.object.sprite).x , sfSprite_getPosition(player.object.sprite).y - window_info->size.y / 11 });
        sfRenderWindow_setView(window, view);


        /* DRAW */

        // Clear la window
        sfRenderWindow_clear(window, sfBlack);

        // Dessins du parallax 
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
        set_position_bottom(window, floor.texture, floor.sprite, *window_info);
        setup_sprite(window, floor.texture, floor.sprite, *window_info);

        // Dessine le Joueur
        setup_sprite(window, player.object.texture, player.object.sprite, *window_info);

        // Draw enemy
        if (enemy.isAlive) setup_sprite(window, enemy.object.texture, enemy.object.sprite, *window_info);

        // Dessine Portal
        if (!enemy.isAlive) setup_sprite(window, portal.object.texture, portal.object.sprite, *window_info);

        // On applique les dessins
        sfRenderWindow_display(window);

    } // End GAME LOOP


    /* Cleanup Resources */
    destroy_object(&floor);
    destroy_object(&(player.object));
    if (enemy.isAlive) destroy_object(&(enemy.object));
    destroy_object(&(portal.object));
    
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    sfView_destroy(view);

    sfSprite_destroy(layer1);
    sfSprite_destroy(layer2);
    sfSprite_destroy(layer3);
    sfTexture_destroy(texture1);
    sfTexture_destroy(texture2);
    sfTexture_destroy(texture3);

    if (sound) PlaySound(NULL, 0, 0);

    return 0;
}