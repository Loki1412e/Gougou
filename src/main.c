/*
    Sujet : Projet en C / ESGI 2i1 / 2024-2025
    Auteur : JAIEL FERRO Milhane
    Date de création : 09/11/2024 (c'est pas vrai oof mais tqt)
*/


#include "../include/main.h"


int main() {

    myWindowInfo window_info = _1920x1200;
    sfRenderWindow* window;
    sfEvent event;

    // Background
    sfTexture* tex_bg;
    sfSprite* sp_bg;
    
    // Btn start
    sfTexture* tex_start_btn;
    sfSprite* sp_start_btn;

    int program_step = MENU_step;

    
    sfVector2f position;
    unsigned SPEED;


    // Background
    tex_bg = sfTexture_createFromFile("./assets/menu/background.png", NULL);
    if (!tex_bg) { EXIT_DEBUG_TEXTURE; }
    sp_bg = sfSprite_create();
    sfSprite_setTexture(sp_bg, tex_bg, sfTrue);

    // Btn Start
    tex_start_btn = sfTexture_createFromFile("./assets/menu/start.png", NULL);
    if (!tex_start_btn) { EXIT_DEBUG_TEXTURE; }
    sp_start_btn = sfSprite_create();
    sfSprite_setTexture(sp_start_btn, tex_start_btn, sfTrue);
    sfSprite_setScale(sp_start_btn, (sfVector2f) {0.3, 0.3}); // on applique une mise à l'echelle


    /* Create the main window */
    window = sfRenderWindow_create((sfVideoMode) {window_info.size.x, window_info.size.y, 32}, "Googoo Gagaga", sfClose, NULL);
    if (!window) { EXIT_DEBUG_WINDOW; }


    /* Start the game loop */
    while (sfRenderWindow_isOpen(window)) {

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {

            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);

            if (sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyEnter))
                sfRenderWindow_close(window);
            
            if (event.type == sfEvtKeyPressed) {

                switch (event.key.code)
                {
                case sfKeyNum1:
                    program_step = MENU_step;
                    break;
                
                case sfKeyNum2:
                    program_step = TEMP_step;
                    break;
                
                case sfKeyEnter:
                    program_step = TEMP_step;
                    break;
                }
                
                // NUMP PAD -> voir screen.c
                if (resize_screen(event.key.code, &window_info)) {
                    sfRenderWindow_destroy(window);
                    window = sfRenderWindow_create((sfVideoMode) {window_info.size.x, window_info.size.y, 32}, "Googoo Gagaga", sfClose, NULL);
                    if (!window) { EXIT_DEBUG_WINDOW; }
                }
            }
        }

        /* PROGRAM STEPS */
        switch (program_step) {

            case MENU_step:

                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(0, 0, 0));
                
                // Mise en place du background
                set_position_center(window, tex_bg, sp_bg, window_info);
                setup_sprite(window, tex_bg, sp_bg, window_info);
                
                // Mise en place du btn_start
                set_position_center(window, tex_start_btn, sp_start_btn, window_info);
                setup_sprite(window, tex_start_btn, sp_start_btn, window_info);
                
                // onclick btn_start
                click_on_btn_start(window, &event, tex_start_btn, sp_start_btn, &program_step);
                
                break;
            
            
            case TEMP_step:
                
                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(48, 12, 1));
                
                // Mise en place du background
                set_position_center(window, tex_bg, sp_bg, window_info);
                setup_sprite(window, tex_bg, sp_bg, window_info);


///////////////////////////////////////////////////////////////////////////////

/*
                Les coordonnées (1920, 1200) sont en dehors de la fenetre ????

                > window_info.size.x = 1920
                > window_info.size.y = 1200
*/

                position = sfSprite_getPosition(sp_start_btn);
                SPEED = 1; // position est unsigned donc speed aussi :/

                if (sfKeyboard_isKeyPressed(sfKeyRight) && position.x <= window_info.size.x)
                    position.x += SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyLeft) && position.x >= 100)
                    position.x -= SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyUp) && position.y >= 100)
                    position.y -= SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyDown) && position.y <= window_info.size.x)
                    position.y += SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyI))
                    printf("\nwindow_info (%u, %u) (%.2f, %.2f)", window_info.size.x, window_info.size.y, window_info.scale.x, window_info.scale.y);
                
                sfSprite_setPosition(sp_start_btn, position);
                setup_sprite(window, tex_start_btn, sp_start_btn, window_info);

///////////////////////////////////////////////////////////////////////////////

                
                break;
        }

        /* Update the window */
        sfRenderWindow_display(window);
    }


    /* Cleanup resources */
    CLEANUP_RESOURCES_


    return EXIT_SUCCESS;
}
