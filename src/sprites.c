
#include "../include/sprites.h"


void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);


// Mise en place d'un sprite
void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info) {

    sfVector2f scale;

    set_bg(window, texture, sprite, window_info);
    scale = sfSprite_getScale(sprite);

    // on applique la mise a l'echelle de la taille de la fenetre
    sfSprite_setScale(sprite, (sfVector2f) {
        scale.x * window_info.scale.x,
        scale.y * window_info.scale.y
    });

    // on dessine le sprite
    sfRenderWindow_drawSprite(window, sprite, NULL);
                
    // on remet les valeurs scale initiales
    sfSprite_setScale(sprite, (sfVector2f) {
        scale.x,
        scale.y
    });
}