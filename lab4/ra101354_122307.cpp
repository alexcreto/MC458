#include<stdio.h>

#define N 5
#define M 5

/*
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   // Base Case
   if (n == 0 || W == 0)
       return 0;
 
   // If weight of the nth item is more than Knapsack capacity W, then
   // this item cannot be included in the optimal solution
   if (wt[n-1] > W)
       return knapSack(W, wt, val, n-1);
 
   // Return the maximum of two cases: (1) nth item included (2) not included
   else return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),
                    knapSack(W, wt, val, n-1)
                  );
}*/


ITALO
	Te explicar como que ta a logica dele.
	Ele recebe os paranaues e trabalha por recursao. Primeira coisa é checar se == 0.
	Se não for, ele avalia se o cliente em questão cabe na capacidade. Tem um for que avalia
	se as necessidades do cara cabem. Se não couber, ele da um break e ja pula pro proximo.
	Se o cara couber, ele forka. Avalia a soma dos lucros com e sem o cara. Eu não consegui
	fazer ele funcionar com o código de baixo. O que ainda precisa ser feito é o código
	levar em consideração as classes dos clientes.
	Para saber com qual cliente trabalhar, ele sempre pega o último cliente da lista, 
	total_usuarios-1. Portanto, na proxima chamada, ele manda um total-usuarios-1, para que 
	na proxima chamada, o codigo pegue o penultimo.
	PS: eu fiz cpp, mas o codigo ta mais c que c++. Ve aí o que voce prefere e boas.
		
	Onde ta os bugs? Eu acredito que tem a ver com a chamada do somaLucro. Não sei se ela 
	ta recebendo direito os paranaues. Eu tambem nao avaliei direito se o fluxo ta seguindo 
	o caminho correto.
		
	Boa sorte!

// Retorna o máximo dentre 2 inteiros
double max(double a, double b) { return (a > b)? a : b; }

// Retorna o lucro acumulado
double somaLucro(double lucro[N], int usuarios_atend[N]) {

	double soma = 0;
	for (int i; i<N ; i++) 
		if (usuarios_atend[i])
			soma += lucro[i];
	printf("%f\n", soma);
	return soma;
}

double Energia(int total_periodo, int total_usuario, int *quant_energ_periodo, int energia_usuario_periodo[][N], double *lucro, int *classes, int *usuarios_atend){
 
	// Caso Base
	if (total_usuario == 0)
		return 0;
	
	double soma = 0;
	int gtfo = 0; // Flag para saber se o usuário é grande demais
	
	int quant_energia_aux[M]; // Caso o usuário não supere a capacidade, esta é a capacidade restante
	for (int a; a<total_periodo; a++)
		quant_energia_aux[a] = quant_energ_periodo[a];

	int usuarios_atend_aux[M]; // Caso o usuário seja um candidato, esta a lista com ele incluso
	for (int a; a<total_usuario; a++)
		usuarios_atend_aux[a] = usuarios_atend[a];
	
	for (int periodo = 0; periodo < total_periodo; periodo++)
	{

		// Se o gasto do enésimo período for superior à capacidade, 
		// o usuário não é incluído na resposta
		if (energia_usuario_periodo[total_usuario-1][periodo] > quant_energ_periodo[periodo]) {
			gtfo = 1;
			break;
		}
		
		quant_energia_aux[periodo] -= energia_usuario_periodo[total_usuario-1][periodo];
	}
		
	if (gtfo == 0) {
		usuarios_atend_aux[total_usuario-1] = 1;
		// Pega o maior lucro entre incluir o usuário ou não
		soma = max(	somaLucro(lucro, usuarios_atend_aux) + 
						  	Energia(total_periodo, total_usuario - 1, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend), 
						  		somaLucro(lucro, usuarios_atend) + 
						 		Energia(total_periodo, total_usuario - 1, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend));
	}
	else
		soma = Energia(total_periodo, total_usuario - 1, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend);
	
 
	return soma;
}
 
int main()
{
    double lucro[N] = {60, 100, 120, 40, 20};
    int quant_energ_periodo[M] = {10, 20, 30, 20, 10};
	int energia_usuario_periodo[N][M] = {{2,3,4,5,3}, {1,1,1,1,1}, {5,4,3,4,5}, {3,3,3,3,3}, {1,3,5,3,1}};
	int classes[N] = {1,2,1,2,1};
	int usuarios_atend[N] = {0,0,0,0,0};
    printf("%f\n", Energia(5, 5, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend));
	for(int i; i<N; i++) 
		if(usuarios_atend[i])
			printf("%d ", i);
    return 0;
}