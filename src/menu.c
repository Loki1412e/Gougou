
#include "../include/menu.h"


void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_step);


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
        switch (*program_step)
        {
        case MENU_step:
            *program_step = TEMP_step;
            break;
        
        case TEMP_step:
            *program_step = MENU_step;
            break;
        
        default:
            *program_step = MENU_step;
        }
    }
}