#include "drawleds.h"

#include <string.h>

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

/*******************************************************************************
 * TEXTO 3x3
 ******************************************************************************/

// Cada cuantos ticks avanza una columna la marquesina (a ~20 ticks/seg,
// 2 => ~10 columnas/seg). Subirlo la hace mas lenta.
#define LED_SCROLL_TICKS_PER_COL 2

/* Glifos 3x3 transcritos de la imagen de referencia del grupo. Cada
 * caracter son 9 bits: fila superior en los bits 8-6, media en 5-3,
 * inferior en 2-0; dentro de cada fila el bit mas alto es el LED
 * izquierdo. Ejemplo A = 010/101/101:  .#.
 *                                      #.#
 *                                      #.#  */
static const uint16_t font3x3[36] = {
    0b010101101, // A
    0b110111111, // B
    0b111100111, // C
    0b110101110, // D
    0b111110111, // E
    0b011110100, // F
    0b110101111, // G
    0b101111101, // H
    0b111010111, // I
    0b111001111, // J
    0b101110101, // K
    0b100100111, // L
    0b111111101, // M
    0b111101101, // N
    0b111101111, // O
    0b111111100, // P
    0b111101011, // Q
    0b110110001, // R
    0b011010110, // S
    0b111010010, // T
    0b101101111, // U
    0b101101010, // V
    0b101111111, // W
    0b101010101, // X
    0b101010010, // Y
    0b110010011, // Z
    0b111101111, // 0
    0b010010010, // 1
    0b011010111, // 2
    0b111011111, // 3
    0b101111001, // 4
    0b111110011, // 5
    0b100111111, // 6
    0b111001001, // 7
    0b011111110, // 8
    0b111111001, // 9
};

// Patron del glifo de c, o 0 (todo apagado) si no hay glifo para c.
static uint16_t glyph_for(char c) {
    if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 'A';
    }
    if (c >= 'A' && c <= 'Z') {
        return font3x3[c - 'A'];
    }
    if (c >= '0' && c <= '9') {
        return font3x3[26 + (c - '0')];
    }
    return 0;
}

// Dibuja la columna gcol (0..2) del glifo pat en la columna x del display.
static void draw_glyph_col(uint16_t pat, int gcol, int x, int top_row) {
    if (x < DISP_MIN || x > DISP_MAX_X) {
        return;
    }
    for (int r = 0; r < LED_GLYPH_H; r++) {
        int y = top_row + r;
        if (y < DISP_MIN || y > DISP_MAX_Y) {
            continue;
        }
        if ((pat >> ((2 - r) * 3 + (2 - gcol))) & 1) {
            dcoord_t coord = {(uint8_t)x, (uint8_t)y};
            disp_write(coord, D_ON);
        }
    }
}

void led_draw_text(const char * msg, int x, int top_row) {
    if (msg == NULL) {
        return;
    }
    for (int i = 0; msg[i] != '\0'; i++) {
        uint16_t pat = glyph_for(msg[i]);
        for (int gc = 0; gc < 3; gc++) {
            draw_glyph_col(pat, gc, x + i * LED_CHAR_PITCH + gc, top_row);
        }
    }
}

void led_scroll_start(led_scroll * s, const char * msg) {
    if (s == NULL) {
        return;
    }
    s->msg = msg;
    s->len = (msg != NULL) ? (int)strlen(msg) : 0;
    s->offset = -DISP_CANT_X_DOTS; // arranca fuera del display, por la derecha
    s->tick = 0;
}

int led_scroll_step(led_scroll * s, int top_row) {
    if (s == NULL || s->msg == NULL) {
        return 1;
    }

    led_draw_text(s->msg, -s->offset, top_row);

    if (++s->tick >= LED_SCROLL_TICKS_PER_COL) {
        s->tick = 0;
        s->offset++;
    }

    return s->offset >= s->len * LED_CHAR_PITCH;
}
