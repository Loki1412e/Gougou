#include "../include/player.h"

void applyTileGravity(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myPlayer *player, sfVector2f* position);
void player_TileMovements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, int** map, sfVector2u map_dimensions, sfSprite* map_tile);

void applyGravity(myPlayer *player, sfVector2f* position, myObject floor);
void playerDash(myPlayer *player, sfVector2f *position);
void playerMoovRL(myPlayer *player, sfVector2f *position);
void player_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor);


// Applique la gravité si le joueur ne touche pas le sol
void applyGravity(myPlayer *player, sfVector2f* position, myObject floor) {

    if(!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
    }

    // Saut
    if(sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    position->y += player->velocity.y * TIME;
}


// Applique la gravité si le joueur ne touche pas le sol
void applyTileGravity(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myPlayer *player, sfVector2f* position) {

    if(!check_collisionMap(map, map_dimensions, map_tile, player->object, BOTTOM)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
    }

    // Saut
    if(sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    position->y += player->velocity.y * TIME;
}


// Dash mais pas trop
// Apparement les boutons sfKeyLeft et sfKeySpace ne peuvent pas etre detecter en meme temps
// Donc pour dash le bouton sera : sfKeyLShift
void playerDash(myPlayer *player, sfVector2f *position) {

    if (!player->dash_cooldown && \
        (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyLeft)) && \
        sfKeyboard_isKeyPressed(sfKeyLShift)
    ) {
        player->dash_duration = DASH_DURATION_player;
        player->dash_cooldown = DASH_COOLDOWN_player;
        player->on_jump = 2;
        player->velocity.y = 0;
    }

    else if (player->dash_cooldown) {

        player->dash_cooldown -= 1;

        if (player->dash_duration) {

        // printf("cool = %d\ndura = %d\n\n", player->dash_cooldown, player->dash_duration);
        
            player->dash_duration -= 1;
        
            switch (player->direction) {
                case RIGHT:
                    position->x += player->speed.x * DASH_SPEED_player;
                    break;
                
                case LEFT:
                    position->x -= player->speed.x * DASH_SPEED_player;
                    break;
            }
        }
    }
}

void playerMoovRL(myPlayer *player, sfVector2f *position) {
    
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        position->x += player->speed.x;
        player->direction = RIGHT;
        }

    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        position->x -= player->speed.x;
        player->direction = LEFT;
    }
}


void player_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {

    // Récupère la position du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Dash du joueur
    playerDash(player, &position);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!player->dash_duration) applyGravity(player, &position, floor);
    
    // Deplacements : quand le joueur dash il ne peut pas bouger
    if (!player->dash_duration) playerMoovRL(player, &position);

    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}


void player_TileMovements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, int** map, sfVector2u map_dimensions, sfSprite* map_tile) {

    // Récupère la position du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Dash du joueur
    playerDash(player, &position);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!player->dash_duration) applyTileGravity(map, map_dimensions, map_tile, player, &position);
    
    // Deplacements : quand le joueur dash il ne peut pas bouger
    if (!player->dash_duration) playerMoovRL(player, &position);

    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}