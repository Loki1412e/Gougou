
#include "../include/sprites.h"


int create_sprite(myObject *object, char *string);
void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);


int create_sprite(myObject *object, char *texure_path) {
    object->texture = sfTexture_createFromFile(texure_path, NULL);
    if (!object->texture) return 1;
    object->sprite = sfSprite_create();
    sfSprite_setTexture(object->sprite, object->texture, sfTrue);
    return 0;
}


// Calcul pour centrer le bg et le btn start (./src/menu.c)
void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info) {

    sfSprite_setTexture(sprite, texture, sfTrue);

    sfVector2u size = sfTexture_getSize(texture); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sprite); // on recup son scale (son echelle)

    sfVector2f position = {
        window_info.size.x / 2. - size.x * (scale.x * window_info.scale.x) / 2.,
        window_info.size.y / 2. - size.y * (scale.y * window_info.scale.y) / 2.
        // window_info.size.x / 2. - size.x * (scale.x) / 2.,
        // window_info.size.y / 2. - size.y * scale.y / 2.
    };

    sfSprite_setPosition(sprite, position);
}


// Mise en place d'un sprite
// on doit appeler le set avant -> ex: set_bg(window, texture, sprite, window_info);
void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info) {

    sfVector2f scale;

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