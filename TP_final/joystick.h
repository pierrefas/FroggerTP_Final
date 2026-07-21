/*
 * joystick.h
 *
 * Traduce las lecturas crudas del joystick (joydrv.h) en cuatro flags de
 * direccion con enclave: una vez detectada una direccion se mantiene fija
 * hasta que el stick vuelve a la zona muerta, para que un solo empujon no
 * se lea como varios pasos seguidos.
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H
#define DEADZONE 100 // zona muerta del joystick
extern char isUp;
extern char isDwn;
extern char isLft;
extern char isRgt;

/**
 * @brief Lee el joystick (joy_read) y actualiza isUp/isDwn/isLft/isRgt
 * con la direccion detectada (una sola activa a la vez, con enclave
 * hasta volver a la zona muerta). Hay que llamarla una vez por ciclo
 * de juego antes de leer esas flags.
 * @return distinto de 0 si el switch del joystick esta presionado.
 */
int joystic_update(void);

#endif