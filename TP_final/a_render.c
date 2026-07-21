#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "a_render.h"
#include "a_sprites.h"
#include "entityupdates.h" /* fase de buceo de las tortugas */
#include "levelset.h" /* extern level para el HUD */

/* Frames que dura el sprite de salto tras cada movimiento (a 30 fps). */
#define FROG_JUMP_FRAMES 4

/* Frames de salto pendientes; frog_anim_jump() lo recarga y el dibujo
 * del jugador lo va gastando. */
static int frog_jump_ticks = 0;

void frog_anim_jump(void){

    frog_jump_ticks = FROG_JUMP_FRAMES;

}

/* Un color distinto por tipo de entidad (0..4 enemigos, 5..9 soportes).
 * Solo se usa en el modo de respaldo sin spritesheet. */
static ALLEGRO_COLOR entity_color(int type){

    switch (type){
    case 0: return al_map_rgb(235, 220, 60);   /* auto amarillo */
    case 1: return al_map_rgb(240, 240, 240);  /* auto blanco */
    case 2: return al_map_rgb(210, 70, 210);   /* auto violeta */
    case 3: return al_map_rgb(80, 200, 230);   /* auto celeste */
    case 4: return al_map_rgb(220, 60, 60);    /* camion rojo */
    case 5: return al_map_rgb(150, 100, 50);   /* troncos marrones */
    case 6: return al_map_rgb(170, 115, 60);
    case 7: return al_map_rgb(135, 90, 45);
    case 8: return al_map_rgb(60, 160, 90);    /* tortugas verdes */
    case 9: return al_map_rgb(40, 130, 75);
    default: return al_map_rgb(128, 128, 128);
    }
}

/* Rana de 16x16 en (x, y) mirando segun orientation (0 arriba, 1 derecha,
 * 2 abajo, 3 izquierda). Con spritesheet usa el sprite del arcade; sin el,
 * cuerpo redondeado + dos ojos del lado del frente. */
static void draw_frog_at(int x, int y, int orientation){

    ALLEGRO_BITMAP * sprite = frog_sprites[orientation & 3];

    if (sprite){

        al_draw_bitmap(sprite, x + (ADJCOORDFROG(1) - al_get_bitmap_width(sprite)) / 2, y + (ADJCOORDFROG(1) - al_get_bitmap_height(sprite)) / 2, 0);
        return;

    }

    ALLEGRO_COLOR body = al_map_rgb(70, 220, 70);
    ALLEGRO_COLOR eyes = al_map_rgb(20, 60, 20);

    al_draw_filled_rounded_rectangle(x + 2, y + 2, x + 14, y + 14, 5, 5, body);

    switch (orientation){
    case 1: /* derecha */
        al_draw_filled_circle(x + 12, y + 5, 1.5, eyes);
        al_draw_filled_circle(x + 12, y + 11, 1.5, eyes);
        break;
    case 2: /* abajo */
        al_draw_filled_circle(x + 5, y + 12, 1.5, eyes);
        al_draw_filled_circle(x + 11, y + 12, 1.5, eyes);
        break;
    case 3: /* izquierda */
        al_draw_filled_circle(x + 4, y + 5, 1.5, eyes);
        al_draw_filled_circle(x + 4, y + 11, 1.5, eyes);
        break;
    default: /* arriba */
        al_draw_filled_circle(x + 5, y + 4, 1.5, eyes);
        al_draw_filled_circle(x + 11, y + 4, 1.5, eyes);
        break;
    }
}

/* Sprite centrado en el casillero de 16x16 cuya esquina superior
 * izquierda es (x, y). flip: ALLEGRO_FLIP_HORIZONTAL o 0. */
static void draw_in_cell(ALLEGRO_BITMAP * sprite, int x, int y, int flip){

    al_draw_bitmap(sprite, x + (ADJCOORDFROG(1) - al_get_bitmap_width(sprite)) / 2, y + (ADJCOORDFROG(1) - al_get_bitmap_height(sprite)) / 2, flip);

}

