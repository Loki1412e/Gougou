#ifndef SPRITES_H_
    #define SPRITES_H_

    #include "../include/my.h"
    #include "../include/mystructs.h"

    int create_sprite(myObject *object, char *texure_path, sfVector2f scale);
    void destroy_object(myObject *object);
    void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
    void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);

#endif