#ifndef MY_H_
    #define MY_H_

    /* Basics */
    #include <unistd.h> // jsp c'est quoi oof
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    /* CSFML */
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Clock.h>
    #include <SFML/Audio.h>


    /* Debug */
    #define EXIT_DEBUG_WINDOW fprintf(stderr, "\n%s\n%d | WINDOW ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__ - 1); return EXIT_FAILURE
    #define EXIT_DEBUG_TEXTURE fprintf(stderr, "\n%s\n%d | TEXTURE ERROR -> EXIT_FAILURE\n\n", __FILE__, __LINE__ - 1); return EXIT_FAILURE


    /* Window Resolution */
    #define _1020x768 (sfVector2u) {1020, 768}
    #define _1280x800 (sfVector2u) {1280, 800}
    #define _1280x1024 (sfVector2u) {1280, 1024}
    #define _1280x1024 (sfVector2u) {1280, 1024}
    #define _1600x1200 (sfVector2u) {1600, 1200}
    #define _1680x1050 (sfVector2u) {1680, 1050}
    #define _1920x1200 (sfVector2u) {1920, 1200}
    #define _2560x1600 (sfVector2u) {2560, 1600}


    /* Program Steps */
    #define MENU_step 0
    #define TEMP_step 1

    
    /* Cleanup Resources */
    #define CLEANUP_RESOURCES_ \
        sfSprite_destroy(sp_bg); \
        sfTexture_destroy(tex_bg); \
        sfSprite_destroy(sp_start_btn); \
        sfTexture_destroy(tex_start_btn); \
        sfRenderWindow_destroy(window);

    
    /* My Structs */

    typedef struct rgb_value { // Pour save des valeurs rgb
        sfUint8 r;
        sfUint8 g;
        sfUint8 b;
    } myRgbValue;

#endif