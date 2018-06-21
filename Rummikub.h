#ifndef RUMMIKUB_H_INCLUDED
#define RUMMIKUB_H_INCLUDED

typedef struct{
    char cor;
    char nbr;
}t_carta;

typedef struct{
    int cards;//quantidade de cartas do jogador
    t_carta* carta;
}t_player;

void baralho(t_carta* carta); //cria o baralho
t_player* alocar_jogadores(int player_nbr); //aloca espaço para os jogadores e para seus baralhos
void liberar_jogadores(int player_nbr, t_player* player);//Libera o espaço usado pelos jogadores e seus baralhos
void clear();
void imprime_tabuleiro();
//t_tabuleiro* criar_conjunto();//Cria um conjunto de acordo com a jogada

#endif // RUMMIKUB_H_INCLUDED
