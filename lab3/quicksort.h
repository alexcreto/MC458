
void Quicksort1(int v[], int n);
void Quicksort2(int v[], int n);
void Quicksort3(int v[], int n);
void QuicksortH1(int v[], int n);
void QuicksortH2(int v[], int n);
void QuicksortH3(int v[], int n);

typedef unsigned int uint;
typedef void (* QS_func_t)(int[], int);

extern int g_num_comparacoes;
extern int g_num_trocas;
extern int g_T_ins_sort;
