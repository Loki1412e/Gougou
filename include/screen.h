#ifndef SCREEN_H_
    #define SCREEN_H_


    #include "my.h"
    #include "config.h"
    

    /* Window Resolution */
    // scale par rapport à 1920x1200
    #define _1920x1200 (myWindowInfo) {(sfVector2u) {1920, 1200}, (sfVector2f) {1., 1.}}                //OUI
    #define _1680x1050 (myWindowInfo) {(sfVector2u) {1680, 1050}, (sfVector2f) {0.875, 0.875}}          //OUI
    #define _1280x800  (myWindowInfo) {(sfVector2u) {1280, 800}, (sfVector2f) {0.666667, 0.666667}}     //OUI


    int resizeMyScreen(sfRenderWindow* window, myWindowInfo *window_info);
    int numpadResize(sfKeyCode code, myWindowInfo *window_info);

#endif