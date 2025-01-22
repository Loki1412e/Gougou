#ifndef TMP_GAME_H_
    #define TMP_GAME_H_

    #include "my.h"
    
    #include "events.h"
    #include "sprites.h"
    
    #include "map_textures.h"
    #include "map.h"
    #include "player.h"

    int tmp_game(sfRenderWindow* window, sfEvent event, myWindowInfo *window_info, int *program_step);

#endif