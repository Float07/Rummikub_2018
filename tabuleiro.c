
#include <stdio.h>
#include <stdlib.h>
#include "Rummikub.h"

/*t_tabuleiro_ptr criar_conjunto(t_tabuleiro_ptr novo) {
	
>>>>>>> master


t_tabuleiro_ptr criar_conjunto(t_tabuleiro_ptr novo, int numpl) {
	int aux;
	int num;
	printf("Quais cartas vc deseja adicionar?(no minimo 3)\n")
	for (int i = 0; i < t_player.cards; ++i)
	{
		printf("%d. %c%c  ", i+1, player[numpl].carta[i].nbr, player[numpl].carta[i].cor )
		
	}
 	scanf("%d", num);
}

*/
void imprime_tabuleiro(t_tabuleiro_ptr conjunto){
	for (int i = 0; i < conjunto->n; ++i){
		printf("%c%c ", conjunto->carta[i].nbr, conjunto->carta[i].cor );
	}
	printf("\n");
	if(conjunto->next != NULL)
	{
			imprime_tabuleiro(conjunto->next);
	}
	else
	{
		return;
	}
	
}

