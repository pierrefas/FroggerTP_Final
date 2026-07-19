#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>
#include <stdlib.h>

#include "a_map.h"
#include "a_sprites.h"
#include "a_pause.h"
#include "a_render.h"
#include "gamestate.h"

#define GAME_HEIGHT 256
#define GAME_WIDTH 224

/* frame size must match a_sprites FRAME_W/FRAME_H */
#ifndef FRAME_W
#define FRAME_W 16
#endif
#ifndef FRAME_H
#define FRAME_H 16
#endif

int fullscreen = 0;

/* inicializa Allegro y addons; no carga sprites aún */
int init_alegro(void){
    if (!al_init()){
        fprintf(stderr, "allegro failed to initialize\n");
        return 0;
    } else {
        printf("allegro initialized successfully\n");
    }

    if (!al_install_keyboard()){
        fprintf(stderr, "allegro keyboard installation failed\n");
        return 0;
    } else {
        printf("keyboard installed\n");
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives addon!\n");
        return 0;
    }

    /* image addon must be initialized before using al_load_bitmap or al_create_sub_bitmap */
    al_init_image_addon();

    return 1; /* success */
}

int display(void)
{
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int desktop_w = info.x2 - info.x1;
    int desktop_h = info.y2 - info.y1;

    int target_height = desktop_h / 2;

    /* scaling factor (integer) to keep pixel art sharp */
    int scale = target_height / GAME_HEIGHT;
    if (scale < 1) scale = 1;

    int scaled_w = GAME_WIDTH * scale;
    int scaled_h = GAME_HEIGHT * scale;

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_BITMAP* buffer = al_create_bitmap(GAME_WIDTH, GAME_HEIGHT);

    ALLEGRO_DISPLAY* disp;
    if (fullscreen) {
        disp = al_create_display(desktop_w, desktop_h);
    } else {
        disp = al_create_display(scaled_w, scaled_h);
    }
    if (!disp) {
        fprintf(stderr, "Failed to create display\n");
        /* cleanup */
        al_destroy_bitmap(buffer);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return 0;
    }

    /* Now that a display exists, load sprites (sub-bitmaps) */
    if (load_sprites(NULL) != 0) {
        fprintf(stderr, "Failed to load spritesheet\n");
        /* cleanup */
        al_destroy_display(disp);
        al_destroy_bitmap(buffer);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return 0;
    }

    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    int redraw = 1;
    int pause = 0;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    /* create/own the game state for rendering and updates */
    game_state *gs = createGame();
    if (!gs) {
        fprintf(stderr, "Failed to create game state\n");
        destroy_sprites();
        al_destroy_display(disp);
        al_destroy_bitmap(buffer);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return 0;
    }

    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = 1;

        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
                break;
            }
            
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                pause = !pause;
                if (!pause) {
                    /* Just resumed: drop any pending events (e.g., the same ESC) */
                    al_flush_event_queue(queue);
                }
            }

            /* While paused allow Enter/Space to resume, Q to quit */
            if (pause) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                    event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    pause = 0;
                    al_flush_event_queue(queue);
                }
                /* If Q pressed here we'd already break above because we check it first */
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            /* draw into low-res buffer */
            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            /* draw map */
            a_disp_map();

            /* draw game state using our renderer */
            draw_game_state(gs);

            if (pause) {
                pause_menu();
                pause = 0;
                al_flush_event_queue(queue);

            }



            /* scale buffer to display backbuffer */
            al_set_target_bitmap(al_get_backbuffer(disp));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_scaled_bitmap(buffer, 0, 0, GAME_WIDTH, GAME_HEIGHT, 0, 0, scaled_w, scaled_h, 0);
            al_flip_display();

            redraw = 0;
        }
    }

    /* cleanup */
    destroy_sprites(); // destroys sub-bitmaps and spritesheet
    endGame(gs);
    al_destroy_bitmap(buffer);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 1;
}