static void draw_support(support_entity * s){

    dive_phase phase = supportDivePhase(s);

    if (phase == SUPPORT_DIVED){
        return; /* sumergida: se ve el agua */
    }

    /* mientras se hunde alterna con el sprite semi-hundido como aviso */
    int sinking = (phase == SUPPORT_SINKING) && (s->divetimer / 4) % 2;

    int y = ROW_TO_Y(s->height);
    int cells = (s->endcoord - s->startcoord) / ADJCOORDFROG(1);
    int c;

    if (SUPPORT_IS_TURTLE(s->type) && turtle_sprite && turtle_dive) {

        /* un grupo de N tortugas: una por casillero */
        for (c = 0; c < cells; c++){

            draw_in_cell(sinking ? turtle_dive : turtle_sprite, s->startcoord + ADJCOORDFROG(c), y, 0);

        }

    }
    else if (!SUPPORT_IS_TURTLE(s->type) && log_left && log_mid && log_right){

        /* tronco continuo, sin costuras: la punta izquierda termina justo
         * donde arranca el primer tramo del medio (se alinea a la derecha
         * de su casillero, porque mide menos de 16), los tramos del medio
         * van pegados cada 16 px, y la punta derecha arranca justo al
         * final del ultimo tramo (alineada a la izquierda). */
        int y_log = y + (ADJCOORDFROG(1) - al_get_bitmap_height(log_mid)) / 2;

        al_draw_bitmap(log_left, s->startcoord + ADJCOORDFROG(1) - al_get_bitmap_width(log_left), y_log, 0);

        for (c = 1; c < cells - 1; c++){

            al_draw_bitmap(log_mid, s->startcoord + ADJCOORDFROG(c), y_log, 0);

        }

        al_draw_bitmap(log_right, s->startcoord + ADJCOORDFROG(cells - 1), y_log, 0);

    }
    else{

        ALLEGRO_COLOR col = entity_color(s->type);

        if (sinking){

            col = al_map_rgb(30, 80, 120); /* medio hundida bajo el agua */

        }
        al_draw_filled_rounded_rectangle(s->startcoord, y + 2, s->endcoord, y + 14, 4, 4, col);
    }
}

static void draw_enemy(game_state * g, enemy_entity * e){

    int y = ROW_TO_Y(e->height);

    if (e->type >= 0 && e->type < NUM_VEHICLE_TYPES && vehicle_sprites[e->type]){

        /* los vehiculos de la hoja miran a la izquierda: si su fila va
         * hacia la derecha, se espejan */
        int flip = (g->pspeedheight[e->height] > 0) ? ALLEGRO_FLIP_HORIZONTAL : 0;

        ALLEGRO_BITMAP * sprite = vehicle_sprites[e->type];

        al_draw_bitmap(sprite, (e->startcoord + e->endcoord - al_get_bitmap_width(sprite)) / 2, y + (ADJCOORDFROG(1) - al_get_bitmap_height(sprite)) / 2, flip);

        return;
    }

    al_draw_filled_rounded_rectangle(e->startcoord, y + 2, e->endcoord, y + 14, 3, 3, entity_color(e->type));
    /* parabrisas para que se lea como vehiculo */
    int mid = (e->startcoord + e->endcoord) / 2;
    al_draw_filled_rectangle(mid - 2, y + 4, mid + 2, y + 12, al_map_rgb(30, 30, 30));

}

