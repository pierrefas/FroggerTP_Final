#ifndef FROGGER_TEXT_H
#define FROGGER_TEXT_H

/**
 * @brief Imprime caracteres alfanuméricos en pantalla utilizando el spritesheet de Frogger.
 * 
 * @param arr   Puntero a la cadena de caracteres a imprimir.
 * @param size  Cantidad de caracteres a procesar (tamaño del array).
 * @param x     Posición inicial en el eje X.
 * @param y     Posición inicial en el eje Y.
 * @param color Selector de color (valores de 0 a 3).
 * 
 * @return int  0: Éxito o fin de pantalla.
 *              1: Error (arr es NULL).
 *              2: Error (coordenadas negativas).
 *              3: Error (coordenadas exceden GAME_WIDTH o GAME_HEIGHT).
 */
int index_disp(char *arr, int size, int x, int y, int color);

#endif // FROGGER_TEXT_H