#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/***************/
/* QUICKSORT 2 */
/***************/

int lesser(int v, int w) {
	if (v < w)
		return 1;
	else return 0;
    }

void quickSort2(int* q2, int left, int right) { 
	
	if (right <= left) return;

	if (lesser(q2[right], q2[left])) swap(q2[left], q2[right]);

	int lt = left + 1, gt = right - 1;
	int i = left + 1;
	while (i <= gt) {
		if       (lesser(q2[i], q2[left])) swap(q2[lt++], q2[i++]);
		else if  (lesser(q2[right], q2[i])) swap(q2[i], q2[gt--]);
			else i++;
	}
	swap(q2[left], q2[--lt]);
	swap(q2[right], q2[++gt]);

	// recursively sort three subarrays
	quickSort2(q2, left, lt-1);
	if (lesser(q2[lt], q2[gt])) quickSort2 (q2, lt+1, gt-1);
	quickSort2(q2, gt+1, right);

}


/****************/
/* QUICKSORT H2 */
/****************/
void quickSortH2(int* q2, int left, int right) { 
	
	int len = right - left;
	if (len < 27) {							// Insertion Sort
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && q2[j] < q2[j - 1]; j--) {
				swap(q2[j], q2[j - 1]);
			}
		}
		return;
	}
	
	int pivot1, pivot2, pivot3, pivot4, pivot5;
	int r1, r2, r3, r4, r5;
	
											// Garantir que os pivos sao diferentes
	do {
		r1 = rand() % right;
		r2 = rand() % right;
		r3 = rand() % right;
		r4 = rand() % right;
		r5 = rand() % right;
		pivot1 = q2[r1];
		pivot2 = q2[r2];
		pivot3 = q2[r3];
		pivot4 = q2[r4];
		pivot5 = q2[r5];
	} while(pivot1 == pivot2 || pivot2 == pivot3 || pivot3 == pivot4 || pivot4 == pivot5 || pivot5 == pivot1);

	int pivots[] = {pivot1, pivot2, pivot3, pivot4, pivot5};
	int indexes[] = {r1, r2, r3, r4, r5};
	
											// Insertion Sort nos pivos
	for (int i = 0; i < 5; i++) {
		for (int j = i; j > 0 && pivots[j] < pivots[j - 1]; j--) {
			swap(pivots[j], pivots[j - 1]);	
			swap(indexes[j], indexes[j - 1]);
		}
	}
	
											// Primeiro pivo passa a ser o primeiro
	swap(q2[left], q2[indexes[2]]);
											// Segundo pivo passa a ser o ultimo
	swap(q2[right], q2[indexes[4]]);

		
	if (right <= left) return;

	if (lesser(q2[right], q2[left])) swap(q2[left], q2[right]);

	int lt = left + 1, gt = right - 1;
	int i = left + 1;
	while (i <= gt) {
		if       (lesser(q2[i], q2[left])) swap(q2[lt++], q2[i++]);
		else if  (lesser(q2[right], q2[i])) swap(q2[i], q2[gt--]);
			else i++;
	}
	swap(q2[left], q2[--lt]);
	swap(q2[right], q2[++gt]);

	// recursively sort three subarrays
	quickSort2(q2, left, lt-1);
	if (lesser(q2[lt], q2[gt])) quickSort2 (q2, lt+1, gt-1);
	quickSort2(q2, gt+1, right);

}


/***************/
/* QUICKSORT 1 */
/***************/

int partition1(int* q1, int left,int right) {

    int x= q1[left];
    int i=left;
    int j;

	for(j=left+1; j<right; j++) {
		if(q1[j]<=x){
            i=i+1;
            swap(q1[i],q1[j]);
        }
    }

    swap(q1[i],q1[left]);
    return i;
}

void quickSort1(int* q1, int left,int right) {
	
    int div;
	if(left < right) {
        div = partition1(q1, left, right);	// Particiona
        quickSort1(q1, left, div);  		// Subarrays
        quickSort1(q1, div+1, right);
    }
}


