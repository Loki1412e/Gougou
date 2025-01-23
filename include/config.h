#ifndef CONFIG_H
    #define CONFIG_H

    #include "my.h"
    #include "mystructs.h"
    #include "screen.h"

    int load_config(char *filepath, myWindowInfo *window_info, int *sound);
    int saveConfig(char *filename, myWindowInfo *window_info, int *sound);

#endif
