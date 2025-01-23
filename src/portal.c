#include "../include/portal.h"


void applyGravityPortal(sfRenderWindow* window, myPortal *portal, myObject floor, myWindowInfo window_info);
void endLvlPortal(myPortal *portal, myPlayer *player, int *program_step);


void endLvlPortal(myPortal *portal, myPlayer *player, int *program_step) {
    if (check_collision(player->object.sprite, portal->object.sprite))
        *program_step = WINMENU_step;
}


void applyGravityPortal(sfRenderWindow* window, myPortal *portal, myObject floor, myWindowInfo window_info) {

    sfVector2f position = sfSprite_getPosition(portal->object.sprite);

    // Si portal touche pas floor on applique la gravité
    if (!check_collision(portal->object.sprite, floor.sprite)) {
        portal->velocity.y += GRAVITY * TIME;
        position.y += portal->velocity.y * TIME;
        sfSprite_setPosition(portal->object.sprite, position);
    }
    
    else
        portal->velocity.y = 0;
}