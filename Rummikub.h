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

struct tabuleiro{
	int n;
	t_carta carta[13];
	struct tabuleiro *next;
};
typedef struct tabuleiro t_tabuleiro; 
typedef t_tabuleiro *t_tabuleiro_ptr;

void criar_baralho(t_carta* carta); //cria o baralho
t_player* alocar_jogadores(int player_nbr); //aloca espaço para os jogadores e para seus baralhos
void liberar_jogadores(int player_nbr, t_player* player);//Libera o espaço usado pelos jogadores e seus baralhos
void clear(); //limpa a tela (windows e linux)
void distribuir_baralho(int player_nbr, t_player* player, t_carta* baralho, int* cartas_baralho); // distribui aleatoriamente o baralho antes do jogo começar
void comprar_carta(t_player* player, t_carta* baralho, int* cartas_baralho, int numpl); //faz com que o jogador "numpl" receba uma carta aleatória do monte

#endif // RUMMIKUB_H_INCLUDED
