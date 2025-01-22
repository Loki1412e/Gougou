#ifndef ENEMIES_H_
    #define ENEMIES_H_

    #include "my.h"
    #include "sprites.h"
    #include "map.h"

    void applyGravityEnemy(sfRenderWindow* window, myEnemy *enemy, myObject floor, myWindowInfo window_info);

#endif