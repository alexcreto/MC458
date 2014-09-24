#include <stdio.h>

void numSplitter(double a, double *high, double *low){
	int i = 0;
	double aux = a;
	*high = a;
	
	for(i = 0 ; aux>1 ; i++){
		aux = fmod(aux, 10);
	}
	i = i/2;
	while(i>0){
		*high = fmod(*high, 10);
	}
	*high = floor(*high);
	*low = a - (*high * pow(10, i));
}

void RecursiveKaratsuba2(double  *A,double *B,double *C)
{ 


	return;
}

int main(){
	double a = 1234, b = 123133, c = 786788;
	printf("num: %d\n", numSplitter((double) 1239999999994));
	RecursiveKaratsuba2(&a, &b, &c);
	return 0;
}
	