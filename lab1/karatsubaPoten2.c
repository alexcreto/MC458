#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 65536
#define EPS 1e-5
#define PI 3.14159265358979323846
typedef unsigned int uint;

typedef struct
{
   double r; /* real */
   double i; /* imaginário */
} complex;

uint quad_sum = 0, quad_mult = 0, kara_sum = 0, kara_mult = 0, fft_sum = 0, fft_mult = 0;

// devolve proxima potencia de 2 maior ou igual a n
static inline
uint power2(uint n){uint p=1;while(p<n)p=p<<1;return(p);}

// verifica se os polinomios A e B sao iguais testando-os em um numero qualquer
uint PolinomiosIguais(uint n,double A[],char *NA,double B[],char *NB)
{ int r=1;
  for (uint i=0;i<n;i++) if (fabs(A[i]-B[i])>EPS) {
      printf("%10s: %lf.X^%d\n",NA,A[i],i);
      printf("%10s: %lf.X^%d\n\n",NB,B[i],i);
      r=0;}
  return(r);
}

void fft(int n, complex* A, complex* C)
{
	complex w, wn, aux;
	complex* A0;
	complex* A1;
	complex* C0;
	complex* C1;
	int i, j;

	if (n == 1) 	//Base da recursão
	{
		C[0] = A[0];
		return;
	}

	wn.r = cos(2*PI/(double)n);
	wn.i = sin(2*PI/(double)n);
	fft_mult += 2;

	w.r = 1.0;
	w.i = 0.0;

	A0 = (complex*)malloc((n/2) * sizeof(complex));
	A1 = (complex*)malloc((n/2) * sizeof(complex));
	C0 = (complex*)malloc((n/2) * sizeof(complex));
	C1 = (complex*)malloc((n/2) * sizeof(complex));
	fft_mult += 4;

	for (i = 0; i < (n/2); i++)	//Pega os coeficiêntes pares e ímpares
	{
		A0[i] = A[2*i];
		A1[i] = A[2*i+1];
		fft_mult += 2;
		fft_sum++;
	}

	fft(n/2, A0, C0);		//Calcula as metades
	fft(n/2, A1, C1);

	for (j = 0; j < (n/2); j++)	//Junta os resultados parciais
	{

		aux.r = w.r * C1[j].r - w.i * C1[j].i;
		aux.i = w.r * C1[j].i + w.i * C1[j].r;
		fft_mult += 4;
		fft_sum += 2;

		C[j].r = C0[j].r + aux.r;
		C[j].i = C0[j].i + aux.i;
		fft_sum += 2;

		C[j+n/2].r = C0[j].r - aux.r;
		C[j+n/2].i = C0[j].i - aux.i;
		fft_sum += 2;

		w.r = w.r * wn.r - w.i * wn.i;
		w.i = w.r * wn.i + w.i * wn.r;
		fft_mult += 4;
		fft_sum += 2;
	}

	free(A0);
	free(A1);
	free(C0);
	free(C1);

	return;
}

// Calcula o produto dos polinomios A e B pelo metodo direto, e coloca em C
unsigned long DummyMult(uint nA, double A[],uint nB, double B[],double C[])
{ unsigned long tinicio=clock();
	for (uint j=0;j<nA+nB-1;j++) C[j] = 0.0;
	for (uint j=0;j<nA;j++) {
		for (uint k=0;k<nB;k++) {
			C[j+k] += A[j]*B[k];
			quad_mult++;
			quad_sum++;
		}
	}
  return(clock()-tinicio);
}

