
#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_INI  300
#define TIME 1.0 / 30.0
#define MASS 1.0 

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);


void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {
    
    sfVector2f position = sfSprite_getPosition(player->object.sprite);
    sfVector2f acceleration = {0, 0};   

  
    sfVector2f gravity = {0, GRAVITY_FORCE * MASS};
    acceleration.y += gravity.y;

    
    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        acceleration.y = -JUMP_FORCE / MASS;  
        player->on_jump = 1;
    }

    player->velocity.y += acceleration.y * TIME;

    // Met à jour la position en fonction de la vélocité
    position.y += player->velocity.y * TIME;    

    // Gravité

    // if (player->on_jump) {
    //     position.y -= player->speed.y;
    //     (player->on_jump)--;
    // }

    // else if (!check_collision(player->object.sprite, floor.sprite))
    //     position.y += player->speed.y;

    // else if (sfKeyboard_isKeyPressed(sfKeyUp))
    //   player->on_jump = JUMP_player;


    // Deplacements

    if (sfKeyboard_isKeyPressed(sfKeyRight))
        position.x += player->speed.x;

    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        position.x -= player->speed.x;

                
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}