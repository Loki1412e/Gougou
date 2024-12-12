
#include "../include/player.h"


void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);


void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {

    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Gravité

    if (player->on_jump) {
        position.y -= player->speed.y;
        (player->on_jump)--;
    }

    else if (!check_collision(player->object.sprite, floor.sprite))
        position.y += player->speed.y;

    else if (sfKeyboard_isKeyPressed(sfKeyUp))
        player->on_jump = JUMP_player;


    // Deplacements

    if (sfKeyboard_isKeyPressed(sfKeyRight))
        position.x += player->speed.x;

    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        position.x -= player->speed.x;

                
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}