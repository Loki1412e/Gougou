#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE  80
#define TIME 1.0/30.0
#define DASH_COOLDOWN 3.0
#define DASH_COOLDOWN 120.0
#define DASH_DURATION 0.2

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);


void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {

    // Récupère la position du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if(!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        sfFloatRect player_bounds = sfSprite_getGlobalBounds(player->object.sprite);
        sfFloatRect floor_bounds =  sfSprite_getGlobalBounds(floor.sprite);
        player->velocity.y = 0;
        player->on_jump = 0;
    }

    if(sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

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