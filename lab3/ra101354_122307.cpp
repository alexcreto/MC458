#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


/***************/
/* QUICKSORT H2 */
/***************/


void quickSortH2(int q2[], int left, int right, int div) {
	
	int len = right - left;
	int pivot1, pivot2, pivot3, pivot4, pivot5;

	if (len < 27) {
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && q2[j] < q2[j - 1]; j--) {
				swap(q2[j], q2[j - 1]);
			}
		}
		return;
	}
	int third = len / div;

								// Tira as medias
	int m1 = left  + third;
	int m2 = right - third;

	if (m1 <= left) {
		m1 = left + 1;
	}
	if (m2 >= right) {
		m2 = right - 1;
	}
	if (q2[m1] < q2[m2]) {
		swap(q2[m1], q2[left]);
		swap(q2[m2], q2[right]);
	}
	else {
		swap(q2[m1], q2[right]);
		swap(q2[m2], q2[left]);
	}
	
								// Calcula os Pivos de forma aleatoria
	do {
		pivot1 = q2[rand() % (sizeof(q2)/sizeof(int))];
		pivot2 = q2[rand() % (sizeof(q2)/sizeof(int))];
		pivot3 = q2[rand() % (sizeof(q2)/sizeof(int))];
		pivot4 = q2[rand() % (sizeof(q2)/sizeof(int))];
		pivot5 = q2[rand() % (sizeof(q2)/sizeof(int))];
	} while(pivot1 != pivot2 && pivot2 !=pivot3 && pivot3 != pivot4 && pivot4 != pivot5);

	int pivots[] = {pivot1, pivot2, pivot3, pivot4, pivot5};
	
	
	
	

    cout<< endl; 
	for(int i = 0; i < sizeof(pivots)/sizeof(int); i++)
        cout<< pivots[i] <<" ";
    cout<< endl;
	
	
	
	
	
	for (int i = 1; i <= 5; i++) {
		for (int j = i; j > 0 && pivots[j] < pivots[j - 1]; j--) {
			swap(pivots[j], pivots[j - 1]);
		}
	}
	
	
	
    cout<< endl; 
    cout<< endl; 
	for(int i = 0; i < sizeof(pivots)/sizeof(int); i++)
        cout<< pivots[i] <<" ";
    cout<< endl; 
	
	
	
								// Ponteiros
	int less  = left  + 1;
	int great = right - 1;

								// Ordenacao
	for (int k = less; k <= great; k++) {
		if (q2[k] < pivots[2]) {
			swap(q2[k], q2[less++]);
		} 
		else if (q2[k] > pivots[4]) {
			while (k < great && q2[great] > pivots[4]) {
				great--;
			}
			swap(q2[k], q2[great--]);

			if (q2[k] < pivots[2]) {
				swap(q2[k], q2[less++]);
			}
		}
	}
	
								// Trocas
	int dist = great - less;

	if (dist < 13) {
	   div++;
	}
	swap(q2[less  - 1], q2[left]);
	swap(q2[great + 1], q2[right]);

								// Subarrays
	quickSortH2(q2, left,   less - 2, div);
	quickSortH2(q2, great + 2, right, div);

								// Elementos de mesmo valor
	if (dist > len - 13 && pivots[2] != pivots[4]) {
		for (int k = less; k <= great; k++) {
			if (q2[k] == pivots[2]) {
				swap(q2[k], q2[less++]);
			}
			else if (q2[k] == pivots[4]) {
				swap(q2[k], q2[great--]);

				if (q2[k] == pivots[2]) {
					swap(q2[k], q2[less++]);
				}
			}
		}
	}
	
								// Subarrays
	if (pivots[2] < pivots[4]) {
		quickSortH2(q2, less, great, div);
	}
}


/***************/
/* QUICKSORT 2 */
/***************/

void quickSort2(int q2[], int left, int right, int div) {
	
	int len = right - left;

	if (len < 27) {
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && q2[j] < q2[j - 1]; j--) {
				swap(q2[j], q2[j - 1]);
			}
		}
		return;
	}
	int third = len / div;

 								// Tira as medias
	int m1 = left  + third;
	int m2 = right - third;

	if (m1 <= left) {
		m1 = left + 1;
	}
	if (m2 >= right) {
		m2 = right - 1;
	}
	if (q2[m1] < q2[m2]) {
		swap(q2[m1], q2[left]);
		swap(q2[m2], q2[right]);
	}
	else {
		swap(q2[m1], q2[right]);
		swap(q2[m2], q2[left]);
	}
	
								// Calcula os Pivos
	int pivot1 = q2[left];
	int pivot2 = q2[right];

								// Ponteiros
	int less  = left  + 1;
	int great = right - 1;

								// Ordenacao
	for (int k = less; k <= great; k++) {
		if (q2[k] < pivot1) {
			swap(q2[k], q2[less++]);
		} 
		else if (q2[k] > pivot2) {
			while (k < great && q2[great] > pivot2) {
				great--;
			}
			swap(q2[k], q2[great--]);

			if (q2[k] < pivot1) {
				swap(q2[k], q2[less++]);
			}
		}
	}
	// swaps
	int dist = great - less;

	if (dist < 13) {
	   div++;
	}
	swap(q2[less  - 1], q2[left]);
	swap(q2[great + 1], q2[right]);

								// Subarrays
	quickSort2(q2, left,   less - 2, div);
	quickSort2(q2, great + 2, right, div);

								// Elementos de mesmo valor
	if (dist > len - 13 && pivot1 != pivot2) {
		for (int k = less; k <= great; k++) {
			if (q2[k] == pivot1) {
				swap(q2[k], q2[less++]);
			}
			else if (q2[k] == pivot2) {
				swap(q2[k], q2[great--]);

				if (q2[k] == pivot1) {
					swap(q2[k], q2[less++]);
				}
			}
		}
	}

								// Subarrays
	if (pivot1 < pivot2) {
		quickSortH2(q2, less, great, div);
	}
}


