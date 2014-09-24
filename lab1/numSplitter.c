#include <stdio.h>
#include <math.h>

void numSplitter(double a, double *high, double *low){
	int i = 0;
	double aux = a;
	*high = a;
	
	for(i = 0 ; aux>1 ; i++){
		aux = aux /10;
	}
	aux = i/2;
	while(aux>0){
		*high = *high / 10;
		aux--;
	}
	*high = floor(*high);
	*low = a - (*high * pow(10, i/2));
}

int main(){
	double a = 1234, b = 123133, c = 12345678901;
	double high, low;
	
	numSplitter(c, &high, &low);
	printf("c: %f, high: %f, low: %f\n", c, high, low);
	
	return 0;
}
	