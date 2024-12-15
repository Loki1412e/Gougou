#ifndef MY_H_
    #define MY_H_

    /* Basics  */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    /* CSFML */
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Clock.h>
    #include <SFML/Audio.h>
    // Mes structs
    #include "../include/mystructs.h"


    /* Debug */
    #define EXIT_DEBUG_WINDOW fprintf(stderr, "\n%s\n%d | WINDOW ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    #define EXIT_DEBUG_TEXTURE fprintf(stderr, "\n%s\n%d | TEXTURE ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    

    /* Program Steps */
    #define MENU_step 0
    #define GAME_step 1
    #define DEATHMENU_step 2


    /* Attributs Player */
    #define JUMP_player 10.0
    #define SPEED_X_player 0.6
    #define SPEED_Y_player 1.6
    #define HP_player 100 

#endif