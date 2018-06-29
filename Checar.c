#include <stdlib.h>
#include <stdio.h>

#include "Rummikub.h"
#define CARTA_NBR 104
#define CORINGA_NBR 2
#define START_CARDS 14
#define CORES {'!','@','#','$'}

int checar_tipo(t_tabuleiro conjunto, int conjunto_cartas, int coringas)
{
	int c = 0;
	int space = 0; //quantos coringas ocupam o espaço entre duas cartas;
	while(conjunto.carta[c].nbr != '0' && c < 13)
	{
		c++;
	}
	if (c == 13)
	{
		return 3;
	}
}

int checar(t_tabuleiro_ptr conjunto){
	int conjunto_cartas;
	int coringas;
	int flag;
	while(conjunto->next != NULL)
	{
		flag = 0;
		coringas = 0;
		conjunto_cartas = 0;
		int tipo; //1=>Sequência 2=>Trinca/quadra 3=>Conjunto vazio
		for (int i = 0; i < 13; ++i)
		{
			if (conjunto->carta[i].nbr != '0')
			{
				conjunto_cartas++;
			}
			if (conjunto->carta[i].nbr == '*')
			{
				coringas++;
			}
		}
		if (conjunto_cartas < 3 && conjunto_cartas > 0)
		{
			return 0;
		}
		if (conjunto_cartas == 3 && coringas)
		{
			flag = 1;
		}
		tipo = checar_tipo((*conjunto), conjunto_cartas, coringas);
		conjunto = conjunto->next;
	}
}