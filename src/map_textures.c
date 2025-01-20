
#include "../include/map_textures.h"


int allTexturesAreLoad(sfTexture** textures);
void freeAllTextures(sfTexture** textures);
sfTexture** loadAllTextures();
sfVector2f normalizeScaleTexture(sfTexture* texture, size_t size);


// Boolean
int allTexturesAreLoad(sfTexture** textures) {
    
    // i=0 et i=1 sont NULL par defaut
    for (int i = 2; i < TOTAL_COUNT_MAP_TEXTURES; i++) {
        if (!textures[i]) return 0;
    }

    return 1;
}


void freeAllTextures(sfTexture** textures) {
    for(int i = 1; i < TOTAL_COUNT_MAP_TEXTURES; i++) sfTexture_destroy(textures[i]);
    free(textures);
}


sfTexture** loadAllTextures() {

    sfTexture** all_textures = (sfTexture**) malloc(sizeof(sfTexture*) * TOTAL_COUNT_MAP_TEXTURES);

    all_textures[0] = NULL; // void
    all_textures[1] = NULL; // player spawn
    all_textures[TERRE_TEXTURE] = sfTexture_createFromFile("./assets/game/terre.png", NULL);
    all_textures[MUR_TEXTURE] = sfTexture_createFromFile("./assets/game/mur.png", NULL);
    all_textures[TEST_TEXTURE] = sfTexture_createFromFile("./assets/game/test.png", NULL);

    if (!allTexturesAreLoad(all_textures)) {
        printf("\nERROR -> Impossible de charger les fichiers de textures");
        freeAllTextures(all_textures);
        return NULL;
    }

    return all_textures;
}


sfVector2f normalizeScaleTexture(sfTexture* texture, size_t size) {
    
    sfVector2u texture_size = sfTexture_getSize(texture);
    
    sfVector2f scale = {
        size / texture_size.x,
        size / texture_size.y
    };

    return scale;
}