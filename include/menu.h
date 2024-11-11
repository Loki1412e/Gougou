#ifndef MENU_H_
    #define MENU_H_

    #include "../include/my.h"

    // Gerer le resize
    sfVector2f window_pourcent_scale(sfRenderWindow* window, sfVector2u *window_size);
    void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, sfVector2u *window_size);
    void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, sfVector2u *window_size);

    // Interaction avec le bouton start
    void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture* tex_start_btn, sfSprite* sp_start_btn, unsigned *program_setp);

#endif