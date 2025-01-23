#ifndef CONFIG_H
    #define CONFIG_H
    #include "mystructs.h" 
    #include "my.h"

    int load_config(const char *filepath, myWindowInfo *window_info);
    int save_config(const char *filename, const myWindowInfo *window_info);

#endif
