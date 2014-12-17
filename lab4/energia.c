#include <stdio.h>
#include <stdlib.h>

#include "energia.h"


void ImprimeEntrada(int m, int n, int E[M], int U[N][M], double V[N], int C[N], int A[N]){
  // IMPRESSAO DA SAIDA
  printf("Numero de periodos: %d\nNumero de usuarios %d\n",m,n); // imprime numeros de: periodos  e usuarios
  // imprime a energia total disponivem em cada periodo
  printf("Energia por periodo\n         ");
  for(int j=0;j<m;j++) printf("%3d ",E[j]);
  printf("\n");
  printf("Val. Clas. Energia_necessaria_em_cada_periodo\n");
  for(int i=0;i<n; i++) {
    // imprime o valor ofertado pelo usuario i e sua classe, seguido pela
    printf("%3.0lf  %2d  ",V[i],C[i]);
    // impressao da energia que o usuario i precisa em cada periodo
    for(int j=0; j<m;j++)  printf("%3d ",U[i][j]); 
    printf("\n"); }
}
  
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
  
double EnergiaAux(int total_periodo, int total_usuario, int *quant_energ_periodo, int energia_usuario_periodo[][M], double *lucro, int *classes, int *usuarios_atend){

  int i;
  int quant_energia_aux[total_periodo], usuarios_atend_aux[N];
  double res_com_elemento, res_sem_elemento;
  
  //Esse for foi adicionado pra conferir tds os periodos(mochilas) de uma soh vez
  for(i = 0; i < total_periodo; i++){
    //Caso nao haja usuarios disponiveis ou nao ha mais energia para vender
    if(total_usuario < 0 || quant_energ_periodo[i] <= 0)
      return 0;

    //Caso o atual usuario exija mais energia do ha disponivel para vender ou o grupo dele ja foi utilizado
    if(energia_usuario_periodo[total_usuario][i] > quant_energ_periodo[i] || usuarios_atend[total_usuario] < 0)
      return EnergiaAux(total_periodo, total_usuario-1, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend);
  
    //Ajusta alguns vetores auxiliares pq se passar por referencia vira um rolo soh
    quant_energia_aux[i] = quant_energ_periodo[i] - energia_usuario_periodo[total_usuario][i];
  }
  for(i = 0; i < N; i++){
    if(i == total_usuario)
      usuarios_atend_aux[i] = 1;
    else if(classes[i] == classes[total_usuario])
      usuarios_atend_aux[i] = -1;
    else 
      usuarios_atend_aux[i] = usuarios_atend[i];
  }

  //Verifica os dois possiveis casos
  res_com_elemento = EnergiaAux(total_periodo, total_usuario-1, quant_energia_aux, energia_usuario_periodo, lucro, classes, usuarios_atend_aux) + lucro[total_usuario];
  res_sem_elemento = EnergiaAux(total_periodo, total_usuario-1, quant_energ_periodo, energia_usuario_periodo, lucro, classes, usuarios_atend);
  
  //Retorna o maior dentre os casos e ajusta o vetor com usuarios atendidos
  if(res_com_elemento == max(res_com_elemento, res_sem_elemento)){
    for(i = 0; i < N; i++){
      if(usuarios_atend_aux[i] < 0)
	usuarios_atend_aux[i] = 0;
      usuarios_atend[i] = usuarios_atend_aux[i];
    }
    return res_com_elemento;
  }
  return res_sem_elemento;
}

double Energia(int m, int n, int E[M], int U[N][M], double V[N], int C[N], int A[N]){
	
	//ImprimeEntrada(m,n,E,U,V,C,A); // Descomente para ver a impressao da entrada que leu
	
	// Preferimos trabalhar com variaveis cujo nome era reconhecivel
  return EnergiaAux(m, n, E, U, V, C, A);
}