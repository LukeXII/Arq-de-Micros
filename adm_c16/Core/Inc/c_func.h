/*
 * c_func.h
 *
 *  Created on: May 24, 2022
 *      Author: Lucas
 */

#ifndef INC_C_FUNC_H_
#define INC_C_FUNC_H_

#include "stm32f4xx_hal.h"

void zeros(uint32_t * vector, uint32_t longitud);
void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
void productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn);
void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
int32_t max (int32_t * vectorIn, uint32_t longitud);
void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
void invertir (uint16_t * vector, uint32_t longitud);

#endif /* INC_C_FUNC_H_ */
