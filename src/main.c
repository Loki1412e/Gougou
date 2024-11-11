/*
    Sujet : Projet en C / ESGI 2i1 / 2024-2025
    Auteur : JAIEL FERRO Milhane
    Date de création : 09/11/2024 (c'est pas vrai oof mais tqt)
*/


#include "../include/main.h"


int main() {

    sfVector2u window_size = _1920x1200;
    sfRenderWindow* window;
    sfEvent event;

    // Background
    sfTexture* tex_bg;
    sfSprite* sp_bg;
    
    // Btn start
    sfTexture* tex_start_btn;
    sfSprite* sp_start_btn;

    unsigned program_setp = MENU_step;

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
    window = sfRenderWindow_create((sfVideoMode) {window_size.x, window_size.y, 32}, "Googoo Gagaga", sfResize | sfClose, NULL);
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
                    program_setp = MENU_step;
                    break;
                
                case sfKeyNum2:
                    program_setp = TEMP_step;
                    break;
                
                case sfKeyEnter:
                    program_setp = TEMP_step;
                    break;

                case sfKeyNumpad1:
                    sfRenderWindow_setSize(window, _1920x1200);
                    window_size = sfRenderWindow_getSize(window);
                    break;
                
                case sfKeyNumpad2:
                    sfRenderWindow_setSize(window, _1680x1050);
                    window_size = sfRenderWindow_getSize(window);
                    break;
                }
            }
        }


        /* PROGRAM STEPS */
        switch (program_setp) {

            case MENU_step:

                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(0, 0, 0));
                // Mise en place du background
                set_bg(window, tex_bg, sp_bg, &window_size);
                sfRenderWindow_drawSprite(window, sp_bg, NULL);
                
                // onclick btn_start
                click_on_btn_start(window, &event, tex_start_btn, sp_start_btn, &program_setp);
                
                // Mise en place du btn_start
                set_start_btn(window, tex_start_btn, sp_start_btn, &window_size);
                sfRenderWindow_drawSprite(window, sp_start_btn, NULL);
                
                break;
            
            
            case TEMP_step:
                
                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(48, 12, 1));
                
                // Mise en place du background
                set_bg(window, tex_bg, sp_bg, &window_size);
                sfRenderWindow_drawSprite(window, sp_bg, NULL);

                break;
        }


        /* Update the window */
        sfRenderWindow_display(window);
    }
    

    /* Cleanup resources */
    CLEANUP_RESOURCES_


    return EXIT_SUCCESS;
}