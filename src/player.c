
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

    // Dash mais pas trop

    // if (player->dash_duration)
    //     player->dash_duration -= 1;
    
    // else if (sfKeyboard_isKeyPressed(sfKeySpace)) {
    //     player->dash_duration = 200;
    //     dash = 100;
    // }


    if (((sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyLeft)) && \
        !(sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyLeft))) && \
        sfKeyboard_isKeyPressed(sfKeySpace) && \
        !player->dash_cooldown
    ) {
        player->dash_duration = DASH_DURATION_player;
        player->dash_cooldown = DASH_COOLDOWN_player;
    }

    else if (player->dash_cooldown) {

        player->dash_cooldown -= 1;

        if (player->dash_duration) {

        // printf("cool = %d\ndura = %d\n\n", player->dash_cooldown, player->dash_duration);
        
            player->dash_duration -= 1;
        
            switch (player->direction) {
                case RIGHT:
                    position.x += player->speed.x * DASH_SPEED_player;
                    break;
                
                case LEFT:
                    position.x -= player->speed.x * DASH_SPEED_player;
                    break;
            }
        }
    }

    if (!player->dash_duration) {

        // Deplacements

        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            position.x += player->speed.x;
            player->direction = RIGHT;
        }

        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            position.x -= player->speed.x;
            player->direction = LEFT;
        }
    
    }
                
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}