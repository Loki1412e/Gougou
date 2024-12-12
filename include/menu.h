#ifndef MENU_H_
    #define MENU_H_

    #include "../include/my.h"
    #include "../include/mystructs.h"
    #include "../include/events.h"
    #include "../include/sprites.h"

    int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);
    void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture* tex_start_btn, sfSprite* sp_start_btn, unsigned *program_step);

#endif