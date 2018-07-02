#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Rummikub.h"

#define CARTA_NBR 104
#define CORINGA_NBR 2

int main()
{	
    clear();
    int primeira;
    t_player* player;
    t_player player_temp;
    t_carta* baralho;
    baralho = (t_carta*)malloc((CARTA_NBR+CORINGA_NBR)*sizeof(t_carta));
    if (baralho == NULL)
    {
    	printf("Memoria insuficiente, encerrando!!!(Sindo muito)\n");
    	exit(0);
    }

    /*cria e zera o conjunto de cartas*/
    t_tabuleiro_ptr conjunto = (t_tabuleiro*)malloc(sizeof(t_tabuleiro));
    if (conjunto == NULL)
    {
    	printf("Memoria insuficiente, encerrando!\n");
    	exit(0);
    }
    conjunto->next = NULL;
    for (int i = 0; i < 13; ++i)
    {
    	conjunto->carta[i].nbr = '0';
    }

    t_tabuleiro* conjunto_temp = (t_tabuleiro_ptr)malloc(sizeof(t_tabuleiro));
    if (conjunto_temp == NULL)
    {
        printf("Memoria insuficiente! Encerrando =(\n");
        exit(0);
    }
    conjunto_temp->next = NULL;
    for (int i = 0; i < 13; ++i)
    {
        conjunto_temp->carta[i].nbr = '0';
    }
    /*cria e zera o conjunto de cartas*/

    int player_nbr;
    int flag = 0;
    int cartas_baralho = (CARTA_NBR + CORINGA_NBR);
    int victory = 0; //verifica se alguem venceu
    int numpl = 0; //indica o numero do player que está jogando
    int finalizar = 0; //verifica se o player deseja finalizar a jogada
    int opt; //registra a escolha do player durante sua jogada
    int valida; //verifica se a jogada foi valida

    criar_baralho(baralho);
    printf("                          ----------------------------\n");
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
    clock_t seed = clock();
    srand(seed);//define uma seed para o rand
    flag = 0;
   	clear();

    player = alocar_jogadores(player_nbr);
    for (int i = 0; i <= player_nbr; ++i)
    {
        player[i].numjogada=0;
    }
    player_temp.carta = (t_carta*)malloc((CARTA_NBR+CORINGA_NBR)*sizeof(t_carta));

    printf("Como deseja distribuir o baralho?(1-aleatorio/2-Arquivo de texto)\n");
    scanf("%d", &opt);
    if (opt == 1)
    {
        distribuir_baralho(player_nbr, player, baralho, &cartas_baralho);   
    }else
    {
        distribuir_baralho_texto(player_nbr, player, baralho, &cartas_baralho);
    }
    clear();
    
    while(!victory)
    {
    	printf("vez do jogador %d!\n", numpl + 1);
        conjunto_temp = copia_reset(conjunto_temp, conjunto , player, &player_temp , numpl);

    	finalizar = 0;
        valida = 1;
        while(!finalizar){
            printf("                               Mesa:\n");
            imprime_tabuleiro(conjunto, 1);
	    	printf("\n\n                               Sua mao:\n");
	    	imprime_mao(player, numpl);
	    	printf("\n\n                 O que deseja fazer?\n                 1-Adicionar uma carta\n                 2-Pegar uma carta\n                 3-Comprar uma carta\n\n                 0-Finalizar jogada\n");
	    	scanf("%d", &opt);
	    	clear();
	    	printf("                               Mesa:\n");
	    	imprime_tabuleiro(conjunto, 1);
	    	printf("\n\n                               Sua mao:\n");
	    	imprime_mao(player, numpl);
	    	printf("\n");
	       	if(player->numjogada == 0)
            {
                primeira = somar_mao(player , numpl);
            }
            if (opt == 1)
	    	{
	    		adicionar_carta(conjunto, player, numpl);
	    	}else if(opt == 2)
	    	{
	    		mudar_pos(conjunto, player, numpl);
	    	}else if (opt == 3)
	    	{
                resetar_jogada( conjunto_temp, conjunto, player , player_temp , numpl);
	    		comprar_carta(player, baralho, &cartas_baralho, numpl);
	    	    finalizar = 1;
            }
            else if(opt == 0){
                if(player[numpl].numjogada == 0){
                    int aux = primeira-somar_mao(player, numpl);
                    if (aux < 0)
                    {
                        resetar_jogada( conjunto_temp, conjunto, player , player_temp , numpl); //primeira jogada nao somou 30 nas cartas
                        clear();
                        valida = 0;
                    }
                }
                if (opt == 0)
                {
                    valida = checar(conjunto);
                    if (!valida)
                    {
                        resetar_jogada( conjunto_temp, conjunto, player , player_temp , numpl);
                    }else
                    {
                        player[numpl].numjogada++;
                        finalizar = 1;
                    }
                }
                else{
                    int aux2 = seguintes-player[numpl].cards;
                    if (aux2 >=  0)
                    {
                        resetar_jogada( conjunto_temp, conjunto, player , player_temp , numpl);
                    }

                }


            }		
        }
    	numpl = (numpl + 1)%player_nbr;
    }
    
    liberar_jogadores(player_nbr, player);
    free(baralho);
}