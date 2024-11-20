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

    int program_step = MENU_step;

    
    sfVector2u size;
    sfVector2f scale;
    sfVector2f position;
    float SPEED;


    // Background
    myObject menu_bg;
    // if (create_sprite(&menu_bg, "./assets/menu/background.png")) { EXIT_DEBUG_TEXTURE }
    menu_bg.texture = sfTexture_createFromFile("./assets/menu/background.png", NULL);
    if (!menu_bg.texture) { EXIT_DEBUG_TEXTURE }
    menu_bg.sprite = sfSprite_create();
    sfSprite_setTexture(menu_bg.sprite, menu_bg.texture, sfTrue);



    // Btn Start
    myObject menu_btn;
    menu_btn.texture = sfTexture_createFromFile("./assets/menu/start.png", NULL);
    if (!menu_btn.texture) { EXIT_DEBUG_TEXTURE }
    menu_btn.sprite = sfSprite_create();
    sfSprite_setTexture(menu_btn.sprite, menu_btn.texture, sfTrue);
    sfSprite_setScale(menu_btn.sprite, (sfVector2f) {0.3, 0.3}); // on applique une mise à l'echelle


    /* Create the main window */
    window = sfRenderWindow_create((sfVideoMode) {window_info.size.x, window_info.size.y, 32}, "Googoo Gagaga", sfClose, NULL);
    if (!window) { EXIT_DEBUG_WINDOW }


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
                    if (!window) { EXIT_DEBUG_WINDOW }
                    set_position_center(window, menu_bg.texture, menu_bg.sprite, window_info);
                    set_position_center(window, menu_btn.texture, menu_btn.sprite, window_info);
                }
            }
        }

        /* PROGRAM STEPS */
        switch (program_step) {

            case MENU_step:

                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(0, 0, 0));
                
                // Mise en place du background
                set_position_center(window, menu_bg.texture, menu_bg.sprite, window_info);
                setup_sprite(window, menu_bg.texture, menu_bg.sprite, window_info);
                
                // Mise en place du btn_start
                set_position_center(window, menu_btn.texture, menu_btn.sprite, window_info);
                setup_sprite(window, menu_btn.texture, menu_btn.sprite, window_info);
                
                // onclick btn_start
                click_on_btn_start(window, &event, menu_btn.texture, menu_btn.sprite, &program_step);
                
                break;
            
            
            case TEMP_step:
                
                // Clear window
                sfRenderWindow_clear(window, sfColor_fromRGB(48, 12, 1));
                
                // Mise en place du background
                set_position_center(window, menu_bg.texture, menu_bg.sprite, window_info);
                setup_sprite(window, menu_bg.texture, menu_bg.sprite, window_info);


///////////////////////////////////////////////////////////////////////////////

/*
                > (window_info.size.x - size.x * scale.x)
                
                - Correspond à la taille de l'écran en x moins la taille du btn en x (size * scale pour avoir la taille du sprite)
                - Ainsi on empeche le sprite de sortir de la fenetre HEHEHEHE

*/

                size = sfTexture_getSize(menu_btn.texture);
                scale = sfSprite_getScale(menu_btn.sprite);
                position = sfSprite_getPosition(menu_btn.sprite);
                SPEED = 0.8;

                if (sfKeyboard_isKeyPressed(sfKeyRight) && position.x <= (window_info.size.x - size.x * scale.x) - 100)
                    position.x += SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyLeft) && position.x >= 100)
                    position.x -= SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyUp) && position.y >= 100)
                    position.y -= SPEED;

                if (sfKeyboard_isKeyPressed(sfKeyDown) && position.y <= (window_info.size.y - size.y * scale.y) - 100)
                    position.y += SPEED;
                
                sfSprite_setPosition(menu_btn.sprite, position);
                setup_sprite(window, menu_btn.texture, menu_btn.sprite, window_info);

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
