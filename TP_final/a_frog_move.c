/*
 * sprites.c
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "a_sprites.h"

#include "entidades.h"

extern frog;
extern MovedUp; 
extern MovedDOWN;
extern MovedLEFT;
extern MovedRIGHT;
extern FollowingSupp;
extern FlagDied;

void frog_move_up (){  //Esto no es, hayq hacer if cases con los flags de movimiento / muerte para cambiar los sprites//

}

int move() {
    al_init();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // 60 FPS

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Load your sprite
    ALLEGRO_BITMAP* sprite = al_load_bitmap("my_sprite.png");
    
    float x = 320.0, y = 240.0; // Initial position
    float speed = 5.0;          // Movement speed
    bool redraw = true;
    bool running = true;

    al_start_timer(timer);

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Update logic
            ALLEGRO_KEYBOARD_STATE key_state;
            al_get_keyboard_state(&key_state);

            if (al_key_down(&key_state, ALLEGRO_KEY_UP))    y -= speed;
            if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))  y += speed;
            if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))  x -= speed;
            if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) x += speed;

            redraw = true;
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            // Draw sprite at new coordinates
            al_draw_bitmap(sprite, x, y, 0); 
            
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_bitmap(sprite);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}