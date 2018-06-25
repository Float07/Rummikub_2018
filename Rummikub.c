#include <stdlib.h>
#include <stdio.h>

#include "Rummikub.h"
#define CARTA_NBR 104
#define CORINGA_NBR 2
#define START_CARDS 14
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

void criar_baralho(t_carta* carta)
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
}

t_player* alocar_jogadores(int player_nbr)
{
	int c;
	t_player* player;

	player = (t_player*)malloc(player_nbr*sizeof(t_player));

	for (c = 0; c < player_nbr; c++)
	{
		player[c].carta = (t_carta*)malloc((CARTA_NBR+CORINGA_NBR)*sizeof(t_carta));
		player[c].carta[0].cor = '!';
		player[c].carta[0].nbr = '1';
		if (player[c].carta == NULL)
		{
			printf("Memoria insuficiente!! encerrando!\n");
			exit(0);
		}
	}

	return player;
}

void liberar_jogadores(int player_nbr, t_player* player)
{
	int c;
	for (c = 0; c < player_nbr; c++)
	{
		free(player[c].carta);
	}
	free(player);
}

void clear()
{
	#ifdef _WIN32
    system("cls");
	#else
    system("clear");
	#endif
}

void distribuir_baralho(int n, t_player* player, t_carta* baralho, int* cartas_baralho)
{
	int steps;

	for (int i = 0; i < n; ++i)
	{
		player[i].cards = 0;
		for (int c = 0; c < START_CARDS; ++c)
		{
			steps = rand() % *cartas_baralho;
			player[i].carta[c] = baralho[steps];
			player[i].cards++;
			for (int k = steps; k < *cartas_baralho; ++k)//preenche os espaços vazios após a carta ter sido comprada
			{
				baralho[k] = baralho[k+1];
			}
			(*cartas_baralho)--;
		}
	}
}

void comprar_carta(t_player* player, t_carta* baralho, int* cartas_baralho, int numpl)
{
	if (cartas_baralho == 0)
	{
		printf("Nao existem cartas no baralho!\n");
		return;
	}
	int steps = rand() % *cartas_baralho;
	player[numpl].carta[player[numpl].cards] = baralho[steps];
	for (int i = steps; i < *cartas_baralho; ++i)
	{
		baralho[i] = baralho[i + 1];
	}
	(*cartas_baralho)--;
	player[numpl].cards++;
	clear();
}