#include<stdio.h>
 
// Retorna o máximo dentre 2 inteiros
int max(int a, int b) { return (a > b)? a : b; }
 
// Retorna o maior lucro dentro da capacidade de energia
int maiorValor(int capacidade, int gasto[], int lucro[], int n)
{
   int i, w;
   int valor[n+1][capacidade+1];
 
   // Cria uma tabela que evita o problema de revisitar áreas já passadas
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= capacidade; w++)
       {
           if (i==0 || w==0)
               valor[i][w] = 0;
		   
		  		// Se o gasto da enésima pessoa for superior à capacidade, 
		  		// ela não é incluída na resposta
           else if (gasto[i-1] <= w)
			   
				// Pega o maior lucro entre incluir o item ou não incluir
                 valor[i][w] = max(lucro[i-1] + valor[i-1][w-gasto[i-1]],  valor[i-1][w]);
           else
                 valor[i][w] = valor[i-1][w];
       }
   }
 
   return valor[n][capacidade];
}

double Energia(int m, int n, int E[M], int U[N][M], double V[N], int C[N], int A[N]){
	
	return 0;
}
 
int main()
{
    int lucro[] = {60, 100, 120};
    int gasto[] = {10, 20, 30};
    int  capacidade = 50;
    int n = sizeof(lucro)/sizeof(lucro[0]);
    printf("%d", maiorValor(capacidade, gasto, lucro, n));
    return 0;
}