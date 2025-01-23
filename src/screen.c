#include "../include/screen.h"


int resizeMyScreen(sfRenderWindow* window, myWindowInfo *window_info);
int numpadResize(sfKeyCode code, myWindowInfo *window_info);


int numpadResize(sfKeyCode code, myWindowInfo *window_info) {
    
    switch (code) {
        
        case sfKeyNumpad0:
            *window_info = _1280x800;
            return 1;
        
        case sfKeyNumpad1:
            *window_info = _1920x1200;
            return 1;

         case sfKeyNumpad2:
            *window_info = _1680x1050;
            return 1;
    }

    return 0;
}

int resizeMyScreen(sfRenderWindow* window, myWindowInfo *window_info) {
    sfRenderWindow_destroy(window);
    window = sfRenderWindow_create((sfVideoMode) {window_info->size.x, window_info->size.y, 32}, "Gogoo Gagaga", sfClose, NULL);
    if (!window) return 1;
    return 0;
}