
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
	int i = 0;
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
		for (i = 0; i < 13; ++i)
		{
			conjunto_temp->carta[i].nbr = '0';
		}
	}
	clear();
}

void mudar_pos(t_tabuleiro_ptr conjunto, t_player* player, int numpl)
{
	int cont = 1;
	int flag3 = 0;
	int flag = 0;
	int flag2 = 0;
	int bandeira = 0;
	t_carta* aux = (t_carta*)malloc(sizeof(t_carta));
	int linha;
	int linha2;
	char coluna;
	char coluna2;
	int n_coluna;
	int n_coluna2;
	if (conjunto->next == NULL)
	{
		conjunto->next = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
		for (int i = 0; i < 13; ++i)
		{
			conjunto->carta[i].nbr = '0';
		}
	}
	while(flag3 == 0){
		while(flag2 == 0){
			printf("Que carta deseja mudar de posicao?\n");
			printf("Linha: ");
			scanf("%d", &linha);
			for (int i = 0; conjunto[i].next == NULL  ; ++i)
			{
				cont++;
			}
			if (linha > cont)
			{
				printf("Nao existe essa linha!\n");
				flag2 = 0;
			}
			else{
				flag2 = 1; 
			}
		}
		
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
		for (int n = 0; n < 13; ++n)
		{
			if(n == n_coluna){
				aux->nbr = conjunto[linha-1].carta[n].nbr;
				aux->cor = conjunto[linha-1].carta[n].cor;
			}
		}
		if(conjunto[linha-1].carta[n_coluna].nbr == '0'){
			printf("Nao ha carta nessa posicao!\n");
			flag3 = 0;
			flag2 = 0;
		}
		else{
			flag3 = 1;
			flag2 = 1;
		}
	}
	while(bandeira == 0 || flag ==0){
		printf("para qual posicao vc deseja mudar a carta?\n");
		while(bandeira == 0){
			printf("Linha:");
			scanf("%d", &linha2);
			if(conjunto[linha2-1].next == NULL){
				bandeira = 0; 
				printf("Essa linha não existe!");
			}
			else{
				bandeira = 1;
			}
		}
		while(flag == 0){
			printf("Coluna:");
			scanf(" %c", &coluna2);
			if (coluna2 >= 'a' && coluna2 <= 'm')
			{
				n_coluna2 = coluna2 - 'a';
			}else if (coluna2 >= 'A' && coluna2 <= 'M')
			{
				n_coluna2 = coluna2 - 'A';
			}else{
			printf("Coluna invalida!!!\n");
			exit(0);
			}
			printf("%c\n", conjunto[linha2-1].carta[n_coluna2].nbr );
			if(conjunto[linha2-1].carta[n_coluna2].nbr != '0'){
				printf("Ja ha uma carta nessa posicao!\n");
				flag = 0;
				bandeira = 0;
			}
			else{
			flag=1;
			}
		}
	}
	conjunto[linha2-1].carta[n_coluna2].nbr = aux->nbr;
	conjunto[linha2-1].carta[n_coluna2].cor = aux->cor; 
	conjunto[linha-1].carta[n_coluna].cor='0';
	conjunto[linha-1].carta[n_coluna].nbr='0';
	free(aux);
	clear();
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

void fim_jogo(int player_nbr , t_player* player){
	int total = 0;
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
	free(cont);
	free(pontos);
}
