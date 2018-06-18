#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* next; //aponta para o proximo card na mao de um jogador
    int used; //if used == 1, ja está é uso e não pode ser comprado.
    char cor;
    char nbr;
}t_carta;

typedef struct{
    int n;//numero do jogador
    int cards;
    t_carta* carta;
}t_player;

int main()
{
    t_carta carta;
    t_player* player;
    int player_nbr;
    int flag = 0;
    int c;
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
}
