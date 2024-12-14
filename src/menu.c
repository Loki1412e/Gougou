
#include "../include/menu.h"


int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);
void click_on_btn_start(sfRenderWindow* window, sfEvent *event, sfTexture *tex_start_btn, sfSprite *sp_start_btn, unsigned *program_step);


int menu_view(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    // Background
    myObject background;
    if (create_sprite(&background, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Btn Start
    myObject start_btn;
    if (create_sprite(&start_btn, "./assets/menu/start.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }


    while (sfRenderWindow_isOpen(window) && *program_step == MENU_step) {


        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event_behavior(window, event, window_info, program_step) == 1) { EXIT_DEBUG_WINDOW };
        }

        
        /* MAIN */

        sfRenderWindow_clear(window, sfBlack);
                
        // Dessine le background
        set_position_center(window, background.texture, background.sprite, *window_info);
        setup_sprite(window, background.texture, background.sprite, *window_info);
                
        // Dessine le boutton start
        set_position_center(window, start_btn.texture, start_btn.sprite, *window_info);
        setup_sprite(window, start_btn.texture, start_btn.sprite, *window_info);
                
        // onclick btn_start
        click_on_btn_start(window, &event, start_btn.texture, start_btn.sprite, program_step);
        

        sfRenderWindow_display(window); // On recharge la window
        
    } // End GAME LOOP


    /* Cleanup Resources */

    sfSprite_destroy(background.sprite);
    sfTexture_destroy(background.texture);

    sfSprite_destroy(start_btn.sprite);
    sfTexture_destroy(start_btn.texture);

    return 0;
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
        *program_step = GAME_step;
    }
}