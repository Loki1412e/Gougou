#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE 80
#define TIME (1.0 / 30.0)
#define DASH_SPEED 300.0
#define DASH_COOLDOWN 3.0
#define DASH_DURATION 0.2

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {
    // Récupère la position actuelle du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
    }

    // Gère le saut
    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    // Gère le dash latéral
    if (sfKeyboard_isKeyPressed(sfKeyLShift) && player->dash_timer == 0) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            player->velocity.x = DASH_SPEED * TIME;
            player->is_dashing = 1;
            player->dash_duration = DASH_DURATION;
            player->dash_timer = DASH_COOLDOWN;
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            player->velocity.x = -DASH_SPEED * TIME;
            player->is_dashing = 1;
            player->dash_duration = DASH_DURATION;
            player->dash_timer = DASH_COOLDOWN;
        }
    }

    // Gère la durée du dash
    if (player->is_dashing) {
        player->dash_duration -= TIME;
        if (player->dash_duration <= 0) {
            player->is_dashing = 0;
            player->velocity.x = 0;  
        }
    }

    // Met à jour le cooldown du dash
    if (player->dash_timer > 0) {
        player->dash_timer -= TIME;
    }

    // Gère les déplacements horizontaux classiques (si pas en dash)
    if (!player->is_dashing) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            position.x += player->speed.x;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            position.x -= player->speed.x;
        }
    }

    // Applique les vitesses horizontale et verticale
    position.x += player->velocity.x;
    position.y += player->velocity.y * TIME;

    // Met à jour la position du sprite
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}