/***************/
/* QUICKSORT 1 */
/***************/

int partition1(int q1[], int p,int q) {

    int x= q1[p];
    int i=p;
    int j;

	for(j=p+1; j<q; j++) {
    
		if(q1[j]<=x){
        
            i=i+1;
            swap(q1[i],q1[j]);
        }

    }

    swap(q1[i],q1[p]);
    return i;
}

void quickSort1(int q1[], int left,int right) {
	
    int div;
	if(left < right) {
        div = partition1(q1, left, right);	// Particiona
        quickSort1(q1, left, div);  		// Subarrays
        quickSort1(q1, div+1, right);
    }
}


/***************/
/* QUICKSORT H1 */
/***************/

int partitionH1(int q1[], int p,int q) {

    int i=p;
    int j, x;
	int pivot1, pivot2, pivot3;

											// Escolha de pivos aleatoria
	do {
		pivot1 = q1[rand() % (sizeof(q1)/sizeof(int))];
		pivot2 = q1[rand() % (sizeof(q1)/sizeof(int))];
		pivot3 = q1[rand() % (sizeof(q1)/sizeof(int))];
	} while(pivot1 != pivot2 && pivot2 !=pivot3);
	
	if (pivot1 >= pivot2 && pivot2 >= pivot3)
		x = pivot2;
	else if (pivot2 >= pivot3 && pivot3 >= pivot1)
		x = pivot3;
		else
			x = pivot1;
	
	for(j=p+1; j<q; j++) {
    
		if(q1[j]<=x){
        
            i=i+1;
            swap(q1[i],q1[j]);
        }

    }

    swap(q1[i],q1[p]);
    return i;
}

void quickSortH1(int q1[], int left,int right) {
	
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
        div = partitionH1(q1, left, right);	// Particiona
        quickSortH1(q1, left, div);  		// Subarrays
        quickSortH1(q1, div+1, right);
    }
}

int main() {
		
    int left = 0;
    int right = 10;
	int div = 5;
	int myints[] = {6,10,13,5,8,3,2,25,4,11};

	
 	cout<<endl<<"======QuickSort - 1 Pivo======="<<endl;

	int q1[] = {6,10,13,5,8,3,2,25,4,11};

    for(int i = 0; i < sizeof(q1)/sizeof(int); i++)
        cout<< q1[i] <<" ";
    cout<< endl;    

    quickSort1(q1,left,right);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < sizeof(q1)/sizeof(int); i++)
        cout<< q1[i] <<" ";
    cout<< endl;   	
	
	
	
    cout<<endl<<"======QuickSort - 2 Pivos======="<<endl;
	
	int q2[] = {6,10,13,5,8,3,2,25,4,11};

    for(int i = 0; i < sizeof(q2)/sizeof(int); i++)
        cout<< q2[i] <<" ";
    cout<< endl;    

    quickSort2(q2,left, right, div);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < sizeof(q2)/sizeof(int); i++)
        cout<< q2[i] <<" ";
    cout<< endl;     	

	
	
 	cout<<endl<<"======QuickSort Hibrido - 1 Pivo======="<<endl;

	int qh1[] = {6,10,13,5,8,3,2,25,4,11};

    for(int i = 0; i < sizeof(qh1)/sizeof(int); i++)
        cout<< qh1[i] <<" ";
    cout<< endl;    

    quickSortH1(qh1,left,right);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < sizeof(qh1)/sizeof(int); i++)
        cout<< qh1[i] <<" ";
    cout<< endl; 
	
	
	
    cout<<endl<<"======QuickSort Hibrido - 2 Pivos======="<<endl;
	
	int qh2[] = {6,10,13,5,8,3,2,25,4,11};

    for(int i = 0; i < sizeof(qh2)/sizeof(int); i++)
        cout<< qh2[i] <<" ";
    cout<< endl;    

    quickSortH2(qh2,left, right, div);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < sizeof(qh2)/sizeof(int); i++)
        cout<< qh2[i] <<" ";
    cout<< endl;  
	
}