// Metodo de Karatsuba. Faca uma primeira versao quando n eh potencia de 2.
// A(x) = A0(x) + A1(x)*x^{n/2}  ,   B(x) = B0(x) + B1(x)*x^{n/2}
// A(x)*B(x) =   A0(x)*B0(x) +
//             [(A0(x) + A1(x))*(B0(x) + B1(x)) - A0*B0 - A1*B1] +
//               A1(x)*B1(x)*x^n
// AA(x) = A0(x) + A1(x)
// BB(x) = B0(x) + B1(x)
// CC(x) = AA(x) * BB(x)
void RecursiveKaratsuba2(uint n,double  *A,double *B,double *C)
{

  /* REMOVER A LINHA ABAIXO E COLOCAR O CODIGO PELO METODO DE KARATSUBA */
  //  DummyMult(n,A,n,B,C);
	if(n <= 32){
		for (uint j=0;j<n+n-1;j++) C[j] = 0.0;
		for (uint j=0;j<n;j++) {
			for (uint k=0;k<n;k++) {
				C[j+k] += A[j]*B[k];
				kara_mult++;
				kara_sum++;
			}
		}
    return;
  }

  double mult1[n], mult2[n], mult3[n], sum1[n/2], sum2[n/2];

  RecursiveKaratsuba2(n/2, A, B, mult1);
  RecursiveKaratsuba2(n/2, &A[n/2], &B[n/2], mult2);


  for(uint j = 0; j<n/2; j++){
    sum1[j] = A[j] + A[j+(n/2)];
    sum2[j] = B[j] + B[j+(n/2)];
	kara_sum += 2;
  }

  RecursiveKaratsuba2(n/2, sum1, sum2, mult3);

	for(uint j = 0; j < n; j++){
    	mult3[j] = mult3[j] - (mult1[j] + mult2[j]);
		kara_sum += 2;
	}

  for(uint j=0;j<n+n-1;j++)
    C[j] = 0.0;

  for(uint j = 0; j < n; j++){
    //    printf("%u\n", n);
    // printf("%lf ", mult1[j]);
    //printf("%lf ", mult2[j]);
    //printf("%lf\n\n", mult3[j]);
    C[j] += mult1[j];
    C[j+(n/2)] += mult3[j];
    C[j+n] += mult2[j];
	kara_sum += 3;
    }

  //for (uint j=0;j<n;j++) for (uint k=0;k<n;k++) C[j+k] += A[j]*B[k];

  return;
}


// devolve o tempo gasto, funciona só para n potencia de 2
unsigned long Karatsuba2(uint dA, double A[],uint dB, double B[],double C[])
{ unsigned long tinicio=clock(); uint n;
  if ((dA<=0)||(dB<=0)) return(0);
  if (dA>dB) n = power2(dA); else n = power2(dB); // n eh menor pot. de 2 >= dA e dB
  for (uint i=dA;i<n  ;i++) A[i] = 0.0; // completa com 0 posições restantes de A
  for (uint i=dB;i<n  ;i++) B[i] = 0.0; // completa com 0 posições restantes de B
  RecursiveKaratsuba2(n,A,B,C);
  return(clock()-tinicio);
}

unsigned long FFT2(uint dA, double A[],uint dB, double B[],double C[])
{ unsigned long tinicio=clock(); uint n;
  if ((dA<=0)||(dB<=0)) return(0);
  if (dA>dB) n = power2(dA); else n = power2(dB); // n eh menor pot. de 2 >= dA e dB
  for (uint i=dA;i<n  ;i++) A[i] = 0.0; // completa com 0 posições restantes de A
  for (uint i=dB;i<n  ;i++) B[i] = 0.0; // completa com 0 posições restantes de B
  complex Ac[N], Bc[N];
  for(uint i=0; i<N; i++){
      Ac[i].r = A[i];
      Bc[i].r = B[i];
  }
  fft(n,Ac,Bc);
  return(clock()-tinicio);
}

