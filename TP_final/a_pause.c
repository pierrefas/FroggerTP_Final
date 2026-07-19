/*
 * a_pause.c
 *
 * Very small pause menu implementation using Allegro 5.
 * Draws a translucent overlay and waits for resume/quit keys.
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a_pause.h"

void pause_menu(void)
{

    srand(time(NULL));

    static int random = 0;

    int x = 255;
    int y = 255;
    int z = 255;

    ALLEGRO_DISPLAY *disp = al_get_current_display();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue) return;

    /* Register keyboard and display events (display may be NULL in headless) */
    al_register_event_source(queue, al_get_keyboard_event_source());
    if (disp) al_register_event_source(queue, al_get_display_event_source(disp));

    ALLEGRO_FONT *font = al_create_builtin_font();
    if (!font) {
        /* We can still wait for input even without a font */
    }

    int running = 1;
    ALLEGRO_EVENT ev;

    /* Draw initial overlay once so user sees immediate feedback */
    if (disp) {
        al_set_target_backbuffer(disp);
        int w = al_get_display_width(disp);
        int h = al_get_display_height(disp);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        if (font) {
            al_draw_text(font, al_map_rgb(x,y,z), w/2, h/2 - 12, ALLEGRO_ALIGN_CENTER, "PAUSED");
            al_draw_text(font, al_map_rgb(x,y,z), w/2, h/2 + 8, ALLEGRO_ALIGN_CENTER,
                         "Press Enter/Space/Esc to resume, Q to quit");
        }
        al_flip_display();
    }

    while (running) {

        if(random)
        {
            x = rand() % 256;
            y = rand() % 256;
            z = rand() % 256;
        }
        else
        {
            x = 255;
            y = 255;
            z = 255;
        }

        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
            case ALLEGRO_KEY_ENTER:
            case ALLEGRO_KEY_SPACE:
                running = 0; /* resume */
                break;
            case ALLEGRO_KEY_Q:
                /* Quit the whole application (frontend loop will not continue). */
                al_destroy_event_queue(queue);
                if (font) al_destroy_font(font);
                exit(0);
                break;
            case ALLEGRO_KEY_C:
                random = 1;
            default:
                break;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            /* treat display close as quit */
            al_destroy_event_queue(queue);
            if (font) al_destroy_font(font);
            exit(0);
        }

        /* redraw overlay so the display doesn't time out while paused */
        if (disp) {
            al_set_target_backbuffer(disp);
            int w = al_get_display_width(disp);
            int h = al_get_display_height(disp);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            if (font) {
                al_draw_text(font, al_map_rgb(x,y,z), w/2, h/2 - 12, ALLEGRO_ALIGN_CENTER, "PAUSED");
                al_draw_text(font, al_map_rgb(x,y,z), w/2, h/2 + 8, ALLEGRO_ALIGN_CENTER,
                             "Press Enter/Space/Esc to resume, Q to quit");
            }
            al_flip_display();
        }
    }

    /* cleanup */
    al_unregister_event_source(queue, al_get_keyboard_event_source());
    if (disp) al_unregister_event_source(queue, al_get_display_event_source(disp));
    al_destroy_event_queue(queue);
    if (font) al_destroy_font(font);
}