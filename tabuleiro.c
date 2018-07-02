
#include <stdio.h>
#include <stdlib.h>
#include "Rummikub.h"

#define CORES {'!','@','#','$'}

void imprime_tabuleiro(t_tabuleiro_ptr conjunto, int n)
{
	if (n == 1)
	{	
		printf("_____________________________________________________________________\n");
		printf("   ");
   		for (int i = 0; i < 13; ++i)
    	{
   			printf("%c    ", 'A'+i);
    	}
    	printf("|\n");
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
	printf("|\n");
	if(conjunto->next != NULL)
	{
		imprime_tabuleiro(conjunto->next, n+1);
	}
	else
	{
		printf("____________________________________________________________________|\n");
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
	t_tabuleiro_ptr conjunto_temp2 = conjunto;
	int flag = 0; 
	int n = 0;
	int i = 0;
	int linha;
	char coluna;
	int n_coluna;
	int card; //A carta que o player escolhe adicionar
	printf("Escolha a posicao desejada\n");
	while(flag == 0){
		printf("Linha: ");
		scanf("%d", &linha);
		for(conjunto_temp2 = conjunto ; conjunto_temp2 != NULL ; conjunto_temp2 = conjunto_temp2->next){
			n++;
		}
		if(linha > n  || linha <= 0){
			printf("Nao existe essa linha!!\n");
			flag = 0;
		}
		else{
			flag = 1;
		}
		if(flag)
		{
			t_tabuleiro_ptr conjunto_aux;
			int j = 0;
			for (conjunto_aux = conjunto; conjunto_aux != NULL; conjunto_aux = conjunto_aux->next)
			{
				j++;
			}
			if(linha > j)
			{
				flag = 0;
				printf("Nao existe essa linha!!\n");
			}
		} 
	}
	printf("Coluna: ");
	scanf(" %c", &coluna);

	if (coluna >= 'A' && coluna <= 'M')
	{
		n_coluna = coluna - 'A';
	}else if(coluna >= 'a' && coluna <= 'm')
	{
		n_coluna = coluna - 'a';
	}else{
		clear();
		printf("Coluna invalida!!!!");
		return;
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
		for (i = 0; i < 13; ++i)
		{
			conjunto_temp->carta[i].nbr = '0';
		}
	}
	clear();
}

void mudar_pos(t_tabuleiro_ptr conjunto, t_player* player, int numpl)
{
	t_tabuleiro_ptr conjunto_aux;
	int linha;
	char coluna;
	int n_coluna;
	int flag = 0;
	t_carta carta_aux;

	printf("Digite a posicao da carta que deseja mudar\n");
	while(!flag)
	{
		int n = 0;
		printf("Linha: ");
		scanf("%d", &linha);
		for (conjunto_aux = conjunto; conjunto_aux != NULL; conjunto_aux = conjunto_aux->next)
		{
			n++;
		}
		if (linha >= n || linha <= 0)
		{
			printf("Linha invalida, digite novamente\n");
		}else
		{
			flag = 1;
		}
		if (flag)
		{
			flag = 0;
			conjunto_aux = conjunto;
			for (int i = 1; i < linha; ++i)
			{
				conjunto_aux = conjunto_aux->next;
			}
			for (int i = 0; i < 13; ++i)
			{
				if (conjunto_aux->carta[i].nbr != '0')
				{
					flag = 1;
				}
			}
			if (!flag)
			{
				printf("Nao existem cartas nessa coluna!!\n");
			}
		}
	}
	flag = 0;
	conjunto_aux = conjunto;
	while(!flag)
	{
		printf("Coluna: ");
		scanf(" %c", &coluna);
		if ((coluna >= 'A')&&(coluna <= 'M'))
		{
			n_coluna = coluna - 'A';
		}else
		{
			n_coluna = coluna - 'a';
		}
		if ((n_coluna <= 12)&&(n_coluna >= 0))
		{
			flag = 1;
		}else
		{
			printf("Coluna invalida!\n");
		}
		for (int i = 1; i < linha; ++i)
		{
			conjunto_aux = conjunto_aux->next;
		}
		if (conjunto_aux->carta[n_coluna].nbr == '0')
		{
			flag = 0;
			printf("Nao existe carta aqui!!\n");
		}
	}
	flag = 0;
	conjunto_aux = conjunto;
	for (int i = 1; i < linha; ++i)
	{
		conjunto_aux = conjunto_aux->next;
	}
	carta_aux.cor = conjunto_aux->carta[n_coluna].cor;
	carta_aux.nbr = conjunto_aux->carta[n_coluna].nbr;
	conjunto_aux->carta[n_coluna].nbr = '0';

	printf("Onde deseja posicionar essa carta?\n");
	printf("Linha: ");
	while(!flag)
	{
		int n = 0;
		scanf("%d", &linha);
		for (conjunto_aux = conjunto; conjunto_aux != NULL; conjunto_aux = conjunto_aux->next)
		{
			n++;
		}
		if (linha > n)
		{
			printf("Linha inexistente\n");
		}else
		{
			flag = 1;
		}
		if(flag)
		{
			conjunto_aux = conjunto;
			flag = 0;
			for (int i = 1; i < linha; ++i)
			{
				conjunto_aux = conjunto_aux->next;
			}
			for (int i = 0; i < 13; ++i)
			{
				if (conjunto_aux->carta[i].nbr == '0')
				{
					flag = 1;
				}
			}
			if (!flag)
			{
				printf("Nao existem espacos livres na linha escolhida!!\n");
			}
		}
	}
	flag = 0;
	conjunto_aux = conjunto;

	printf("Coluna: ");
	while(!flag)
	{
		scanf(" %c", &coluna);
		if ((coluna >= 'A')&&(coluna <= 'M'))
		{
			n_coluna = coluna - 'A';
		}else
		{
			n_coluna = coluna - 'a';
		}
		if ((n_coluna <= 12)&&(n_coluna >= 0))
		{
			flag = 1;
		}else
		{
			printf("Coluna invalida!!\n");
		}
		for (int i = 1; i < linha; ++i)
		{
			conjunto_aux = conjunto_aux->next;
		}
		if (conjunto_aux->carta[n_coluna].nbr != '0')
		{
			flag = 0;
			printf("Existe uma carta aqui!!\n");
		}
	}
	flag = 0;
	conjunto_aux = conjunto;

	for (int i = 1; i < linha; ++i)
	{
		conjunto_aux = conjunto_aux->next;
		if (conjunto_aux->next == NULL)
		{
			conjunto_aux->next = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
			(conjunto_aux->next)->next = NULL;
			for (int j = 0; j < 13; ++j)
			{
				(conjunto_aux->next)->carta[j].nbr = '0';
			}
		}
	}

	conjunto_aux->carta[n_coluna].nbr = carta_aux.nbr;
	conjunto_aux->carta[n_coluna].cor = carta_aux.cor;
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

int somar_mao(t_player* player, int numpl){
	int cont = 0;
	for (int i = 0; i < player[numpl].cards; i++)
	{
		if (player[numpl].carta[i].nbr == '*')
		{
			cont += 20;
		}else
		{
			cont += hexa_binario(player[numpl].carta[i].nbr);
		}
	}
	return cont;
}

void fim_jogo(int player_nbr , t_player* player, t_tabuleiro_ptr conjunto){
	int total = 0;
	int vencedor = 0;
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
			for (i = 0; i < player_nbr; ++i)
			{
				total = total + cont[i];
			}
			pontos[i] = total;
		}
		else{
			pontos[i] = -cont[i];
		}
	}
	for (int i = 0; i < player_nbr; ++i)
	{
		if (pontos[i] > pontos[vencedor])
		{
			vencedor = i;
		}
	}
	clear();
	for (int i = 0; i < player_nbr; ++i)
	{
		printf("Jogador %d: %d\n", i+1, pontos[i]);
	}
	printf("Parabens jogador %d, voce venceu!\n", vencedor + 1);
	free(cont);
	free(pontos);
	liberar_coluna(conjunto);
	exit(0);
}
