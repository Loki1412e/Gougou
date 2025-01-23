#include "../include/events.h"


int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step);
int handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event, int *program_step, int action,  myWindowInfo *window_info, int *sound);
int handle_button_Sound(myButton *mute_btn, myButton *unmute_btn, sfRenderWindow *window, sfEvent *event, int *sound, char *music);


// return 1 => EXIT_DEBUG_WINDOW
// return 2 => SUCCESS : Window Update
int event_behavior(sfRenderWindow *window, sfEvent event, myWindowInfo *window_info, int *program_step) {
    
    if (event.type == sfEvtClosed || (sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyEnter)))
        sfRenderWindow_close(window);

    if (event.type == sfEvtKeyPressed) {

        switch (event.key.code) {

            case sfKeyEscape:
                *program_step = SETTINGS_step;
                break;

            case sfKeyNum1:
                *program_step = MENU_step;
                break;
                
            case sfKeyNum2:
                *program_step = GAME_step;
                break;
            
            case sfKeyNum3:
                *program_step = TMP_game;
                break;
                
            case sfKeyNum4:
                *program_step = DEATHMENU_step;
                break;

        }
                
        // NUMP PAD -> voir screen.c
        if (resize_screen(event.key.code, window_info)) {
            sfRenderWindow_destroy(window);
            window = sfRenderWindow_create((sfVideoMode) {window_info->size.x, window_info->size.y, 32}, "Gogoo Gagaga", sfClose, NULL);
            if (!window) return 1;
            return 2;
        }
    }

    return 0;
}


int handle_button_event(myButton *button, sfRenderWindow *window, sfEvent *event, int *program_step, int action,  myWindowInfo *window_info, int *sound) {
    
    sfVector2i mouse_position = sfMouse_getPositionRenderWindow(window);
    sfFloatRect bounds = sfSprite_getGlobalBounds(button->sprite);

    if (event->type == sfEvtMouseMoved) {
        // Change l'état en hover si la souris survole le bouton
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y)) {
            sfSprite_setTexture(button->sprite, button->texture_hovered, sfTrue);
        } else {
            sfSprite_setTexture(button->sprite, button->texture_normal, sfTrue);
        }
    } else if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
        // Change l'état en click si le bouton est pressé
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y)) {
            sfSprite_setTexture(button->sprite, button->texture_clicked, sfTrue);
        }
    } else if (event->type == sfEvtMouseButtonReleased && event->mouseButton.button == sfMouseLeft) {
        // Effectue une action si le bouton est relâché sur lui-même
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y)) {
            switch (action) {
                
                case QUIT_step:
                    sfRenderWindow_close(window);
                    break;
                case MENU_step:
                    *program_step = action;
                    break;
                case GAME_step:
                    *program_step = action;
                    break;
                case SETTINGS_step:
                    *program_step = action;
                    break;

                case _1920:
                    *window_info = _1920x1200;
                    if (save_config("./configs/config.test", window_info)) { EXIT_DEBUG_FILE }
                    break;
                case _1680:
                    *window_info = _1680x1050;
                    if (save_config("./configs/config.test", window_info)) { EXIT_DEBUG_FILE }
                    break;
                case _1280:
                    // printf("ouo");
                    *window_info = _1280x800; 
                    if (save_config("./configs/config.test", window_info)) { EXIT_DEBUG_FILE } 
                    // printf("aled");
                    break;
            }
        }
        
        // Retourne à l'état normal ou hover après le clic
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y)) {
            sfSprite_setTexture(button->sprite, button->texture_hovered, sfTrue);
        } else {
            sfSprite_setTexture(button->sprite, button->texture_normal, sfTrue);
        }
    }

    return 0; // pas de pbl
}


int handle_button_Sound(myButton *mute_btn, myButton *unmute_btn, sfRenderWindow *window, sfEvent *event, int *sound, char *music) {
    int state;
    myButton *button = *sound ? mute_btn : unmute_btn;

    sfVector2i mouse_position = sfMouse_getPositionRenderWindow(window);
    sfFloatRect bounds = sfSprite_getGlobalBounds(button->sprite);

    if (event->type == sfEvtMouseMoved) {

        // Change l'état en hover si la souris survole le bouton
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y))
            sfSprite_setTexture(button->sprite, button->texture_hovered, sfTrue);
        
        else
            sfSprite_setTexture(button->sprite, button->texture_normal, sfTrue);
    }
    
    else if (event->type == sfEvtMouseButtonPressed && event->mouseButton.button == sfMouseLeft) {
        // Change l'état en click si le bouton est pressé
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y))
            sfSprite_setTexture(button->sprite, button->texture_clicked, sfTrue);
    }
    
    else if (event->type == sfEvtMouseButtonReleased && event->mouseButton.button == sfMouseLeft) {
        
        // Effectue une action si le bouton est relâché sur lui-même
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y)) {
            if (sound) PlaySound(NULL, 0, 0);
            state = *sound;
            *sound = *sound ? 0 : 1;
            if (*sound && *sound != state) return 2;

        }
        // Retourne à l'état normal ou hover après le clic
        if (sfFloatRect_contains(&bounds, mouse_position.x, mouse_position.y))
            sfSprite_setTexture(button->sprite, button->texture_hovered, sfTrue);
        
        else
            sfSprite_setTexture(button->sprite, button->texture_normal, sfTrue);
    }

    return 0; // pas de pbl
}