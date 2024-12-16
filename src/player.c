#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE 80
#define TIME (1.0 / 32.0)      // Temps en fonction de 32 FPS
#define DASH_FORCE 300.0       // Force appliquée pour le dash
#define DASH_COOLDOWN 3.0      // Cooldown du dash en secondes
#define DASH_DURATION 0.2      // Durée du dash en secondes

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {
    // Récupère la position actuelle du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;
    } else {
        player->velocity.y = 0;
        player->on_jump = 0;
        player->can_dash = 1;         // Recharge le dash lorsqu'on touche le sol
        player->dash_cooldown = 0;    // Réinitialise le cooldown
    }

    // Gestion du saut
    if (sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    // Gestion du dash
    if (player->can_dash && sfKeyboard_isKeyPressed(sfKeyLShift)) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            player->velocity.x = DASH_FORCE * TIME;
            player->can_dash = 0;             // Désactive le dash jusqu'au prochain contact avec le sol
            player->dash_cooldown = DASH_COOLDOWN;
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            player->velocity.x = -DASH_FORCE * TIME;
            player->can_dash = 0;
            player->dash_cooldown = DASH_COOLDOWN;
        }
    }

    // Applique un freinage progressif après le dash
    if (!sfKeyboard_isKeyPressed(sfKeyRight) && !sfKeyboard_isKeyPressed(sfKeyLeft)) {
        player->velocity.x *= 0.9;  // Réduit la vitesse progressivement
    }

    // Applique les vitesses horizontale et verticale
    position.x += player->velocity.x;
    position.y += player->velocity.y * TIME;

    // Met à jour la position du sprite
    sfSprite_setPosition(player->object.sprite, position);
    setup_sprite(window, player->object.texture, player->object.sprite, window_info);
}
