#ifndef SPRITES_H_
    #define SPRITES_H_

    #include "../include/my.h"

    int create_sprite(myObject *object, char *texure_path, sfVector2f scale);
    void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
    void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);

#endif