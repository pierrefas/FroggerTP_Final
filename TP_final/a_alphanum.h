#ifndef FROGGER_TEXT_H
#define FROGGER_TEXT_H

/**
 * @brief Imprime caracteres alfanuméricos en pantalla utilizando el spritesheet de Frogger.
 *
 * @param text  Puntero a la cadena de caracteres NUL-terminated a imprimir.
 * @param x     Posición inicial en el eje X.
 * @param y     Posición inicial en el eje Y.
 * @param color Selector de color (valores de 0 a 3).
 *
 * @return int  0: Éxito o fin de pantalla.
 *              <0: Error.
 */
int index_disp(const char *text, int x, int y, int color);

/**
 * @brief Ancho en pixeles que ocuparia text dibujado con index_disp
 * (para centrar). 0 si text es NULL.
 */
int index_disp_len(const char *text);

#endif // FROGGER_TEXT_H
