
#include "../include/sprites.h"


int create_sprite(myObject *object, char *texure_path, sfVector2f scale);
void destroy_object(myObject *object);
void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
void set_position_bottom(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
int check_collision(sfSprite* A, sfSprite* B);


int create_sprite(myObject *object, char *texure_path, sfVector2f scale) {
    object->texture = sfTexture_createFromFile(texure_path, NULL);
    if (!object->texture) return 1;
    object->sprite = sfSprite_create();
    sfSprite_setTexture(object->sprite, object->texture, sfTrue);
    sfSprite_setScale(object->sprite, scale);
    return 0;
}


void destroy_object(myObject *object) {
    sfSprite_destroy(object->sprite);
    sfTexture_destroy(object->texture);
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


// Calcul pour centrer le bg et le btn start (./src/menu.c)
void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info) {

    sfVector2u size = sfTexture_getSize(texture); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sprite); // on recup son scale (son echelle)

    sfVector2f position = {
        window_info.size.x / 2. - size.x * (scale.x * window_info.scale.x) / 2.,
        window_info.size.y / 2. - size.y * (scale.y * window_info.scale.y) / 2.
    };

    sfSprite_setPosition(sprite, position);
}


// Calcul pour centrer le bg et le btn start (./src/menu.c)
void set_position_bottom(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info) {

    sfVector2u size = sfTexture_getSize(texture); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sprite); // on recup son scale (son echelle)

    sfVector2f position = { 0, window_info.size.y - (size.y * scale.y) };

    sfSprite_setPosition(sprite, position);
}


int check_collision(sfSprite* A, sfSprite* B) {

    // recupere les rectangles des sprites
    sfFloatRect bounds_A = sfSprite_getGlobalBounds(A);
    sfFloatRect bounds_B = sfSprite_getGlobalBounds(B);

    // verifie si les rectangles se chevauchent
    return sfFloatRect_intersects(&bounds_A, &bounds_B, NULL);
}

int create_button(myButton *button, char *normal_path, char *hovered_path, char *clicked_path, sfVector2f scale, sfVector2f position) {
    button->texture_normal = sfTexture_createFromFile(normal_path, NULL);
    button->texture_hovered = sfTexture_createFromFile(hovered_path, NULL);
    button->texture_clicked = sfTexture_createFromFile(clicked_path, NULL);

    if (!button->texture_normal || !button->texture_hovered || !button->texture_clicked) {
        return 1;
    }

    button->sprite = sfSprite_create();
    if (!button->sprite) {
        return 1;
    }

    sfSprite_setTexture(button->sprite, button->texture_normal, sfTrue);
    sfSprite_setScale(button->sprite, scale);
    button->position = position;
    sfSprite_setPosition(button->sprite, position);

    return 0;
}



void destroy_button(myButton *button) {
    sfTexture_destroy(button->texture_normal);
    sfTexture_destroy(button->texture_hovered);
    sfTexture_destroy(button->texture_clicked);
    sfSprite_destroy(button->sprite);
}

void draw_button(sfRenderWindow *window, myButton *button) {
    sfRenderWindow_drawSprite(window, button->sprite, NULL);
}