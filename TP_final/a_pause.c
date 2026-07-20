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

#define MAX_HIGHSCORES 10
#define MAX_LINE_LEN 128
#define HIGHSCORE_FILE "highscores.txt"

/* Read up to MAX_HIGHSCORES lines from HIGHSCORE_FILE into 'out'.
 * Returns number of lines read (>=1 — returns 1 with placeholder if file missing). */
static int read_highscores(char out[MAX_HIGHSCORES][MAX_LINE_LEN])
{
    FILE *f = fopen(HIGHSCORE_FILE, "r");
    int count = 0;
    if (f) {
        while (count < MAX_HIGHSCORES && fgets(out[count], MAX_LINE_LEN, f)) {
            size_t L = strlen(out[count]);
            if (L && out[count][L-1] == '\n') out[count][L-1] = '\0';
            ++count;
        }
        fclose(f);
    }

    if (count == 0) {
        /* placeholder if file missing or empty */
        strncpy(out[0], "No highscores (highscores.txt)", MAX_LINE_LEN-1);
        out[0][MAX_LINE_LEN-1] = '\0';
        count = 1;
    }
    return count;
}

int pause_menu(game_state *gs)
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

    char scores[MAX_HIGHSCORES][MAX_LINE_LEN];
    int score_count = read_highscores(scores);

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

                int rows_per_col = 5;
        int col_gap = 40;
        int col_width = 160;
        int left_x = w/2 - (col_width/2) - col_gap/2;
        int right_x = w/2 + (col_gap/2);
        int start_y = 88;
        int line_h = 18;

        /* left column */
        for (int i = 0; i < rows_per_col; ++i) {
            int idx = i;
            if (idx < score_count) {
                if (font) al_draw_text(font, al_map_rgb(220,220,220), left_x, start_y + i*line_h, ALLEGRO_ALIGN_LEFT, scores[idx]);
            }
        }
        /* right column */
        for (int i = 0; i < rows_per_col; ++i) {
            int idx = rows_per_col + i;
            if (idx < score_count) {
                if (font) al_draw_text(font, al_map_rgb(220,220,220), right_x, start_y + i*line_h, ALLEGRO_ALIGN_LEFT, scores[idx]);
            }
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
            case ALLEGRO_KEY_R:
                
                if (font) al_destroy_font(font);
                al_unregister_event_source(queue, al_get_keyboard_event_source());
                if (disp) al_unregister_event_source(queue, al_get_display_event_source(disp));
                al_destroy_event_queue(queue);
                return PAUSE_RESET;
            
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