/*
** Kakou Kakou
*/

#include <SFML/Graphics.h>

int main() {

    sfRenderWindow* window;
    sfVideoMode videomode = { 1920, 1080, 32 };
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(videomode, "Googoo Gagaga", sfResize | sfClose, NULL);
    if (!window) return 1;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window)) {
        
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            
            sfRenderWindow_clear(window, sfMagenta);
            sfRenderWindow_display(window);
        }
    }
    
    sfRenderWindow_destroy(window);

    return 0;
}