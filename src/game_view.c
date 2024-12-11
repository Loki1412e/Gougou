
#include "../include/game_view.h"

int gam_ing(sfRenderWindow* window, sfEvent event, myWindowInfo window_info);

// return 1 -> EXIT_DEBUG_TEXTURE
int gam_ing(sfRenderWindow* window, sfEvent event, myWindowInfo window_info) {

    sfVector2u size;
    sfVector2f scale;
    sfVector2f position;
    float SPEED;

    // Background
    myObject game_bg;
    if (create_sprite(&game_bg, "./assets/menu/background.png", (sfVector2f) {1., 1.})) { EXIT_DEBUG_TEXTURE }

    // Btn Start
    myObject game_btn;
    if (create_sprite(&game_btn, "./assets/menu/start.png", (sfVector2f) {0.3, 0.3})) { EXIT_DEBUG_TEXTURE }

    // Clear window
    sfRenderWindow_clear(window, sfColor_fromRGB(48, 12, 1));
    
    // Mise en place du background
    set_position_center(window, game_bg.texture, game_bg.sprite, window_info);
    setup_sprite(window, game_bg.texture, game_bg.sprite, window_info);


///////////////////////////////////////////////////////////////////////////////

/*
    > (window_info.size.x - size.x * scale.x)
    
    - Correspond à la taille de l'écran en x moins la taille du btn en x (size * scale pour avoir la taille du sprite)
    - Ainsi on empeche le sprite de sortir de la fenetre HEHEHEHE
*/

    size = sfTexture_getSize(game_btn.texture);
    scale = sfSprite_getScale(game_btn.sprite);
    position = sfSprite_getPosition(game_btn.sprite);
    SPEED = 0.8;

    if (sfKeyboard_isKeyPressed(sfKeyRight) && position.x <= (window_info.size.x - size.x * scale.x) - 100)
        position.x += SPEED;

    if (sfKeyboard_isKeyPressed(sfKeyLeft) && position.x >= 100)
        position.x -= SPEED;

    if (sfKeyboard_isKeyPressed(sfKeyUp) && position.y >= 100)
        position.y -= SPEED;

    if (sfKeyboard_isKeyPressed(sfKeyDown) && position.y <= (window_info.size.y - size.y * scale.y) - 100)
        position.y += SPEED;
    
    sfSprite_setPosition(game_btn.sprite, position);
    setup_sprite(window, game_btn.texture, game_btn.sprite, window_info);

///////////////////////////////////////////////////////////////////////////////

    return 0;
}