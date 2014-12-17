#include <stdio.h>
#include <stdlib.h>
#include "energia.h"

// devolve um inteiro 'aleatorio' em [Lower , Upper)
int Random(int Lower,int Upper){return(Lower +  (int) (Upper - Lower)*drand48());}

void ImprimeEntrada(int m, int n, int E[M], int U[N][M], double V[N], int C[N], int A[N]){
  // IMPRESSAO DA SAIDA
  printf("%d %d\n         ",m,n); // imprime numeros de: periodos  e usuarios
  // imprime a energia total disponivem em cada periodo
  for(int j = 0; j < m; j++) printf("%3d ",E[j]);
  printf("\n");
  for(int i=0;i<n; i++) {
    // imprime o valor ofertado pelo usuario i e sua classe, seguido pela
    printf("%3.0f  %2d  ",V[i],C[i]);
    // impressao da energia que o usuario i precisa em cada periodo
    for(int j=0; j<m;j++)  printf("%3d ",U[i][j]); 
    printf("\n"); }
}

int main(int argc, char *argv[ ])
{
  int m; //numero de periodos
  int n; //numero de usuarios
  int c; // maior classe usada para gerar instancia
  int E[M]; // vetor de energia em cada periodo
  int U[N][M]; // Caso o usuario i seja atendido, entao ele usa toda energia necessaria
               // em cada um dos periodos. I.e., se A[i]==1 então o usuario i recebe
               // as energias U[i][0],U[i][1],...,U[i][m-1]
  double V[N]; //  Usuario i paga V[i] se for atendido (em todos os periodos)
  int C[N]; // vetor de classes
  int EU[N]; // energia total pedida pelo usuario
  // Usaremos i para percorrer usuarios e j para percorrer periodos

  if(argc != 4){
    printf("Parametros incorretos. "
	   "Use os parametros: <num_periodos> <num_usuarios> <num_classes> \n");
    return -1; }
  m=atoi(argv[1]);  n=atoi(argv[2]);  c=atoi(argv[3]);
  if ((m>M)||(n>N)||(c>NC)) {printf("Erro: Numero maximo de periodos, usuarios e classes: %d, %d, %d\n",M,N,NC);return(-1);
  }

  // aloca as energias disponiveis em cada periodo i
  for(int j=0;j<m;j++) E[j]= Random(LMIN,LMAX+1);

  // aloca a energia necessaria pelo usuario i no periodo j, caso seja atendido.
  for(int i=0; i<n;i++) {
    EU[i] = 0;
    for(int j=0;j<m;j++) {
      U[i][j]=Random(0,(int) ((double) 0.3* E[j]+1));
      EU[i] += U[i][j];
    }
  }

  // aloca os valores de lucro de cada usuario oferece a empresa 
  for(int i=0;i<n;i++) V[i]=(double) EU[i]*M +Random(10,20);

  // gera a classe aleatoriamente
  for(int i=0;i<n;i++) C[i]=Random(1,c+1); 

  // IMPRESSAO DA SAIDA
  printf("%d %d\n         ",m,n); // imprime numeros de: periodos  e usuarios
  // imprime a energia total disponivem em cada periodo
  for(int j = 0; j < m; j++) printf("%3d ",E[j]);
  printf("\n");
  for(int i=0;i<n; i++) {
    // imprime o valor ofertado pelo usuario i e sua classe, seguido pela
    printf("%3.0f  %2d  ",V[i],C[i]);
    // impressao da energia que o usuario i precisa em cada periodo
    for(int j=0; j<m;j++)  printf("%3d ",U[i][j]); 
    printf("\n");
  }
}