double TestaPorArquivo(char *filename)
{  uint np,dA,dB;
	double A[N],B[N],C1[N],C2[N], C3[N];
	FILE *fp;
	unsigned long tDummyMult=0,tKaratsuba2=0, tFFT=0;
	fp = fopen(filename,"r");
	if (fp==NULL){printf("Erro para abrir arquivo %s\n.\n",filename);return(0);}
	fscanf(fp,"%u",&np);
	for (uint i=0;i<np;i++){
		// le o polinomio A com dA elementos e o polinomio B com dB elementos
		fscanf(fp,"%u",&dA); for (uint j=0;j<dA;j++) fscanf(fp,"%lf",&A[j]);
		fscanf(fp,"%u",&dB); for (uint j=0;j<dB;j++) fscanf(fp,"%lf",&B[j]);
		if ((dA>N/2)||(dB>N/2)){
		  printf("Tamanho dos polinomios nao suportado. Max %d.\n",N/2);exit(0);}
		tDummyMult += DummyMult(dA,A,dB,B,C1);// resolve por met. DummyMult
		tKaratsuba2 += Karatsuba2(dA,A,dB,B,C2);  // resolve por met. Karatsuba
		tFFT += FFT2(dA,A,dB,B,C3);  // resolve por met. FFT
		if (!PolinomiosIguais(dA+dB-1,C1,"DummyMult",C2,"Karatsuba2") || !PolinomiosIguais(dA+dB-1,C1,"DummyMult",C3,"FFT2")) {
			printf("\n\nIter. %d: Polinomios sao diferentes.\n",i+1); break;}

		printf("It.%4u: Tempo Karatsuba2 = %.3lfs,   Dummy/Karatsuba2 = %5.3lf\n",
		   i+1, (double) tKaratsuba2/CLOCKS_PER_SEC,
		        (double) tDummyMult / (double) tKaratsuba2);
		printf("It.%4u: Tempo FFT = %.3lfs,   Dummy/FFT = %5.3lf\n",
		   i+1, (double) tFFT/CLOCKS_PER_SEC,
		        (double) tDummyMult / (double) tFFT);
	}

	FILE *file = fopen("ra101354_122307.log", "rw");
	fprintf(file, "quad %s %d %d %f", filename, quad_mult, quad_sum, (double)tDummyMult/CLOCKS_PER_SEC);
	fprintf(file, "kara %s %d %d %f", filename, kara_mult, kara_sum, (double)tKaratsuba2/CLOCKS_PER_SEC);
	fprintf(file, "fft %s %d %d %f", filename, fft_mult, fft_sum, (double)tFFT/CLOCKS_PER_SEC);
	fclose(file);

	fclose(fp);  // devolve a taxa de tempo entre Dummy e Karatsuba2
	return((double) tDummyMult / (double) tKaratsuba2);
}

double TestaAleatorio(uint n)
{ double A[N],B[N],C1[N],C2[N];
  unsigned long tDummyMult=0,tKaratsuba2=0;
  srand48(clock()); // gera dois polinomios aleatorios de tam. n
  for (int i=0;i<100;i++) {
    for (uint j=0;j<n;j++){
      A[j]=(double)((int)10*drand48());
      B[j]=(double)((int)10*drand48());}
    tDummyMult += DummyMult(n,A,n,B,C1);// resolve por met. DummyMult
    tKaratsuba2 += Karatsuba2(n,A,n,B,C2);  // resolve por met. Karatsuba
    if (!PolinomiosIguais(n+n-1,C1,"DummyMult",C2,"Karatsuba2")) {
      printf("\n\nIter. %d: Polinomios sao diferentes.\n",i+1);
      printf("Polinomios C1 e C2 sao diferentes.\n"); break;}

    printf("It.%4u: Dummy=%.3lfs,  Kara=%.3lfs, Dummy/Karatsuba2 = %5.3lf\n",i+1,
	   (double)tDummyMult/CLOCKS_PER_SEC,
	   (double)tKaratsuba2/CLOCKS_PER_SEC,
	   (double)tDummyMult/(double)tKaratsuba2);
  } // devolve a taxa de tempo entre Dummy e Karatsuba2
  return((double) tDummyMult / (double) tKaratsuba2);
}

int main(int argc,char **argv)
{
  uint n; double taxa;
  if ((argc>2)||(argc<1)) {printf("Numero de parametros errado");return(1);}
  if (argc==1) {
    printf("Ha' duas alternativas de uso:\n\n"
	   "                   %s <arquivo>\n\n"
	   "                   %s <tamanho_polinomios>\n\n"
	   "Na primeira, <arquivo> e' nome do arquivo onde os dados serao lidos e testados.\n"
	   "Na segunda, <tamanho_polinomios> e' o numero de coeficientes dos\n"
	   "polinomios a multiplicar (serao executados 100 testes aleatorios).\n",
	   argv[0],argv[0]);
    return(1);
  } else {
    n = atoi(argv[1]);
    if (n==0) taxa = TestaPorArquivo(argv[1]);
    else taxa = TestaAleatorio(n);}

    if (taxa<1) printf("\nMultiplicacao direta foi mais rapida, na media.\n\n");
  else printf("\nMultiplicacao por Karatsuba foi mais rapida, na media.\n\n");

  return(1);
}
