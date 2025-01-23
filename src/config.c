#include "../include/config.h"


int load_config(char *filepath, myWindowInfo *window_info, int *sound);
int saveConfig(char *filename, myWindowInfo *window_info, int *sound);


int load_config(char *filepath, myWindowInfo *window_info, int *sound) {
    
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de configuration.\n");
        return 1;
    }

    char line[256]; // sert de buffer pour lire les lignes
    
    sfVector2u size = {0, 0};
    int music = -1;

    while (fgets(line, sizeof(line), file)) {

        // verifie si la ligne commence par "resolution="
        if (strncmp(line, "resolution=", 11) == 0) {
            // recupere les deux entiers apres "resolution="
            if (sscanf(line + 11, "%dx%d", &size.x, &size.y) != 2) {
                printf("Erreur -> Format invalide dans le fichier");
                fclose(file);
                return 1;
            }
        }

        // verifie si la ligne commence par "music="
        if (strncmp(line, "music=", 6) == 0) {
            // recupere un entier '0' ou '1' apres "music="
            if (sscanf(line + 6, "%d", &music) == 1 && (music == 1 || music == 0))
                *sound = music;
            else {
                printf("Erreur -> Format invalide dans le fichier");
                fclose(file);
                return 1;
            }
        }
    }

    // On redefini la taille de l'écran en fonction du fichier de conf
    switch (size.x) {
    
        case 1920:
            *window_info = _1920x1200;
            break;
    
        case 1680:
            *window_info = _1680x1050;
            break;
    
        case 1280:
            *window_info = _1280x800;
            break;
        
        default:
            if (music != 1 && music != 0) return 1;
    }

    fclose(file);
    return 0;
}



int saveConfig(char *filename, myWindowInfo *window_info, int *sound) {
    
    FILE *file = fopen(filename, "w"); // Ouvre le fichier en mode écriture
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de configuration.");
        return 1;
    }

    // save la resolution actuelle dans le dossier de conf
    fprintf(file, "resolution=%dx%d\n", window_info->size.x, window_info->size.y);
    fprintf(file, "music=%d\n", *sound);

    fclose(file);
    return 0;
}