#include "../include/player.h"

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

    // Saut
    if(sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    position.y += player->velocity.y * TIME;


    // Dash mais pas trop
    // Apparement les boutons sfKeyLeft et sfKeySpace ne peuvent pas etre detecter en meme temps
    // Donc pour dash le bouton sera : sfKeyLShift

    if (((sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyLeft)) && \
        !(sfKeyboard_isKeyPressed(sfKeyRight) && sfKeyboard_isKeyPressed(sfKeyLeft))) && \
        sfKeyboard_isKeyPressed(sfKeyLShift) && \
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

        // Deplacements : quand le joueur dash il ne peut pas bouger

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