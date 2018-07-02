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

int hexa_binario(char c)
{
	int n;
	if ((c >= '1')&&(c <= '9'))
	{
		n = c - '0';
	}else
	{
		n = c - 'A' + 10;
	}
	return n;
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

t_tabuleiro_ptr copia_reset(t_tabuleiro_ptr conjunto_temp, t_tabuleiro_ptr conjunto, t_player* player, t_player* player_temp, int numpl)
{
	t_tabuleiro_ptr conjunto_aux = conjunto_temp;
	while(conjunto->next != NULL)
	{
		if (conjunto_aux->next == NULL)
		{
			conjunto_aux->next = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
		}
		for (int i = 0; i < 13; ++i)
		{
			conjunto_aux->carta[i] = conjunto->carta[i];
		}

		conjunto_aux =conjunto_aux->next;
		conjunto = conjunto->next;
	}
	for (int i = 0; i < 13; ++i)
	{
		conjunto_aux->carta[i].nbr = '0';
	}
	conjunto_aux->next = NULL;
	player_temp->cards = player[numpl].cards;
	for (int i = 0; i < player[numpl].cards; ++i)
	{
		player_temp->carta[i] = player[numpl].carta[i];
	}
	return conjunto_temp;
}

void distribuir_baralho_texto(int player_nbr,t_player* player, t_carta* baralho, int* cartas_baralho)
{
	int k;
	char temp;
	FILE* input = fopen("baralho.txt", "rt");
	if(input == NULL)
	{
		printf("Nao foi possivel abrir o arquivo!\n");
		exit(0);
	}
	for (int i = 0; i < START_CARDS; ++i)
	{
		for (int c = 0; c < player_nbr; ++c)
		{
			k = 0;
			fscanf(input, "%c", &player[c].carta[i].nbr);
			fscanf(input, "%c", &player[c].carta[i].cor);
			fscanf(input, "%c", &temp);
			for (int k = 0; k < *cartas_baralho; ++k)
			{
				if (baralho[k].nbr == player[c].carta[i].nbr && baralho[k].cor == player[c].carta[i].cor)
				{
					break;
				}
			}
			(*cartas_baralho)--;
			for ( ; k < *cartas_baralho; ++k)
			{
				baralho[k] = baralho[k+1];
			}
		}
	}
	for (int i = 0; i < player_nbr; ++i)
	{
		player[i].cards = START_CARDS;
	}
}