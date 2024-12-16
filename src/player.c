
#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_INI  300
#define TIME 0,327

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);


void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {

    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
    }

    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_INI;
        player->on_jump = 1; 
    }
    
    position.y += player->velocity.y;

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