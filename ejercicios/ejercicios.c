#include <stdio.h>
#include <stdint.h>

// Resolucion Guia de Ejercicios

void zeros(uint32_t * vector, uint32_t longitud);
void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
void productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void invertir (uint16_t * vector, uint32_t longitud);
int32_t max (int32_t * vectorIn, uint32_t longitud);
void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn);

int main()
{
    int16_t vec1[] = {1, 2, 3, 3, 5, 0, 7, 2, 10, 11, 0, 1, 14, 5}, vec2[15];
    uint32_t longitud = 14;

    for(unsigned int i = 0;i < longitud;i++)
        printf("%d ", vec1[i]);
    
    printf("\n");

    filtroVentana10(vec1, vec2, longitud);

    //printf("%d ", res);

    for(unsigned int i = 0;i < longitud;i++)
        printf("%d ", vec2[i]);

    return 0;
}

void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn)
{
	uint32_t i, index = 0, aux;
	uint16_t avg = 0;

	while(index < longitudVectorIn)
	{
		for(i = 0;i < 10;i++)
		{
			aux = (index + i) >= longitudVectorIn ? (index + i) % longitudVectorIn : (index + i);
			avg += vectorIn[aux];
		}

		vectorOut[index] = avg/10;

		avg = 0;
		index++;
    }

}

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

void invertir (uint16_t * vector, uint32_t longitud)
{
	uint16_t aux;
	uint32_t index1 = 0, index2 = longitud - 1, loops;

	loops = longitud/2;
	while(loops--)
	{
		aux = vector[index2];
		vector[index2] = vector[index1];
		vector[index1] = aux;
		index1++;
		index2--;
	}
}

int32_t max (int32_t * vectorIn, uint32_t longitud)
{
    int32_t maxValue = vectorIn[longitud-1];
    int32_t maxIndex = longitud;

    longitud--;
    while(longitud--)
    {
        if(vectorIn[longitud] >= maxValue)
        {
            maxValue = vectorIn[longitud];
            maxIndex = longitud + 1;
        }

    }

    return maxIndex;
}