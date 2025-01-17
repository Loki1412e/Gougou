#include "../include/player.h"

#define GRAVITY 9.81
#define JUMP_FORCE 80
#define TIME (1.0 / 32.0)      // Temps en fonction de 32 FPS
#define DASH_FORCE 30.0        // Force appliquée pour le dash (diminuée)
#define DASH_COOLDOWN 5.0      // Cooldown du dash en secondes
#define DASH_DURATION 0.2      // Durée du dash (en secondes)
#define DASH_DECAY 0.9         // Décélération progressive après le dash

void player_basics_movements(sfRenderWindow* window, myWindowInfo window_info, myPlayer *player, myObject floor) {

    // Récupère la position du joueur
    sfVector2f position = sfSprite_getPosition(player->object.sprite);

    // Applique la gravité si le joueur ne touche pas le sol
    if (!check_collision(player->object.sprite, floor.sprite)) {
        player->velocity.y += GRAVITY * TIME;  // Applique la gravité à la vitesse verticale
    } else {
        if (player->velocity.y > 0) {
            player->velocity.y = 0;  // Arrête la descente du joueur si il touche le sol
            player->on_jump = 0;      // Le joueur n'est plus en l'air
        }
    }

    // Mise à jour du cooldown du dash
    if (player->dash_cooldown > 0) {
        player->dash_cooldown -= TIME;  // Diminue le cooldown à chaque frame
    } else {
        player->can_dash = 1;  // Le dash est prêt à être utilisé après que le cooldown soit terminé
    }

    // Saut
    if(sfKeyboard_isKeyPressed(sfKeyUp) && player->on_jump == 0) {
        player->velocity.y = -JUMP_FORCE;
        player->on_jump = 1;
    }

    // Gestion du dash (seulement si le dash est disponible)
    if (player->can_dash && sfKeyboard_isKeyPressed(sfKeyLShift)) {
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            // Commence le dash
            if (player->dash_timer <= 0) {
                player->dash_timer = DASH_DURATION;  // Commence le dash
                player->velocity.x = DASH_FORCE;  // Vitesse horizontale du dash
                player->can_dash = 0;             // Désactive le dash immédiatement
                player->dash_cooldown = DASH_COOLDOWN;  // Active le cooldown de 5 secondes
            }
        } else if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            // Commence le dash
            if (player->dash_timer <= 0) {
                player->dash_timer = DASH_DURATION;  // Commence le dash
                player->velocity.x = -DASH_FORCE;  // Vitesse horizontale du dash
                player->can_dash = 0;             // Désactive le dash immédiatement
                player->dash_cooldown = DASH_COOLDOWN;  // Active le cooldown de 5 secondes
            }
        }
    }

    // Applique le mouvement linéaire pendant le dash (le mouvement ne sera pas instantané)
    if (player->dash_timer > 0) {
        // Applique la vitesse horizontale pendant la durée du dash
        position.x += player->velocity.x * TIME;

        // Réduit progressivement la vitesse du dash avec la décélération
        player->velocity.x *= DASH_DECAY;  // Diminue progressivement la vitesse horizontale

        player->dash_timer -= TIME;  // Diminue la durée du dash

        // Une fois le dash terminé, réinitialise la vitesse horizontale
        if (player->dash_timer <= 0) {
            player->velocity.x = 0;  // Réinitialise la vitesse horizontale une fois le dash terminé
        }
    } else {
        // Déplacements horizontaux normaux lorsque le dash est terminé
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            position.x += player->speed.x;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            position.x -= player->speed.x;
        }
    }

    // Applique les vitesses horizontale et verticale (y compris pendant le dash)
    position.x += player->velocity.x;
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