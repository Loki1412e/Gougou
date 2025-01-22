
#include "../include/game.h"


int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);


int game_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

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


        /* MAIN */

        // Recharge la camera a partir du Player
        sfView_setSize(view, (sfVector2f) { window_info->size.x , window_info->size.y });
        sfView_setCenter(view, (sfVector2f) { sfSprite_getPosition(player.object.sprite).x , sfSprite_getPosition(player.object.sprite).y - window_info->size.y / 11 });
        sfRenderWindow_setView(window, view);


        /* DRAW */

        // Clear la window
        sfRenderWindow_clear(window, sfBlack);

        // Dessine le sol
        set_position_bottom(window, floor.texture, floor.sprite, *window_info);
        setup_sprite(window, floor.texture, floor.sprite, *window_info);

        // Dessine le Joueur
        setup_sprite(window, player.object.texture, player.object.sprite, *window_info);

        // Draw enemy
        if (enemy.isAlive) setup_sprite(window, enemy.object.texture, enemy.object.sprite, *window_info);

        // On applique les dessins
        sfRenderWindow_display(window);

    } // End GAME LOOP


    /* Cleanup Resources */
    destroy_object(&floor);
    destroy_object(&(player.object));
    destroy_object(&(enemy.object));
    
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    sfView_destroy(view);

    return 0;
}