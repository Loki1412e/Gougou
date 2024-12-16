#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE 80
#define TIME (1.0 / 30.0)
#define DASH_FORCE 400.0       // Force horizontale appliquée pour le dash
#define DASH_DURATION 0.2      // Durée du dash en secondes
#define DASH_COOLDOWN 3.0      // Cooldown du dash en secondes

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {
    // Récupère la position actuelle du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
        player->dash_ready = 1;        // Recharge le dash lorsqu'on touche le sol
        player->dash_cooldown_timer = 0; // Réinitialise le cooldown
    }

    // Gère le saut
    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    // Gère le dash avec cooldown
    static float dash_timer = 0.0;               // Timer pour la durée du dash
    static float dash_cooldown_timer = 0.0;      // Timer pour le cooldown du dash

    if (player->dash_ready && dash_cooldown_timer <= 0 && sfKeyboard_isKeyPressed(sfKeyLShift)) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            player->velocity.x = DASH_FORCE * TIME;
            player->dash_ready = 0;
            dash_timer = DASH_DURATION;
            dash_cooldown_timer = DASH_COOLDOWN;
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            player->velocity.x = -DASH_FORCE * TIME;
            player->dash_ready = 0;
            dash_timer = DASH_DURATION;
            dash_cooldown_timer = DASH_COOLDOWN;
        }
    }

    // Réduit le timer du dash
    if (dash_timer > 0) {
        dash_timer -= TIME;
    } else {
        // Arrête le dash après la durée écoulée
        player->velocity.x = 0;
    }

    // Réduit le cooldown du dash
    if (dash_cooldown_timer > 0) {
        dash_cooldown_timer -= TIME;
    }

    // Deplacements

    if (sfKeyboard_isKeyPressed(sfKeyRight))
        position.x += player->speed.x;

    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        position.x -= player->speed.x;

                
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}