/****************/
/* QUICKSORT H1 */
/****************/

int partitionH1(int* q1, int left,int right) {

    int x= q1[left];
    int i=left;
    int j;	
	int pivot1, pivot2, pivot3;
	int r1, r2, r3;

											// Garantir que os pivos sao diferentes
	do {
		r1 = rand() % right;
		r2 = rand() % right;
		r3 = rand() % right;
		pivot1 = q1[r1];
		pivot2 = q1[r2];
		pivot3 = q1[r3];
	} while(pivot1 == pivot2 || pivot2 == pivot3 || pivot3 == pivot1);

	int pivots[] = {pivot1, pivot2, pivot3};
	int indexes[] = {r1, r2, r3};
	
											// Insertion Sort nos pivos
	for (int i = 0; i < 3; i++) {
		for (int j = i; j > 0 && pivots[j] < pivots[j - 1]; j--) {
			swap(pivots[j], pivots[j - 1]);	
			swap(indexes[j], indexes[j - 1]);
		}
	}
	
											// Pivo passa a ser o primeiro
	swap(q1[left], q1[indexes[2]]);

	for(j=left+1; j<right; j++) {
		if(q1[j]<=x){
            i=i+1;
            swap(q1[i],q1[j]);
        }
    }

    swap(q1[i],q1[left]);
    return i;
}

void quickSortH1(int* q1, int left,int right) {
	
	int len = right - left;
	if (len < 27) {							// Insertion Sort
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && q1[j] < q1[j - 1]; j--) {
				swap(q1[j], q1[j - 1]);
			}
		}
		return;
	}
	
    int div;
	if(left < right) {
        div = partition1(q1, left, right);	// Particiona
        quickSort1(q1, left, div);  		// Subarrays
        quickSort1(q1, div+1, right);
    }
}

/********/
/* Main */
/********/

int main() {
		
    int left = 0;
    int right = 10;
	int div = 5;

	


	int q1[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
    left = 0;
    right = sizeof(q1)/sizeof(int);
	div = sizeof(q1)/sizeof(int)/2; 
	
 	cout<<endl<<"======Original======="<<endl;
    for(int i = 0; i < sizeof(q1)/sizeof(int); i++)
        cout<< q1[i] <<" ";
    cout<< endl;    

    quickSort1(q1, left,right);

 	cout<<endl<<"======QuickSort - 1 Pivo======="<<endl;
    for(int i = 0; i < sizeof(q1)/sizeof(int); i++)
        cout<< q1[i] <<" ";
    cout<< endl;
	
	
	
	

	
	int q2[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
    left = 0;
    right = sizeof(q2)/sizeof(int);
	div = sizeof(q2)/sizeof(int)/2; 
	
    quickSort2(q2, left, right);

    cout<<endl<<"======QuickSort - 2 Pivos======="<<endl;
    for(int i = 0; i < sizeof(q2)/sizeof(int); i++)
        cout<< q2[i] <<" ";
    cout<< endl; 	
	
	
	
	


	int qh1[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
    left = 0;
    right = sizeof(qh1)/sizeof(int);
	div = sizeof(qh1)/sizeof(int)/2;   

    quickSortH1(qh1, left,right);

    cout<<endl<<"======QuickSort Hibrido - 1 Pivo======="<<endl;
    for(int i = 0; i < sizeof(qh1)/sizeof(int); i++)
        cout<< qh1[i] <<" ";
    cout<< endl; 
	
		
	
	

	
	int qh2[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
    left = 0;
    right = sizeof(qh2)/sizeof(int);
	div = sizeof(qh2)/sizeof(int)/2; 

    quickSortH2(qh2, left, right);

    cout<<endl<<"======QuickSort Hibrido - 2 Pivos======="<<endl;
    for(int i = 0; i < sizeof(qh2)/sizeof(int); i++)
        cout<< qh2[i] <<" ";
    cout<< endl;  
	
}
