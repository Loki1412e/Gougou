
#include "../include/menu.h"


void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, myWindowInfo window_info);
void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, myWindowInfo window_info);
void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_step);

// Calcul pour centrer le bg (./src/menu.c)
void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, myWindowInfo window_info) {

    sfSprite_setTexture(sp_bg, tex_bg, sfTrue);

    sfVector2u size = sfTexture_getSize(tex_bg); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sp_bg); // on recup son scale (son echelle)

    sfVector2f position = {
        window_info.size.x / 2. - size.x * (scale.x * window_info.scale.x) / 2.,
        window_info.size.y / 2. - size.y * (scale.y * window_info.scale.y) / 2.
        // window_info.size.x / 2. - size.x * (scale.x) / 2.,
        // window_info.size.y / 2. - size.y * scale.y / 2.
    };

    sfSprite_setPosition(sp_bg, position);
}


// Calcul pour positionner le btn start (./src/menu.c)
void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, myWindowInfo window_info) {

    sfVector2u size = sfTexture_getSize(tex_start_btn); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sp_start_btn); // on recup son scale (son echelle)

    sfVector2f position = { // Comme le btn a été scale on inclus son scale dans les calculs
        window_info.size.x / 2. - size.x * (scale.x * window_info.scale.x) / 2.,
        window_info.size.y / 2. - size.y * (scale.y * window_info.scale.y) / 2.
        // window_info.size.x / 2. - size.x * scale.x / 2.,
        // window_info.size.y / 2. - size.y * scale.y / 2.
    };
    
    sfSprite_setPosition(sp_start_btn, position);
}


void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_step) {
    
    // Coordonnée de la souris
    sfVector2i mouse_position = sfMouse_getPositionRenderWindow(window);
    
    // Btn start
    sfVector2u size = sfTexture_getSize(tex_start_btn);
    sfVector2f scale = sfSprite_getScale(sp_start_btn);
    sfVector2f position = sfSprite_getPosition(sp_start_btn);

    // si la souris est dans cette zone (qui correspond au btn start)
    // et que mouse est onclick
    if ((  (float) mouse_position.x >= position.x \
        && (float) mouse_position.x <= position.x + (float) size.x * scale.x \
        && (float) mouse_position.y >= position.y \
        && (float) mouse_position.y <= position.y + (float) size.y * scale.y
        && event->type == sfEvtMouseButtonPressed )
        // ou si la touche ENTER est press
        || (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter)
        ) {

        /* Change the program_step */
        *program_step = TEMP_step;
    }
}