
#include <stdio.h>
#include <stdlib.h>
#include "Rummikub.h"

#define CORES {'!','@','#','$'}

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

	if (conjunto_temp->carta[n_coluna].nbr == '0')
	{
		conjunto_temp->carta[n_coluna] = player[numpl].carta[card];
	}else
	{
		clear();
		printf("Local ja ocupado!!\n");
		return;
	}

	for (int i = card; i < player[numpl].cards; ++i)
	{
		player[numpl].carta[i] = player[numpl].carta[i + 1];
	}
	player[numpl].cards--;

	if (conjunto_temp->next == NULL)
	{
		conjunto_temp->next = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
		conjunto_temp = conjunto_temp->next;
		conjunto_temp->next = NULL;
		for (int i = 0; i < 13; ++i)
		{
			conjunto_temp->carta[i].nbr = '0';
		}
	}
	clear();
}

void pegar_carta(t_tabuleiro_ptr conjunto, t_player* player, int numpl)
{
	int linha;
	char coluna;
	int n_coluna;
	t_tabuleiro_ptr conjunto_temp = conjunto;

	printf("Que carta deseja adicionar ao seu baralho?\n");
	printf("Linha: ");
	scanf("%d", &linha);
	printf("Coluna: ");
	scanf(" %c", &coluna);

	if (coluna >= 'a' && coluna <= 'm')
	{
		n_coluna = coluna - 'a';
	}else if (coluna >= 'A' && coluna <= 'M')
	{
		n_coluna = coluna - 'A';
	}else{
		printf("Coluna invalida!!!\n");
		exit(0);
	}

	for (int i = 0; i < linha - 1; ++i)
	{
		conjunto_temp = conjunto_temp->next;
	}

	clear();
	if (conjunto_temp->carta[n_coluna].nbr == '0')
	{
		printf("Nao existe carta aqui!");
	}else{
		player[numpl].carta[player[numpl].cards] = conjunto_temp->carta[n_coluna];
		player[numpl].cards++;
		conjunto_temp->carta[n_coluna].nbr = '0';
	}
}

void resetar_jogada(t_tabuleiro_ptr conjunto_temp, t_tabuleiro_ptr conjunto, t_player* player, t_player player_temp, int numpl)
{
	t_tabuleiro_ptr aux;
	while(conjunto_temp != NULL)
	{
		if (conjunto_temp->next == NULL)
		{
			for (int i = 0; i < 13; ++i)
			{
				conjunto->carta[i].nbr = '0';
			}
			aux = conjunto->next;
			conjunto->next = NULL;
			break;
		}
		for (int i = 0; i < 13; ++i)
		{
			conjunto->carta[i] = conjunto_temp->carta[i];
		}
		conjunto = conjunto->next;
		conjunto_temp = conjunto_temp->next;
	}
	conjunto = aux;
	while(conjunto != NULL)
	{
		if (conjunto->next != NULL)
		{
			aux = conjunto->next;
			free(conjunto);
			conjunto = aux;
		}else
		{
			free(conjunto);
			conjunto = NULL;
		}
	}
	player[numpl].cards = player_temp.cards;
	for (int i = 0; i < player_temp.cards; ++i)
	{
		player[numpl].carta[i] = player_temp.carta[i];
	}
}

int checar(t_tabuleiro_ptr conjunto){
	int tipo; //verifica se eh uma trinca(1), sequencia(2) ou invalida(3)
	int flag = 1;
	int c;
	int i;
	char cores[4] = CORES;
	int cores_usadas[4]; //no caso da trinca ou quadra, verifica qual cor ja foi usada
	while(conjunto != NULL)
	{
		for (i = 0; i < 4; ++i)
		{
			cores_usadas[i] = 0;
		}
		c = 0;
		tipo = 0;
		for (i = 0; !tipo; ++i)
		{
			if (conjunto->carta[i].nbr != '0')
			{
				if(conjunto->carta[i].nbr == (conjunto->carta[i+1].nbr) - 1){
					tipo = 2;
				}else if (conjunto->carta[i].nbr == conjunto->carta[i+1].nbr)
				{
					tipo = 1;
				}else{
					flag = 0;
					return flag;
				}
			}
		}
		printf("%d\n", tipo);
		if (tipo == 2)
		{
			for ( ; (i < 13) && (conjunto->carta[i].nbr !='0'); ++i)
			{
				if (((conjunto->carta[i].cor != conjunto->carta[i+1].cor) || (conjunto->carta[i].nbr != (conjunto->carta[i+1].nbr)-1))&&(conjunto->carta[i+1].nbr != '0')&&(i < 13))
				{
					flag = 0;
					return flag;
				}else{
					c++;
				}
			}
		}
		if (tipo == 1)
		{
			for (i = 0; (i < 13)&&(conjunto->carta[i].nbr != '0'); ++i)
			{
				if ((conjunto->carta[i].nbr != conjunto->carta[i+1].nbr)&&(conjunto->carta[i+1].nbr != '0')&&(i<13))
				{
					flag = 0;
					return flag;
				}else
				{
					c++;
					if (conjunto->carta[i].cor == cores[0])
					{
						cores_usadas[0]++;
					}else if (conjunto->carta[i].cor == cores[1])
					{
						cores_usadas[1]++;
					}else if (conjunto->carta[i].cor == cores[2])
					{
						cores_usadas[2]++;
					}else if (conjunto->carta[i].cor == cores[3])
					{
						cores_usadas[3]++;
					}
				}
				for (int k = 0; k < 4 ; ++k)
				{
					if (cores_usadas[k] != 1)
					{
						flag = 0;
						return flag;
					}
				}
			}

		}

		for ( ; i < 13; ++i)
		{
			if(conjunto->carta[i].nbr != '0')
			{
				flag = 0;
				break;
			}
		}	

		if (c < 3)
		{
			flag = 0;
			return flag;
		}
	}
	return flag;
}

int somar_mao(t_player* player, int numpl){
	int cont = 0;
	for (int i = 0; i < player[numpl].cards; i++)
	{
		cont =  (cont) +(int) ( player[numpl].carta[i].nbr - '0') ;
	}
	return cont;
}

int* fim_jogo(int player_nbr , t_player* player ){
	int total;
	int* cont;
	int* pontos;
	cont = (int*) malloc ((player_nbr)*sizeof(int));
	pontos = (int*) malloc ((player_nbr)*sizeof(int));
	for (int i = 0; i < player_nbr; ++i)
	{
		cont[i] = somar_mao(player, i);
	}
	for (int i = 0; i < player_nbr; ++i)
	{
		if(somar_mao(player , i)==0){
			for (int i = 0; i < player_nbr; ++i)
			{
				total= total + cont[i];
			}
			pontos[i]= total;
		}
		else{
			pontos[i]=-cont[i];
		}
	}
	return pontos;
}
