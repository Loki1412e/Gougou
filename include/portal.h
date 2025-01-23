#ifndef PORTAL_H_
    #define PORTAL_H_

    #include "my.h"
    #include "sprites.h"
    #include "map.h"

    void applyGravityPortal(sfRenderWindow* window, myPortal *portal, myObject floor, myWindowInfo window_info);
    void endLvlPortal(myPortal *portal, myPlayer *player, int *program_step);

#endif