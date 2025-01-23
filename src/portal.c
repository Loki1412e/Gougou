#include "../include/portal.h"


void applyGravityPortal(sfRenderWindow* window, myPortal *portal, myObject floor, myWindowInfo window_info);
void endLvlPortal(myPortal *portal, myPlayer *player, int *program_step);


void endLvlPortal(myPortal *portal, myPlayer *player, int *program_step) {

    sfVector2f position = sfSprite_getPosition(portal->object.sprite);
    sfVector2u size = sfTexture_getSize(portal->object.texture);
    sfVector2f scale = sfSprite_getScale(portal->object.sprite);

    sfVector2f mid_portal = {
        position.x + (size.x * scale.x) / 2.,
        position.y + (size.y * scale.y) / 2.
    };

    position = sfSprite_getPosition(player->object.sprite);
    size = sfTexture_getSize(player->object.texture);
    scale = sfSprite_getScale(player->object.sprite);

    if (mid_portal.x >= position.x && mid_portal.x <= position.x + (size.x * scale.x) && \
        mid_portal.y >= position.y && mid_portal.y <= position.y + (size.y * scale.y)
    ) *program_step = WINMENU_step;
}


void applyGravityPortal(sfRenderWindow* window, myPortal *portal, myObject floor, myWindowInfo window_info) {

    sfVector2f position = sfSprite_getPosition(portal->object.sprite);

    // Si portal touche pas floor on applique la gravité
    if (!check_collision(portal->object.sprite, floor.sprite)) {
        portal->velocity.y += GRAVITY * TIME / 4.;
        position.y += portal->velocity.y * TIME;
        sfSprite_setPosition(portal->object.sprite, position);
    }
    
    else
        portal->velocity.y = 0;
}