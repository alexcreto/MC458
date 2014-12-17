#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "energia.h"


int main(int argc, char *argv[ ])
{
  if(argc != 2){
    printf("Parametros incorretos. Use a execucao: ./lab04.c arquivo_de_dados.txt \n");  
    return -1; }

  FILE *fp = fopen(argv[1], "r") ;
  if (!fp) {
    fprintf(stderr, "Nao foi possivel abrir o arquivo de dados \"%s\".\n", argv[1]);
    return 1;}

  int m; //numero de periodos
  int n; //numero de usuarios
  double SOL; //solucao final em reais
  int E[M]; // vetor da energia disponivel em cada periodo
  int U[N][M]; // Caso o usuario i seja atendido, entao ele usa toda energia necessaria
               // em cada um dos periodos. I.e., se A[i]==1 então o usuario i recebe
               // as energias U[i][0],U[i][1],...,U[i][m-1]
  
  double V[N]; //  Usuario i paga V[i] se for atendido (em todos os periodos)
  int C[N]; // C[i] e' a classe do usuario i. Em toda solucao final, so' podera' ter
            // um usuario da mesma classe.
  int A[N];  // E' a solucao: A[i] tera' o valor 1 se atendido e 0 caso contrario.
  
  fp = fopen(argv[1],"r");
  if (fp == NULL) fprintf(stderr, "Nao foi possivel abrir o arquivo \"%s\".\n", argv[1]);
  
  fscanf(fp, "%d %d", &m, &n);  // le o numero de periodos e usuarios

  // le as energias disponiveis em cada periodo
  for(int j=0;j<m;j++) fscanf(fp,"%d",&E[j]); 

  for(int i=0;i<n;i++){
    fscanf(fp, "%lf", &V[i]);// le o valor ofertado pelo usuario i, caso atendido
    fscanf(fp, "%d", &C[i]); // le a classe do usuario i
    for(int j=0;j<m;j++)
      fscanf(fp, "%d", &U[i][j]); // le a energia necessaria pelo usuario i no periodo j
                                  // caso esteja na solucao
  }
  fclose(fp);
  
  SOL= Energia(m,n,E,U,V,C,A);
  
  printf("Ao maximizar a venda de energia, a empresa tera um lucro de %lf\n", SOL);

  printf("Os usuarios atendidos foram:\n");
  for(int i=0;i<n;i++) if(A[i]==1) printf("Usuario %d\n",i); 
  
}