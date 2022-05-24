/*
 * c_func.c
 *
 *  Created on: May 24, 2022
 *      Author: Lucas
 */

#include "c_func.h"

void zeros(uint32_t * vector, uint32_t longitud)
{
    while(longitud--)
        vector[longitud] = 0;
}

void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar)
{
    //uint64_t aux;

    while(longitud--)
    {
        vectorOut[longitud] = escalar*vectorIn[longitud];

        //if(aux > pow(2, 32))

    }

}

void productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
{
    while(longitud--)
        vectorOut[longitud] = escalar*vectorIn[longitud];
}

void productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
{
    uint32_t aux;

    while(longitud--)
    {
        aux = escalar*vectorIn[longitud];

        if(aux > 4095)
            vectorOut[longitud] = 4095;
        else
            vectorOut[longitud] = aux;
    }

}
