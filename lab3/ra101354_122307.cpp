#include <vector>
#include <iostream>

using namespace std;


/***************/
/* QUICKSORT H2 */
/***************/


void quickSortH2(int q2[], int left, int right, int div) {
	
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

	// "medians"
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
	// pivots
	int pivot1 = q2[left];
	int pivot2 = q2[right];	int pivot2 = q2[right];
	int pivot2 = q2[right];
	int pivot2 = q2[right];
	int pivot2 = q2[right];


	// pointers
	int less  = left  + 1;
	int great = right - 1;

	// sorting
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

	// subarrays
	quickSortH2(q2, left,   less - 2, div);
	quickSortH2(q2, great + 2, right, div);

	// equal elements
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
	// subarray
	if (pivot1 < pivot2) {
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

	// "medians"
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
	// pivots
	int pivot1 = q2[left];
	int pivot2 = q2[right];

	// pointers
	int less  = left  + 1;
	int great = right - 1;

	// sorting
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

	// subarrays
	quickSort2(q2, left,   less - 2, div);
	quickSort2(q2, great + 2, right, div);

	// equal elements
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
	// subarray
	if (pivot1 < pivot2) {
		quickSortH2(q2, less, great, div);
	}
}


/***************/
/* QUICKSORT 1 */
/***************/

int partition1(vector<int>& q1, int p,int q) {

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


/***************/
/* QUICKSORT H1 */
/***************/

void quickSortH1(vector<int>& q1, int left,int right) {
	
	int len = right - left;
	if (len < 27) {
            for (int i = left + 1; i <= right; i++) {
                for (int j = i; j > left && q1[j] < q1[j - 1]; j--) {
                    swap(q1[j], q1[j - 1]);
                }
            }
            return;
        }
	
    int div;
	if(left < right) {
        div = partition1(q1, left, right);
        quickSortH1(q1, left, div);  
        quickSortH1(q1, div+1, right);
    }
}

void quickSort1(vector<int>& q1, int left,int right) {
	
    int div;
	if(left < right) {
        div = partition1(q1, left, right);
        quickSort1(q1, left, div);  
        quickSort1(q1, div+1, right);
    }
}

int main() {
		
    int left = 0;
    int right = 10;
	int div = 5;
	int myints[] = {6,10,13,5,8,3,2,25,4,11};

	
 	cout<<endl<<"======QuickSort - 1 Pivo======="<<endl;

	std::vector<int> q1 (myints, myints + sizeof(myints) / sizeof(int) );

    for(int i = 0; i < q1.size(); i++)
        cout<< q1[i] <<" ";
    cout<< endl;    

    quickSort1(q1,left,right);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < q1.size(); i++)
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

	std::vector<int> qh1 (myints, myints + sizeof(myints) / sizeof(int) );

    for(int i = 0; i < qh1.size(); i++)
        cout<< qh1[i] <<" ";
    cout<< endl;    

    quickSortH1(qh1,left,right);

    cout<<"=======Sorted========"<<endl;
    for(int i = 0; i < qh1.size(); i++)
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
