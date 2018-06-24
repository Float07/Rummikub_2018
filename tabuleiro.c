
#include <stdio.h>
#include <stdlib.h>
#include "Rummikub.h"


void imprime_tabuleiro(t_tabuleiro_ptr conjunto, int n)
{
	if (n == 1)
	{	
		printf("   ");
   		for (int i = 0; i < 13; ++i)
    	{
   			printf("%c    ", 'A'+i);
    	}
    	printf("\n");
	}
	printf("%d. ", n);
	for (int i = 0; i < 13; ++i){
		if (conjunto->carta[i].nbr == '0')
		{
			printf("     ");
		}else
		{
			printf("%c%c   ", conjunto->carta[i].nbr, conjunto->carta[i].cor);
		}
	}
	printf("\n");
	if(conjunto->next != NULL)
	{
		imprime_tabuleiro(conjunto->next, n+1);
	}
	else
	{
		return;
	}
}

void imprime_mao(t_player* player, int numpl)
{
	for (int i = 0; i < player[numpl].cards; ++i)
	{
		if (i < 10)
		{
			printf("%d    ", i);
		}else if (i < 100)
		{
			printf("%d   ", i);
		}else
		{
			printf("%d  ", i);
		}
	}
	printf("\n");
	for (int i = 0; i < player[numpl].cards; ++i)
	{
		printf("%c%c   ", player[numpl].carta[i].nbr, player[numpl].carta[i].cor);
	}
}

void adicionar_carta(t_tabuleiro_ptr conjunto, t_player* player, int numpl)
{
	t_tabuleiro_ptr conjunto_temp = conjunto;
	int linha;
	char coluna;
	int n_coluna;
	int card; //A carta que o player escolhe adicionar
	printf("Escolha a posicao desejada\n");
	printf("Linha: ");
	scanf("%d", &linha);
	printf("Coluna: ");
	scanf(" %c", &coluna);

	if (coluna >= 'A' && coluna <= 'M')
	{
		n_coluna = coluna - 'A';
	}else if(coluna >= 'a' && coluna <= 'm')
	{
		n_coluna = coluna - 'a';
	}else{
		printf("Coluna invalida!!!!");
		exit(0);
	}
	for (int i = 0; i < linha - 1; ++i)
	{
		conjunto_temp = conjunto_temp->next;
	}

	printf("Qual carta deseja posicionar?\n");
	scanf("%d", &card);

	conjunto_temp->carta[n_coluna] = player[numpl].carta[card];
	for (int i = card; i < player[numpl].cards; ++i)
	{
		player[numpl].carta[i] = player[numpl].carta[i + 1];
	}
	player[numpl].cards--;

	if (conjunto_temp->next == NULL)
	{
		conjunto_temp->next = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
		conjunto_temp = conjunto_temp->next;
		conjunto_temp->n = 0;
		conjunto_temp->next = NULL;
		for (int i = 0; i < 13; ++i)
		{
			conjunto_temp->carta[i].nbr = '0';
		}
	}
}