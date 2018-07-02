#include <stdlib.h>
#include <stdio.h>

#include "Rummikub.h"
#define CARTA_NBR 104
#define CORINGA_NBR 2
#define START_CARDS 14
#define CORES {'!','@','#','$'}

int checa_sequencia(t_tabuleiro conjunto)
{
	int space = 0; //quantos coringas ocupam o espaço entre duas cartas.
	int coringas_antes = 0; //Conta quantos coringas antes de iniciar a sequencia
	int primeira; //a primeira posição sendo ocupada por uma carta.
	int c;

	for(c = 0; (conjunto.carta[c].nbr == '0')||(conjunto.carta[c].nbr == '*'); c++){
		if (conjunto.carta[c].nbr == '*')
		{
			coringas_antes++;
		}
	}
	primeira = c;

	if (hexa_binario(conjunto.carta[primeira].nbr) <= coringas_antes)
	{
		return 0;
	}

	for(; (conjunto.carta[c].nbr != '0') && (c<13); c++)
	{
		while(conjunto.carta[c].nbr == '*')
		{
			c++;
			space++;
			if(c >= 13)
			{
				return 1;
			}
		}
		if(conjunto.carta[c].nbr == '0')
		{
			break;
		}
		if((space+1)+hexa_binario(conjunto.carta[c-space-1].nbr) != hexa_binario(conjunto.carta[c].nbr) && c != primeira)
		{
			return 0;
		}
		space = 0;
	}
	for(; c < 13; c++)
	{
		if(conjunto.carta[c].nbr != '0')
		{
			return 0;
		}
	}
	return 1;
}

int checar_trinca_quadra(t_tabuleiro conjunto, int conjunto_cartas)
{
	int pos1; //posicao da primeira carta
	int pos2;//posicao da ultima carta
	int c;
	if(conjunto_cartas > 4)
	{
		return 0;
	}
	for (c = 0; c < 13; ++c)
	{
		if(conjunto.carta[c].nbr != '0')
		{
			pos1 = c;
			break;
		}
	}
	for ( ; c < 13; ++c)
	{
		if((c == 12)||(conjunto.carta[c+1].nbr == '0'))
		{
			pos2 = c;
			break;
		}
	}
	if(((pos2 - pos1) + 1) != conjunto_cartas)
	{
		return 0;
	}
	for (int i = pos1; i <= pos2; ++i)
	{
		for (int j = pos1; j <= pos2; ++j)
		{
			if(j != i)
			{
				if(conjunto.carta[j].nbr != '*' && conjunto.carta[i].nbr != '*')
				{
					if ((conjunto.carta[i].nbr != conjunto.carta[j].nbr)||(conjunto.carta[i].cor == conjunto.carta[j].cor))
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int checar_tipo(t_tabuleiro conjunto)
{
	int c = 0;
	int k;
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
	int flag = 0;
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
		if (conjunto_cartas == 3 && coringas == 2)
		{
			return 1;
		}
		if(!flag)
		{
			tipo = checar_tipo((*conjunto));
			if (tipo == 1)
			{
				valida = checa_sequencia((*conjunto));
				if (!valida)
				{
					return 0;
				}
			}else if (tipo == 2)
			{
				valida = checar_trinca_quadra((*conjunto), conjunto_cartas);
				if (!valida)
				{
					return 0;
				}
			}
		}
		flag = 0;
		conjunto = conjunto->next;
	}
	return 1;
}