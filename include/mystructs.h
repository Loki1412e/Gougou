#ifndef MYSTRUCTS_H_
    #define MYSTRUCTS_H_


    #include "../include/my.h"


    // Window informations
    typedef struct __my_window_info__ {
        sfVector2u size;
        sfVector2f scale;
    } myWindowInfo;


    // Define an object
    typedef struct __my_object__ {
        sfTexture* texture;
        sfSprite* sprite;
    } myObject;


    // Define Player
    typedef struct __my_player__ {
        myObject object;
        sfVector2f speed;
        sfVector2f velocity;
        int on_jump;
        float hp;
        int dash_ready;
        float dash_cooldown_timer; 
    } myPlayer;


#endif