void draw_game_state(game_state * g, int hide_player){

    if (!g) return;

    int i;

    /* soportes (lago) */
    for (i = 0; g->psoport[i].type != -1; i++){

        draw_support(&g->psoport[i]);

    }

    /* enemigos (calle) */
    for (i = 0; g->penemies[i].type != -1; i++){

        draw_enemy(g, &g->penemies[i]);

    }

    /* ranas ya guardadas en los huecos-meta */
    for (i = 0; i < NUM_GOAL_SLOTS; i++){

        if (g->safespaces[i]){

            if (home_frog){

                al_draw_bitmap(home_frog, GOAL_SLOT_X(i), ROW_TO_Y(GOALROW), 0);

            } 
            else{

                draw_frog_at(GOAL_SLOT_X(i), ROW_TO_Y(GOALROW), 2);

            }
        }
    }

    /* la rana del jugador: recien movida usa el cuadro de salto */
    if (g->prana && !hide_player){

        int o = g->prana->orientation & 3;
        ALLEGRO_BITMAP * jump = (frog_jump_ticks > 0) ? frog_jump_sprites[o] : NULL;

        if (jump){

            al_draw_bitmap(jump, g->prana->startcoord + (ADJCOORDFROG(1) - al_get_bitmap_width(jump)) / 2, ROW_TO_Y(g->prana->height) + (ADJCOORDFROG(1) - al_get_bitmap_height(jump)) / 2, 0);

        } 
        else{

            draw_frog_at(g->prana->startcoord, ROW_TO_Y(g->prana->height), o);

        }

        if (frog_jump_ticks > 0){

            frog_jump_ticks--;

        }
    }
}

void draw_death_at(int x, int row, int step){

    if (step < 0) step = 0;

    if (step >= NUM_DEATH_FRAMES) step = NUM_DEATH_FRAMES - 1;

    int y = ROW_TO_Y(row);
    ALLEGRO_BITMAP * sprite = death_sprites[step];

    if (sprite){

        al_draw_bitmap(sprite, x + (ADJCOORDFROG(1) - al_get_bitmap_width(sprite)) / 2, y + (ADJCOORDFROG(1) - al_get_bitmap_height(sprite)) / 2, 0);
        return;

    }

    /* respaldo sin spritesheet: circulo rojo que se apaga */
    al_draw_filled_circle(x + ADJCOORDFROG(1) / 2, y + ADJCOORDFROG(1) / 2, 7 - step, al_map_rgb(220, 60, 60));
}

void draw_hud(game_state * g, ALLEGRO_FONT * font, int time_left, int time_total){

    if (!g || !font){ 

        return;
        
    }

    al_draw_textf(font, al_map_rgb(255, 255, 255), 4, 4, 0, "SCORE %d", g->score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH - 4, 4,  ALLEGRO_ALIGN_RIGHT, "NIVEL %d", level);

    /* vidas: ranitas chicas abajo a la izquierda */
    int i;
    for (i = 0; g->prana && i < g->prana->lives; i++){
        
        if (frog_sprites[0]){

            al_draw_scaled_bitmap(frog_sprites[0], 0, 0, al_get_bitmap_width(frog_sprites[0]), al_get_bitmap_height(frog_sprites[0]), 4 + i * 14, GAME_HEIGHT - 14, 12, 12, 0);

        } 
        else{

            al_draw_filled_rounded_rectangle(4 + i * 14, GAME_HEIGHT - 13, 14 + i * 14, GAME_HEIGHT - 3, 3, 3, al_map_rgb(70, 220, 70));

        }
    }

    /* barra de tiempo abajo a la derecha (se achica y termina en rojo) */
    int bar_max = 100;
    int w = (time_total > 0) ? (bar_max * time_left) / time_total : 0;
    if (w < 0) w = 0;
    ALLEGRO_COLOR bar = (4 * time_left > time_total) ? al_map_rgb(80, 220, 80) : al_map_rgb(220, 60, 60);

    al_draw_rectangle(GAME_WIDTH - 5 - bar_max, GAME_HEIGHT - 13, GAME_WIDTH - 3, GAME_HEIGHT - 3, al_map_rgb(120, 120, 120), 1);

    al_draw_filled_rectangle(GAME_WIDTH - 4 - w, GAME_HEIGHT - 12, GAME_WIDTH - 4, GAME_HEIGHT - 4, bar);
}
