
#include "../include/level_test.h"


int tmp_game(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);


int tmp_game(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

    sfVector2u size;
    sfVector2f scale;
    sfVector2f position;

    
    // Camera (view)
    sfView* view = sfView_create();
    sfView_setSize(view, (sfVector2f) { window_info->size.x , window_info->size.y });

    
    // Map
    sfVector2u map_dimensions;
    int **map = use_map("./maps/level_01", &map_dimensions);
    if (!map) {
        sfRenderWindow_destroy(window);
        EXIT_DEBUG_MAP
    }

    sfTexture **all_textures = loadAllTextures();
    if (!all_textures) {
        freeMap(map, map_dimensions.y);
        sfRenderWindow_destroy(window);
        EXIT_DEBUG_TEXTURE
    }

    sfSprite* map_tile = sfSprite_create();


    // Player
    myPlayer player = {
        .on_jump = 0,
        .dash_cooldown = 0,
        .direction = RIGHT,
        .speed = (sfVector2f) { SPEED_X_player , SPEED_Y_player },
        .hp = HP_player
    };
    if (create_sprite(&(player.object), "./assets/player/tmp.png", (sfVector2f) {4, 4})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, player.object.texture, player.object.sprite, *window_info);


    /* Start GAME LOOP */
    while (sfRenderWindow_isOpen(window) && *program_step == TMP_game) {

        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            
            switch (event_behavior(window, event, window_info, program_step)) {
            
                case 1:
                    EXIT_DEBUG_WINDOW;
                
                case 2:
                    position = sfSprite_getPosition(player.object.sprite);
                    sfSprite_setPosition(player.object.sprite, (sfVector2f) { position.x / window_info->scale.x, position.y / window_info->scale.y });
                    break;
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        
        // Recharge la camera a partir du Player
        sfView_setSize(view, (sfVector2f) { window_info->size.x , window_info->size.y });
        sfView_setCenter(view, (sfVector2f) { sfSprite_getPosition(player.object.sprite).x , window_info->size.y / 2. });
        sfRenderWindow_setView(window, view);


        // Dessine la map
        drawMap(window, map, map_dimensions, map_tile, all_textures);       

        // Dessine le Joueur
        setup_sprite(window, player.object.texture, player.object.sprite, *window_info);

        // Pour bouger le joueur
        // player_TileMovements(window, window_info, &player);

        sfRenderWindow_display(window);
    
    }

    // Free Map
    sfSprite_destroy(map_tile);
    freeAllTextures(all_textures);
    freeMap(map, map_dimensions.y);
    
    // Free player
    destroy_object(&player.object);
    
    // Free view
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
    sfView_destroy(view);

    return 0;
}