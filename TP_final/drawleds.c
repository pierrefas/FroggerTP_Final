#include "drawleds.h"

#include <string.h>

// Vinculacion con el arreglo de largos de Juanga (levelset.c).
// Su tamano debe coincidir con NUM_ENTITY_TYPES (ver drawleds.h).
extern int lentypes[];

/* El campo de juego va dado vuelta VERTICALMENTE: la fila logica 0 (la
 * salida de la rana) sale abajo del panel y la fila de llegada arriba.
 * Solo se invierten las filas: espejar tambien las columnas (rotacion
 * completa de 180) daba vuelta el eje horizontal y el joystick quedaba
 * cruzado (derecha se veia como izquierda). Todo dibujo DEL JUEGO pasa
 * por aca; el texto usa led_write_abs, sin invertir. */
void led_write(int x, int y, dlevel_t val) {
    if (x < DISP_MIN || x > DISP_MAX_X || y < DISP_MIN || y > DISP_MAX_Y) {
        return;
    }
    dcoord_t coord = {(uint8_t)x, (uint8_t)(DISP_MAX_Y - y)};
    disp_write(coord, val);
}

/* Escritura SIN invertir, en coordenadas fisicas del panel: para el
 * texto 3x3 (marquesinas, iniciales), que tiene que leerse derecho
 * independientemente de como se dibuje el campo de juego. */
void led_write_abs(int x, int y, dlevel_t val) {
    if (x < DISP_MIN || x > DISP_MAX_X || y < DISP_MIN || y > DISP_MAX_Y) {
        return;
    }
    dcoord_t coord = {(uint8_t)x, (uint8_t)y};
    disp_write(coord, val);
}

// Dibuja un unico punto para la rana
void led_draw_frog(int x_px, int y_height) {
    int x = x_px >> 4; // Division por 16 con desplazamiento de bits

    // Se limita a PLAY_FIELD_MAX_X (no a DISP_MAX_X) para que la rana no
    // pueda dibujarse sobre la columna separadora ni sobre la de vidas.
    if (x >= DISP_MIN && x <= PLAY_FIELD_MAX_X) {
        led_write(x, y_height, D_ON);
    }
}

// Dibuja autos (val = D_ON, sobre calle apagada) o pisa el "agua" de la
// zona del lago (val = D_OFF: los soportes son LEDs apagados sobre las
// filas encendidas del lago), estirando la entidad segun su tipo.
void led_draw_entity(int x_px, int y_height, int type, dlevel_t val) {
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
        if (current_x >= 0 && current_x <= PLAY_FIELD_MAX_X) {
            led_write(current_x, y_height, val);
        }
    }
}

// Enciende todas las columnas de juego de las filas row_from..row_to
// (el "agua" del lago: encendida, con los soportes como huecos apagados).
void led_fill_rows(int row_from, int row_to) {
    for (int y = row_from; y <= row_to; y++) {
        for (int x = 0; x <= PLAY_FIELD_MAX_X; x++) {
            led_write(x, y, D_ON);
        }
    }
}

// Dibuja la barra de tiempo en la fila fija TIME_BAR_ROW
void led_draw_time(int time_val) {
    for (int t = 0; t < time_val; t++) {
        if (t > PLAY_FIELD_MAX_X) {
            break; // ya no queda lugar en la barra
        }
        led_write(t, TIME_BAR_ROW, D_ON);
    }
}

// Dibuja el contador de vidas en la columna fija LIVES_COLUMN
void led_draw_lives(int lives_val) {
    for (int v = 0; v < lives_val; v++) {
        if (v > DISP_MAX_Y) {
            break; // no hay mas filas donde dibujar
        }
        led_write(LIVES_COLUMN, v, D_ON);
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
// Usa led_write_abs: el texto no se invierte con el campo de juego.
static void draw_glyph_col(uint16_t pat, int gcol, int x, int top_row) {
    if (x < DISP_MIN || x > DISP_MAX_X) {
        return;
    }
    for (int r = 0; r < LED_GLYPH_H; r++) {
        if ((pat >> ((2 - r) * 3 + (2 - gcol))) & 1) {
            led_write_abs(x, top_row + r, D_ON);
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
