
#include <stdio.h>
#include <stdlib.h>
#include "Rummikub.h"

/*t_tabuleiro_ptr criar_conjunto(t_tabuleiro_ptr novo) {
	

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
