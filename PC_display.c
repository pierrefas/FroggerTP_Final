/*
 * main.c
 *
 *  Created on: Jul 9, 2026
 *      Author: peterfas
 */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>

#define GAME_HEIGHT 256
#define GAME_WIDTH 224

int fullscreen = 0;

int display(void)
{
    if (al_init()){
    	printf("allegro initialized successfully \n");
    }
    else{
    	printf("allegro falied to initialize \n");
    	return 0;
    }
    if(al_install_keyboard()){
    	printf("allegro font initialized successfully \n");
    }
    else{
        printf("allegro font falied to initialize \n");
        return 0;
    }

    ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info);
        int desktop_w = info.x2 - info.x1;
        int desktop_h = info.y2 - info.y1;

        int target_height = desktop_h / 2;

        // 2. Calculate the scaling factor based on the monitor height
        // (Using integer division keeps pixel art sharp)
        int scale = target_height / GAME_HEIGHT;
        if (scale < 1) scale = 1; // Fallback just in case

        // Calculate the dimensions of the scaled game window
        int scaled_w = GAME_WIDTH * scale;
        int scaled_h = GAME_HEIGHT * scale;


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 144.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_BITMAP* buffer = al_create_bitmap(GAME_WIDTH, GAME_HEIGHT);

    ALLEGRO_DISPLAY* disp;
    if (fullscreen) {
        disp = al_create_display(desktop_w, desktop_h);
    } else {
        disp = al_create_display(scaled_w, scaled_h);
    }

    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    int redraw = 1;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = 1;

        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            // Check if the key that was pressed is specifically the 'Q' key
            if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            // This ensures clicking the window's "X" button still closes the game safely
            break;
        }

        if(redraw && al_is_event_queue_empty(queue))
                {
                    // 1. Draw your game elements onto the internal low-res buffer canvas
                    al_set_target_bitmap(buffer);
                    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clears buffer to black

                    // Draw your text near the top left of the game canvas
                    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Hello world!");

                    // 2. Put a green dot at the exact mathematical center of your game canvas
                    // Width center: 224 / 2 = 112, Height center: 256 / 2 = 128
                    int center_x = GAME_WIDTH / 2;
                    int center_y = GAME_HEIGHT / 2;
                    al_put_pixel(center_x, center_y, al_map_rgb(0, 255, 0)); // Draws a sharp green pixel

                    // 3. Switch back to the operating system display window
                    al_set_target_bitmap(al_get_backbuffer(disp));
                    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clears window backbuffer

                    // 4. Scale up the canvas to fill the entire window (starting at 0, 0)
                    al_draw_scaled_bitmap(buffer,
                                          0, 0, GAME_WIDTH, GAME_HEIGHT,
                                          0, 0, scaled_w, scaled_h,
                                          0);

                    // 5. Push everything to your monitor screen
                    al_flip_display();

                    redraw = 0;
                }
    }
    al_destroy_bitmap(buffer);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 1;
}
