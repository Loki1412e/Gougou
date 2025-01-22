#include "../include/enemies.h"


void applyGravityEnemy(sfRenderWindow* window, myEnemy *enemy, myObject floor, myWindowInfo window_info);
int touchPlayer(myPlayer player, myEnemy enemy);


void applyGravityEnemy(sfRenderWindow* window, myEnemy *enemy, myObject floor, myWindowInfo window_info) {

    sfVector2f position = sfSprite_getPosition(enemy->object.sprite);

    if(!check_collision(enemy->object.sprite, floor.sprite)) {
        enemy->velocity.y += GRAVITY * TIME;
    } else {
        sfFloatRect player_bounds = sfSprite_getGlobalBounds(enemy->object.sprite);
        sfFloatRect floor_bounds =  sfSprite_getGlobalBounds(floor.sprite);
        enemy->velocity.y = 0;
        enemy->on_jump = 0;
    }

    position.y += enemy->velocity.y * TIME;

    sfSprite_setPosition(enemy->object.sprite, position);
    setup_sprite(window, enemy->object.texture, enemy->object.sprite, window_info);
}