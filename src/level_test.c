
#include "../include/level_test.h"


int tmp_game(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);


int tmp_game(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step) {

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


    // // Player
    myObject player;
    if (create_sprite(&player, "./assets/player/Foxy/Sprites/idle/player-idle-1.png", (sfVector2f) {4, 4})) { EXIT_DEBUG_TEXTURE };
    set_position_center(window, player.texture, player.sprite, *window_info);


    /* Start GAME LOOP */
    while (sfRenderWindow_isOpen(window) && *program_step == TMP_game) {

        // Process events
        while (sfRenderWindow_pollEvent(window, &event)) {
            
            switch (event_behavior(window, event, window_info, program_step)) {
            
                case 1:
                    EXIT_DEBUG_WINDOW;
                
                // case 2:
                //     set_position_center(window, player.texture, player.sprite, *window_info);
                //     break;
            }
        }

        sfRenderWindow_clear(window, sfBlack);

        // Dessine la map
        drawMap(window, map, map_dimensions, map_tile, all_textures);       

        // Dessine le Joueur
        setup_sprite(window, player.texture, player.sprite, *window_info);

        // Pour bouger le joueur
        // player_basics_movements(window, window_info, &player);

        sfRenderWindow_display(window);
    
    }

    // Free Map
    sfSprite_destroy(map_tile);
    freeAllTextures(all_textures);
    freeMap(map, map_dimensions.y);
    
    // Free player
    destroy_object(&player);

    return 0;
}