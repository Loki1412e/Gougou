#include "../include/config.h"

int load_config(const char *filepath, myWindowInfo *window_info) {
    FILE *file = fopen(filepath, "r");
    if (!file) return 1; // Echec d'ouverture du fichier

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        char key[64];
        int value;

        if (sscanf(line, "%63[^=]=%d", key, &value) == 2) {
            if (strcmp(key, "SCREEN_WIDTH") == 0) {
                window_info->size.x = value;
            } else if (strcmp(key, "SCREEN_HEIGHT") == 0) {
                window_info->size.y = value;
            }
        }
    }

    fclose(file);
    return 0; // Succès
}

#include <stdio.h>

int save_config(const char *filename, const myWindowInfo *window_info) {
    FILE *file = fopen(filename, "w"); // Ouvre le fichier en mode écriture
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de configuration.\n");
        return 1; // Erreur si le fichier ne peut pas être ouvert
    }

    // Sauvegarder les informations de taille de la fenêtre
    fprintf(file, "%d %d\n", window_info->size.x, window_info->size.y);
    fclose(file);
    return 0; // Succès
}

