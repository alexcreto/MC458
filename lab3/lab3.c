#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <memory.h>
#include "quicksort.h"

int g_num_comparacoes;
int g_num_trocas;
int g_T_ins_sort;

static void print_arr(const int v[], int n) {
  for(int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
}

static void run_test_case(int v[], int n, QS_func_t qs_func) {
  int v_[n];  
  struct timeval t_s, t_e;
  
  memcpy(v_, v, sizeof(v[0]) * n);
    
  //zera variaveis globais
  g_num_comparacoes = 0;
  g_num_trocas = 0;
  g_T_ins_sort = 0;  

  //executa o algoritmo e mede o tempo
  gettimeofday(&t_s, NULL);
  qs_func(v_, n);
  gettimeofday(&t_e, NULL);  
  
  long long elapsed = (t_e.tv_sec - t_s.tv_sec) * 1000000 + (t_e.tv_usec - t_s.tv_usec);  
  printf("%llds %.3lldm %.3lldu, %d, %d, %d\n", elapsed / 1000000, (elapsed / 1000) % 1000, elapsed % 1000, g_num_comparacoes, g_num_trocas, g_T_ins_sort);
}

static void run_test_set(FILE *fp, int n_test_cases, int len_test_case, QS_func_t qs_func) {
  int v[len_test_case];
  
  for (int k = 0; k < n_test_cases; k++) {
    for(int i = 0; i < len_test_case; i++) {
      if (fscanf(fp, "%d", &v[i]) != 1) {
	fprintf(stderr, "Formato invalido");
	exit(1);
      }      
    }
    //print_arr(v, len_test_case);
    run_test_case(v, len_test_case, qs_func);
  }
}

int main (int argc, char **argv) {  
  if (argc < 2) {
    printf("Número inválido de argumentos\n");
    printf("Uso: ./lab03 arq_dados.txt\n");
    return 1;
  }
  
  QS_func_t qs_funcs[] = { Quicksort1, Quicksort2, Quicksort3,		\
			   QuicksortH1, QuicksortH2, QuicksortH3 };
  
  // roda cada algoritmo sobre todos os casos de teste contidos no arquivo
  for (uint i = 0; i < sizeof(qs_funcs)/sizeof(qs_funcs[0]); i++) {

    FILE *fp = fopen(argv[1], "r") ;
    if (!fp) {
      fprintf(stderr, "Não foi possível abrir o arquivo de dados \"%s\".\n", argv[1]);
      return 1;
    }    
    int n_test_cases = 0;
    int len_test_case = 0;
  
    if (fscanf(fp, "%d %d", &n_test_cases, &len_test_case) != 2) {
      fprintf(stderr, "Formato invalido.\n");
      return 1;
    }
    
    run_test_set(fp, n_test_cases, len_test_case, qs_funcs[i]);
    fclose(fp);
  }
  
  return 0;
}
