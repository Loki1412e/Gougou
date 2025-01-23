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
    #include "mystructs.h"

    /* Paralax Speed */
    #define SPEED_LAYER1 1.0f
    #define SPEED_LAYER2 0.5f
    #define SPEED_LAYER3 0.2f

    /* Son */
    #include <windows.h>
    #include <mmsystem.h>


    /* Debug */
    #define EXIT_DEBUG_WINDOW fprintf(stderr, "\n%s\n%d | WINDOW ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    #define EXIT_DEBUG_TEXTURE fprintf(stderr, "\n%s\n%d | TEXTURE ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    #define EXIT_DEBUG_MAP fprintf(stderr, "\n%s\n%d | MAP ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    #define EXIT_DEBUG_SPAWN_PLAYER fprintf(stderr, "\n%s\n%d | SPAWN PLAYER ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__); return 1;
    
    
    /* FPS */
    #define FPS 60.0
    

    /* Program Steps */
    #define MENU_step 0
    #define GAME_step 1
    #define DEATHMENU_step 2
    #define SETTINGS_step 3
    #define TMP_game 4
    #define QUIT_step 5
    

    /* Gravity */
    #define GRAVITY 9.81
    #define JUMP_FORCE  80
    #define TIME 1.0/32.0


    /* Attributs Player */
    #define JUMP_player 1.6
    #define SPEED_X_player 0.6
    #define DASH_DURATION_player 300
    #define DASH_SPEED_player 3
    #define DASH_COOLDOWN_player (DASH_DURATION_player * 2)
    #define HP_player 100


    /* Directions */
    #define TOP 't'
    #define BOTTOM 'b'
    #define LEFT 'l'
    #define RIGHT 'r'

#endif