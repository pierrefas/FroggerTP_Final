#include "drawleds.h"

// Vinculacion con el arreglo de largos de Juanga (levelset.c).
// Su tamano debe coincidir con NUM_ENTITY_TYPES (ver drawleds.h).
extern int lentypes[];

// Dibuja un unico punto para la rana
void led_draw_frog(int x_px, int y_height) {
    dcoord_t coord;
    coord.x = (uint8_t)(x_px >> 4); // Division por 16 con desplazamiento de bits
    coord.y = (uint8_t)y_height;    // Altura directa

    // Se limita a PLAY_FIELD_MAX_X (no a DISP_MAX_X) para que la rana no
    // pueda dibujarse sobre la columna separadora ni sobre la de vidas.
    if (y_height >= DISP_MIN && coord.x <= PLAY_FIELD_MAX_X && coord.y <= DISP_MAX_Y) {
        disp_write(coord, D_ON);
    }
}

// Dibuja autos o troncos estirandolos segun su tipo
void led_draw_entity(int x_px, int y_height, int type) {
    // Chequeo defensivo: sin esto, un type fuera de rango leeria
    // lentypes[] fuera de sus limites (comportamiento indefinido).
    if (type < 0 || type >= NUM_ENTITY_TYPES) {
        return;
    }

    int x_start_led = x_px >> 4;
    int largo = lentypes[type];

    for (int i = 0; i < largo; i++) {
        int current_x = x_start_led + i;

        // Filtro para mantener el dibujo dentro de la zona de juego (columnas 0 a 13)
        if (current_x >= 0 && current_x <= PLAY_FIELD_MAX_X &&
            y_height >= DISP_MIN && y_height <= DISP_MAX_Y) {
            dcoord_t coord;
            coord.x = (uint8_t)current_x;
            coord.y = (uint8_t)y_height;
            disp_write(coord, D_ON);
        }
    }
}

// Dibuja la barra de tiempo en la fila fija TIME_BAR_ROW
void led_draw_time(int time_val) {
    for (int t = 0; t < time_val; t++) {
        if (t > PLAY_FIELD_MAX_X) {
            break; // ya no queda lugar en la barra
        }
        dcoord_t coord = {(uint8_t)t, TIME_BAR_ROW};
        disp_write(coord, D_ON);
    }
}

// Dibuja el contador de vidas en la columna fija LIVES_COLUMN
void led_draw_lives(int lives_val) {
    for (int v = 0; v < lives_val; v++) {
        if (v > DISP_MAX_Y) {
            break; // no hay mas filas donde dibujar
        }
        dcoord_t coord = {LIVES_COLUMN, (uint8_t)v};
        disp_write(coord, D_ON);
    }
}
