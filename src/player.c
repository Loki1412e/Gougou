#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE 80
#define TIME (1.0 / 32.0)
#define DASH_FORCE 400
#define DASH_DURATION 0.2*32

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {
    // Récupère la position actuelle du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
        player->dash_ready = 1; 
    }

    // Gère le saut
    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    // Gère le dash horizontal avec accélération et durée limitée
    static float dash_timer = 0.0;  

    if (player->dash_ready && sfKeyboard_isKeyPressed(sfKeyLShift)) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            player->velocity.x = DASH_FORCE * TIME;
            player->dash_ready = 0;
            dash_timer = DASH_DURATION;
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            player->velocity.x = -DASH_FORCE * TIME;
            player->dash_ready = 0;
            dash_timer = DASH_DURATION;
        }
    }

    // Réduit le timer du dash
    if (dash_timer > 0) {
        dash_timer -= TIME;
    } else {
        // Si le timer atteint 0, on arrête le dash
        player->velocity.x = 0;
    }

    // Applique la décélération naturelle après le dash si nécessaire
    if (player->velocity.x > 0) {
        player->velocity.x -= 20 * TIME;
        if (player->velocity.x < 0) player->velocity.x = 0;
    } else if (player->velocity.x < 0) {
        player->velocity.x += 20 * TIME;
        if (player->velocity.x > 0) player->velocity.x = 0;
    }

    // Applique les vitesses horizontale et verticale
    position.x += player->velocity.x;
    position.y += player->velocity.y * TIME;

    // Met à jour la position du sprite
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}
