#include "../include/enemies.h"


void applyGravityEnemy(sfRenderWindow* window, myEnemy *enemy, myObject floor, myWindowInfo window_info);
void interactWithPlayer(myEnemy *enemy, myPlayer *player, myWindowInfo window_info);


void interactWithPlayer(myEnemy *enemy, myPlayer *player, myWindowInfo window_info) {
    
    sfVector2f position_player = sfSprite_getPosition(player->object.sprite);
    sfVector2u size_player = sfTexture_getSize(player->object.texture);
    sfVector2f scale_player = sfSprite_getScale(player->object.sprite);

    sfVector2f position_enemy = sfSprite_getPosition(enemy->object.sprite);

    position_player.y = position_player.y + (size_player.y * scale_player.y);

    if (sfKeyboard_isKeyPressed(sfKeyA)) printf("P(%.2f)\nE(%.2f)\n\n", position_player.y, position_enemy.y);
    
    if (!check_collision(player->object.sprite, enemy->object.sprite)) return; // pas en collision

    if (position_player.y <= position_enemy.y + 50)
        enemy->hp = 0; // enemy est mort        
    
    else player->hp = 0; // player est mort
}


void applyGravityEnemy(sfRenderWindow* window, myEnemy *enemy, myObject floor, myWindowInfo window_info) {

    sfVector2f position = sfSprite_getPosition(enemy->object.sprite);

    sfVector2f pos_floor = sfSprite_getPosition(floor.sprite);

    if (position.y >= pos_floor.y + window_info.size.y / 2.) {
        destroy_object(&(enemy->object));
        enemy->isAlive = 0;
        return;
    };

    // Si enemy est mort ou ne touche pas le sol il subit la gravité
    if ((enemy->hp == 0 && enemy->isAlive) || !check_collision(enemy->object.sprite, floor.sprite)) {
        enemy->velocity.y += GRAVITY * TIME;
        position.y += enemy->velocity.y * TIME;
        sfSprite_setPosition(enemy->object.sprite, position);
    } else {
        enemy->velocity.y = 0;
        enemy->on_jump = 0;
    }
}