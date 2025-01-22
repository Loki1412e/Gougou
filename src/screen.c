
#include "../include/screen.h"


int resize_screen(sfKeyCode code, myWindowInfo *window_info);


int resize_screen(sfKeyCode code, myWindowInfo *window_info) {

    switch (code) {
        case sfKeyNumpad0:
            *window_info = _2560x1600;
            return 1;
        
        case sfKeyNumpad1:
            *window_info = _1920x1200;
            return 1;
        
        case sfKeyNumpad2:
            *window_info = _1680x1050;
            return 1;
        
        case sfKeyNumpad3:  // :(
            *window_info = _1600x1200;
            return 1;
        
        case sfKeyNumpad4:  // :(
            *window_info = _1280x1024;
            return 1;
        
        case sfKeyNumpad5:
            *window_info = _1280x800;
            return 1;
        
        case sfKeyNumpad6:  // :(
            *window_info = _1020x768;
            return 1;
    }

    return 0;
}