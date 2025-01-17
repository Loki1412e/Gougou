
#include "../include/map.h"

int countLWithGetC(FILE * f);
int countCharFirstL_withoutSpace(FILE* f);
int fileToMap(FILE* f, int **map, sfVector2u* map_dimensions);
int** allocateMap(sfVector2u map_dimensions);
void freeMap(int **map, int map_columns);
int** use_map(char* file_path, sfVector2u* map_dimensions);
int drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures);


int countLWithGetC(FILE * f) {
    
    int counter = 0;
    char ch;

    fseek(f, 0, SEEK_SET);
    
    while((ch = fgetc(f)) != EOF) {
        if (ch == '\n') counter++;
    }

    if(ch != '\n' && counter >= 0) counter++;

    return counter;
}


int countCharFirstL_withoutSpace(FILE* f) {
    
    int counter = 0;
    char ch;
    
    fseek(f, 0, SEEK_SET);

    while((ch = fgetc(f)) != '\n' && ch != EOF) {
        if (ch != ' ') counter++;
    }

    return counter;
}


int fileToMap(FILE* f, int **map, sfVector2u* map_dimensions) {

    fseek(f, 0, SEEK_SET);

    for (int y = 0; y < map_dimensions->y; y++) {
        for (int x = 0; x < map_dimensions->x; x++) {
            if (fscanf(f, "%d", &map[y][x]) != 1) {
                printf("\nErreur de lecture -> map[%d][%d] = %d", y, x, map[y][x]);
                printf("\nmap_dimensions = (%d, %d)\n", map_dimensions->y, map_dimensions->x);
                freeMap(map, map_dimensions->y);
                return EXIT_FAILURE;
            }
        }
    }

    return 0;
}


int** allocateMap(sfVector2u map_dimensions) {
    
    // Allouer un tableau de pointeurs (représente les lignes)
    int** map = (int**) malloc(sizeof(int*) * map_dimensions.y);
    if (!map) return NULL;

    // Allouer chaque ligne (chaque pointeur pointe vers un tableau)
    for (int i = 0; i < map_dimensions.y; i++) {
        
        map[i] = (int*) malloc(sizeof(int) * map_dimensions.x);
        
        if (!map[i]) {
            freeMap(map, i); // On free toute la map deja alloue
            return NULL;
        }
    }

    return map;
}


void freeMap(int **map, int map_columns) {
    for(int i = 0; i < map_columns; i++) free(map[i]);
    free(map);
}


// Return :
// - int** map (like map[y][x])
// - sfVector2u map_dimensions
int** use_map(char* file_path, sfVector2u* map_dimensions) {
    
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("\nErreur a l'ouverture du fichier");
        return NULL;
    }

    map_dimensions->y = countLWithGetC(file);
    map_dimensions->x = countCharFirstL_withoutSpace(file);


    int **map = allocateMap(*map_dimensions);
    if (!map) {
        printf("\nERROR MALLOC MAP");
        fclose(file);
        return NULL;
    }

    if (fileToMap(file, map, map_dimensions)) {
        printf("\nERROR CONVERT FILE ON MAP");
        fclose(file);
        return NULL;
    };

    fclose(file);

    return map;
}

int drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures) {
    
    for (int y = 0; y < map_dimensions.y; y++) {
        for (int x = 0; x < map_dimensions.x; x++) {

            int tile = map[y][x];

            switch (tile) {
                
                case TERRE_TEXTURE:
                    sfSprite_setTexture(map_tile, all_textures[TERRE_TEXTURE], sfTrue);
                    break;

                case MUR_TEXTURE:
                    sfSprite_setTexture(map_tile, all_textures[MUR_TEXTURE], sfTrue);
                    break;

                case TEST_TEXTURE:
                    sfSprite_setTexture(map_tile, all_textures[TEST_TEXTURE], sfTrue);
                    break;
            }

            if (tile) {
                sfSprite_setScale(map_tile, normalizeScaleTexture(sfSprite_getTexture(map_tile), TILE_SIZE));
                sfSprite_setPosition(map_tile, (sfVector2f) {x * TILE_SIZE, y * TILE_SIZE});
                sfRenderWindow_drawSprite(window, map_tile, NULL);
            }
        }
    }
}