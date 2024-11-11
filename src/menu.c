
#include "../include/menu.h"


sfVector2f window_pourcent_scale(sfRenderWindow* window, sfVector2u *window_size);
void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, sfVector2u *window_size);
void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, sfVector2u *window_size);
void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_setp);


sfVector2f window_pourcent_scale(sfRenderWindow* window, sfVector2u *window_size) {
    
    sfVector2u position = sfRenderWindow_getSize(window);
    sfVector2f pourcent_scale;

    if (position.x != window_size->x) {
        pourcent_scale.x = position.x / window_size->x;
        window_size->x = position.x;
    }

    if (position.y != window_size->y) {
        pourcent_scale.y = position.y / window_size->y;
        window_size->y = position.y;
    }
    
    return pourcent_scale;
}

// Calcul pour centrer le bg
void set_bg(sfRenderWindow* window, sfTexture *tex_bg, sfSprite *sp_bg, sfVector2u *window_size) {

    sfSprite_setTexture(sp_bg, tex_bg, sfTrue);

    sfVector2f window_scale = window_pourcent_scale(window, window_size);
    sfVector2u size = sfTexture_getSize(tex_bg); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sp_bg); // on recup son scale (son echelle)

    sfSprite_setScale(sp_bg, (sfVector2f) {
        // scale.x * window_scale.x,
        // scale.y * window_scale.y
        scale.x,
        scale.y
    }); // on applique une mise à l'echelle

    scale = sfSprite_getScale(sp_bg); // on recup son nouveau scale
    sfVector2f position = {
        (float) (window_size->x - size.x) * scale.x / 2.,
        (float) (window_size->y - size.y) * scale.y / 2.
    };

    sfSprite_setPosition(sp_bg, position);
}

// Calcul pour positionner le btn start
void set_start_btn(sfRenderWindow* window, sfTexture *tex_start_btn, sfSprite *sp_start_btn, sfVector2u *window_size) {

    sfSprite_setTexture(sp_start_btn, tex_start_btn, sfTrue);

    sfVector2f window_scale = window_pourcent_scale(window, window_size);
    sfVector2u size = sfTexture_getSize(tex_start_btn); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(sp_start_btn); // on recup son scale (son echelle)
    
    sfSprite_setScale(sp_start_btn, (sfVector2f) {
        // scale.x * window_scale.x,
        // scale.y * window_scale.y
        scale.x,
        scale.y
    });

    scale = sfSprite_getScale(sp_start_btn);
    sfVector2f position = { // Comme le btn a été scale on inclus son scale dans les calculs
        (float) window_size->x / 2. - scale.x * (float) size.x /2.,
        (float) window_size->y / 2. - scale.y * (float) size.y /2.
    };
    
    sfSprite_setPosition(sp_start_btn, position);
}


void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_setp) {
    
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
        // ou si la touche enter est entrée
        || (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter)
        ) {

        /* Change the program_setp */
        *program_setp = TEMP_step;
    }
}