#ifndef MY_H_
    #define MY_H_

    /* Basics  */
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

#endif