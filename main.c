#include <stdio.h>
#include <stdlib.h>

#include "Rummikub.h"

#define CARTA_NBR 104
#define CORINGA_NBR 2

int main()
{
    t_player* player;
    int player_nbr;
    int flag = 0;
    t_carta* carta;
    carta = (t_carta*)malloc((CARTA_NBR+CORINGA_NBR)*sizeof(t_carta));
    baralho(carta);
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
    player = (t_player*)malloc(player_nbr*sizeof(t_player));
    if (player == NULL){
        printf("Memoria insuficiente! encerrando!!!\n");
        exit(0);
    }


    free(player);
    free(carta);
}
