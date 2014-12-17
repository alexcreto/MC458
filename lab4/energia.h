#ifndef ENERGIADEF
#define ENERGIADEF

#define N 50 // Maior numero de usuarios
#define M 12 // Maior numero de periodos
#define NC 10 // Maior numero de classes
#define LMAX 20 // Maior capacidade de um periodo qualquer
#define LMIN  5 // Menor capacidade de um periodo qualquer
double Energia(int m, int n, int E[M], int U[N][M], double V[N], int C[N], int A[N]);
#endif
