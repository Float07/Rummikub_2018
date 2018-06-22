#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Rummikub.h"

#define CARTA_NBR 104
#define CORINGA_NBR 2

int main()
{	
	clock_t seed = clock();
	srand(seed);//define uma seed para o rand
    clear();

    t_player* player;
    t_carta* baralho;
    baralho = (t_carta*)malloc((CARTA_NBR+CORINGA_NBR)*sizeof(t_carta));
    if (baralho == NULL)
    {
    	printf("Memoria insuficiente, encerrando!!!(Sindo muito)\n");
    	exit(0);
    }
    t_tabuleiro_ptr conjunto = (t_tabuleiro*)malloc(sizeof(t_tabuleiro));
    conjunto->n = 0;
    conjunto->next = NULL;

    int player_nbr;
    int flag = 0;
    int cartas_baralho = (CARTA_NBR + CORINGA_NBR);
    int victory = 0; //verifica se alguem venceu
    int numpl = 0; //indica o numero do player que está jogando

    criar_baralho(baralho);
    printf("                          -----------------------------\n");
    printf("                          |   Bem Vindo ao Rummikub!  |\n");
    printf("                          -----------------------------\n");
    while(!flag){
        printf("Numero de jogadores(1 - 5):");
        scanf("%d", &player_nbr);
        if(player_nbr < 1 || player_nbr > 5){
            printf("Numero invalido! Digite novamente!\n");
        }else{
            flag = 1;
        }
    }
    flag = 0;
   	clear();

    player = alocar_jogadores(player_nbr);
    distribuir_baralho(player_nbr, player, baralho, &cartas_baralho);
    while(!victory)
    {
    	printf("vez do jogador %d!\n", numpl + 1);

    	imprime_tabuleiro(conjunto, 1);

    	numpl = (numpl + 1)%player_nbr;
    }
    
    liberar_jogadores(player_nbr, player);
    free(baralho);
}
