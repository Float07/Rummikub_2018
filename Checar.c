#include <stdlib.h>
#include <stdio.h>

#include "Rummikub.h"
#define CARTA_NBR 104
#define CORINGA_NBR 2
#define START_CARDS 14
#define CORES {'!','@','#','$'}

int checa_sequencia(t_tabuleiro conjunto, int coringas)
{

}

int checar_tipo(t_tabuleiro conjunto)
{
	int c = 0;
	int k;
	int space = 0; //quantos coringas ocupam o espaço entre duas cartas;
	while((conjunto.carta[c].nbr == '*' || conjunto.carta[c].nbr == '0') && c < 13)
	{
		c++;
	}
	if (c == 13)
	{
		return 3;
	}
	k = c + 1;
	for (; conjunto.carta[k].nbr == '*'; ++k){}
	if (hexa_binario(conjunto.carta[k].nbr) == hexa_binario(conjunto.carta[c].nbr)+(k-c))
	{
		return 1;
	}else
	{
		return 2;
	}
}

int checar(t_tabuleiro_ptr conjunto){
	int conjunto_cartas;
	int coringas;
	int flag;
	int valida; //verifica se a jogada é valida
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
		tipo = checar_tipo((*conjunto));
		if (tipo == 1)
		{
			valida = checa_sequencia((*conjunto), coringas)
			if (!valida)
			{
				return 0;
			}
		}else if (tipo == 2)
		{
			valida =
			if (!valida)
			{
				return 0;
			}
		}
		conjunto = conjunto->next;
	}
	return 1;
}