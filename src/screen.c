
#include "../include/screen.h"
#include "../include/config.h"



int resize_screen(sfKeyCode code, myWindowInfo *window_info);

int resize_screen(sfKeyCode code, myWindowInfo *window_info) {
    switch (code) {
        case sfKeyNumpad0:
            *window_info = _1280x800;
            save_config("./configs/config.test", window_info);
            return 1;
        case sfKeyNumpad1:
            *window_info = _1920x1200;
            save_config("./configs/config.test", window_info);
            return 1;
         case sfKeyNumpad2:
            *window_info = _1680x1050;
            save_config("./configs/config.test", window_info);
            return 1;
    }
    return 0;
}