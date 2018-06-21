#include <stdlib.h>
#include <stdio.h>

#include "Rummikub.h"

#define CARTA_NBR 104
#define CORINGA_NBR 2
#define CORES {'!','@','#','$'}

char binario_hexa(int n)
{
	char caracter;
	if(n <= 9){
		caracter = '0' + n;
	}else{
		caracter = 'A' + n - 10;
	}
	return caracter;
}

void baralho(t_carta* carta)
{
	char cores[4] = CORES;
	int c, k = -1;
	int numero;//valor numerico no numero da carta
	for (c = 0; c < CARTA_NBR; c += 2)
	{
		if (c % (CARTA_NBR/4) == 0)
		{
			k++;
			numero = 1;
		}
		carta[c].nbr = binario_hexa(numero);
		carta[c + 1].nbr = binario_hexa(numero);
		carta[c].cor = cores[k];
		carta[c + 1].cor = cores[k];
		numero++;
	}
	for(c = 0; c < CORINGA_NBR; c++){
		carta[CARTA_NBR + c].cor = '*';
		carta[CARTA_NBR + c].nbr = '*';
	}
	printf("Testando as cartas!!!\n");
	for (c = 0; c < CARTA_NBR + CORINGA_NBR; c++)
	{
		printf("carta %d: %c%c\n",c+1, carta[c].nbr, carta[c].cor);
	}
}
