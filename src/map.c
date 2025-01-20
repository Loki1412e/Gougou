
#include "../include/map.h"

int countLWithGetC(FILE * f);
int countCharFirstL_withoutSpace(FILE* f);
int fileToMap(FILE* f, int **map, sfVector2u* map_dimensions);
int** allocateMap(sfVector2u map_dimensions);
void freeMap(int **map, int map_columns);
int** use_map(char* file_path, sfVector2u* map_dimensions);
void drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures);
int check_collisionMap(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myObject object, char direction);
int set_player_spawn(int** map, sfVector2u map_dimensions, myObject* player);


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

void drawMap(sfRenderWindow* window, int** map, sfVector2u map_dimensions, sfSprite* map_tile, sfTexture **all_textures) {
    
    for (int y = 0; y < map_dimensions.y; y++) {
        for (int x = 0; x < map_dimensions.x; x++) {

            int tile = map[y][x];

            switch (tile) {

                case VOID_TEXTURE:
                case PLAYER_SPAWN:
                    break;
                
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

            if (tile != VOID_TEXTURE && tile != PLAYER_SPAWN) {
                // sfSprite_setScale(map_tile, normalizeScaleTexture(sfSprite_getTexture(map_tile), TILE_SIZE));
                sfSprite_setPosition(map_tile, (sfVector2f) {x * TILE_SIZE, y * TILE_SIZE});
                sfRenderWindow_drawSprite(window, map_tile, NULL);
            }
        }
    }
}


// Boolean : Return 0 si pas collision et 1 si collision dans la direction indiqué (LEFT / RIGHT / TOP / BOTTOM)
int check_collisionMap(int** map, sfVector2u map_dimensions, sfSprite* map_tile, myObject object, char direction) {
// int check_collisionMap(int** map, sfVector2u map_dimensions, myObject object, char direction) {
    sfVector2f obj_position = sfSprite_getPosition(object.sprite);
    sfVector2f obj_scale = sfSprite_getScale(object.sprite);
    sfVector2u obj_size = sfTexture_getSize(object.texture);

    // Dimensions et positions du joueur
    float obj_width = obj_size.x * obj_scale.x;
    float obj_height = obj_size.y * obj_scale.y;

    sfVector2f obj_top_left = obj_position;
    sfVector2f obj_top_right = { obj_position.x + obj_width, obj_position.y };
    sfVector2f obj_bot_left = { obj_position.x, obj_position.y + obj_height };
    sfVector2f obj_bot_right = { obj_position.x + obj_width, obj_position.y + obj_height };

    // Parcours des tuiles autour du joueur
    for (int y = (obj_position.y / TILE_SIZE) - 1; y <= (obj_bot_right.y / TILE_SIZE) + 1; y++) {
        if (y < 0 || y >= map_dimensions.y) continue;

        for (int x = (obj_position.x / TILE_SIZE) - 1; x <= (obj_bot_right.x / TILE_SIZE) + 1; x++) {
            if (x < 0 || x >= map_dimensions.x) continue;

            // Vérifier si la tuile est collidable
            if (map[y][x] == TERRE_TEXTURE || map[y][x] == MUR_TEXTURE) {
                sfFloatRect tile_rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

                // Détection selon la direction
                if (direction == LEFT && obj_top_left.x <= tile_rect.left + tile_rect.width)
                    return 1;
                if (direction == RIGHT && obj_top_right.x >= tile_rect.left)
                    return 1;
                if (direction == TOP && obj_top_left.y <= tile_rect.top + tile_rect.height)
                    return 1;
                if (direction == BOTTOM && obj_bot_left.y >= tile_rect.top)
                    return 1;
            }
        }
    }

    return 0; // Pas de collision
}


int set_player_spawn(int** map, sfVector2u map_dimensions, myObject* player) {

    sfVector2u size = sfTexture_getSize(player->texture); // on recup la taille avec la texture
    sfVector2f scale = sfSprite_getScale(player->sprite); // on recup son scale (son echelle)

    for (int y = 0; y < map_dimensions.y; y++) {
        for (int x = 0; x < map_dimensions.x; x++) {

            if (map[y][x] == PLAYER_SPAWN) {

                sfVector2f position = {
                    (x * TILE_SIZE),
                    (y * TILE_SIZE) + TILE_SIZE - (size.y * scale.y) // On place le joueur collé en bas de la tile PLAYER_SPAWN
                    
                    // (x * TILE_SIZE) + TILE_SIZE / 2 - (size.x * scale.x) / 2, // On place le joueur au milieu de la tile PLAYER_SPAWN
                    // (y * TILE_SIZE) + TILE_SIZE - (size.y * scale.y) // On place le joueur collé en bas de la tile PLAYER_SPAWN
                };
                
                sfSprite_setPosition(player->sprite, position);
                
                return 0; // success
            }
        }
    }

    return 1; // error    
}