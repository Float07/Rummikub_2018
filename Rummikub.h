#ifndef RUMMIKUB_H_INCLUDED
#define RUMMIKUB_H_INCLUDED

typedef struct{
    char cor;
    char nbr;
}t_carta;

typedef struct{
    int n;//numero do jogador
    int cards;
    t_carta carta;
}t_player;

void baralho(t_carta* carta); //cria o baralho

#endif // RUMMIKUB_H_INCLUDED
