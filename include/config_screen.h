#ifndef CONFIG_SCREEN_H_
    #define CONFIG_SCREEN_H_


    #include "../include/my.h"


    /* Struct for window informations */
    typedef struct __my_window_info__ {
        sfVector2u size;
        sfVector2f scale;
    } myWindowInfo;
    

    /* Window Resolution */
    // scale par rapport à 1920x1200
    #define _2560x1600 (myWindowInfo) {(sfVector2u) {2560, 1600}, (sfVector2f) {1.333333, 1.2}}
    #define _1920x1200 (myWindowInfo) {(sfVector2u) {1920, 1200}, (sfVector2f) {1., 1.}}
    #define _1680x1050 (myWindowInfo) {(sfVector2u) {1680, 1050}, (sfVector2f) {0.875, 0.875}}
    #define _1600x1200 (myWindowInfo) {(sfVector2u) {1600, 1200}, (sfVector2f) {0.833333, 1.}}
    #define _1280x1024 (myWindowInfo) {(sfVector2u) {1280, 1024}, (sfVector2f) {0.666667, 0.971429}}
    #define _1280x800  (myWindowInfo) {(sfVector2u) {1280, 800}, (sfVector2f) {0.666667, 0.666667}}
    #define _1020x768  (myWindowInfo) {(sfVector2u) {1020, 768}, (sfVector2f) {0.53125, 0.64}}


    int resize_screen(sfKeyCode code, myWindowInfo *window_info);

#endif