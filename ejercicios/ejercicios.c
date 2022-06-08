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
void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
void corr(int16_t *vectorX, int16_t * vectorY, int16_t * vectorCorr, uint32_t longitud);

int main()
{
    int16_t vec1[] = {1, 2, 3, 4, 5, 6, 7};
    int16_t vec2[] = {0, 6, 2, 1, 1, 4, 8}, vec3[7];
    uint32_t longitud = 7;

    for(unsigned int i = 0;i < longitud;i++)
        printf("%d ", vec1[i]);
    
    printf("\n");

    corr(vec1, vec1, vec3, longitud);

    //printf("%d ", res);

    for(unsigned int i = 0;i < longitud;i++)
        printf("%d ", vec3[i]);

    return 0;
}

void corr(int16_t * vectorX, int16_t * vectorY, int16_t * vectorCorr, uint32_t longitud)
{
    uint32_t i, largo = longitud;

    while(longitud--)
    {
        vectorCorr[longitud] = 0;

        for(i = 0;i < largo;i++)
            vectorCorr[longitud] += vectorX[largo]*vectorY[largo - longitud];

    }

}

void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N)
{
    uint32_t index = 1, outIndex = 0, inIndex = 0;

    while(longitud--)
    {
        if(index < N)
        {
            vectorOut[outIndex] = vectorIn[inIndex];
            outIndex++;
        }
        else
            index = 0;

        inIndex++;
        index++;
    }
}

void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud)
{
    while(longitud--)
        vectorOut[longitud] = vectorIn[longitud] >> 16;
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