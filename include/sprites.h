#ifndef SPRITES_H_
    #define SPRITES_H_

    #include "my.h"

    int create_sprite(myObject *object, char *texure_path, sfVector2f scale);
    void destroy_object(myObject *object);
    void setup_sprite(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
    void set_position_center(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
    void set_position_bottom(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite, myWindowInfo window_info);
    int check_collision(sfSprite* A, sfSprite* B);
    int create_button(myButton *button, char *normal_path, char *hovered_path, char *clicked_path, sfVector2f scale, sfVector2f position);
    void draw_button(sfRenderWindow *window, myButton *button);
    void destroy_button(myButton *button);

#endif