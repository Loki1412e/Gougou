#ifndef MENU_H_
    #define MENU_H_

    #include "../include/my.h"
    #include "../include/config_screen.h"

    // Gerer le resize
    void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, myWindowInfo window_info);
    void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, myWindowInfo window_info);

    // Interaction avec le bouton start
    void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture* tex_start_btn, sfSprite* sp_start_btn, unsigned *program_step);

#endif