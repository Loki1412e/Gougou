#ifndef MAP_TEXTURES_H_
    #define MAP_TEXTURES_H_


    #include "my.h"


    // Taille des tuiles en pixels
    #define TILE_SIZE 84


    // Faut penser a update le total a chaque fois
    #define TOTAL_COUNT_MAP_TEXTURES 5
    #define VOID_TEXTURE    0
    #define PLAYER_SPAWN    1
    #define TERRE_TEXTURE   2
    #define MUR_TEXTURE     3
    #define TEST_TEXTURE    4


    int allTexturesAreLoad(sfTexture** textures);
    void freeAllTextures(sfTexture** textures);
    sfTexture** loadAllTextures();
    sfVector2f normalizeScaleTexture(sfTexture* texture, size_t size);

#endif