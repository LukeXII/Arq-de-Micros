#include <stdio.h>
#include <stdint.h>

// Resolucion Guia de Ejercicios

void zeros(uint32_t * vector, uint32_t longitud);
void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
void productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);

int main()
{
    uint16_t vec1[] = {0, 4 , 1, 2500, 3};
    uint16_t vec2[5];

    for(unsigned int i = 0;i < 5;i++)
        printf("%d ", vec1[i]);
    
    printf("\n");

    productoEscalar12(vec1, vec2, 5, 4);

    for(unsigned int i = 0;i < 5;i++)
        printf("%d ", vec2[i]);

    return 0;
}

void zeros(uint32_t * vector, uint32_t longitud)
{
    while(longitud--)
        vector[longitud] = 0;
}

void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar)
{
    while(longitud--)
        vectorOut[longitud] = escalar*vectorIn[longitud];
}

void productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
{
    while(longitud--)
        vectorOut[longitud] = escalar*vectorIn[longitud];
}

void productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
{
    while(longitud--)
    {
        vectorOut[longitud] = escalar*vectorIn[longitud];

        if(vectorOut[longitud] > 4095)
            vectorOut[longitud] = 4095;
    }

}