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
  quickSortH2(q2, left, lt-1);
  if (lesser(q2[lt], q2[gt])) quickSort2 (q2, lt+1, gt-1);
  quickSortH2(q2, gt+1, right);

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

/***************/
/* QUICKSORT 3 */
/***************/


//Funcao para saber onde fazer as divisorias das 4 particoes
void check(int a, int b, int *indp, int *indq, int *indr) {
  if(a == *indp)
    *indp = b;
  else if(b == *indp)
    *indp = a;

  if(a == *indq)
    *indq = b;
  else if(b == *indq)
    *indq = a;

  if(a == *indr)
    *indr = b;
  else if(b == *indr)
    *indr = a;
    
}

//Algoritimo do Paper que faz todo o o hard work
void Particiona3(int* q3, int left, int right, int *indp, int *indq, int *indr) {

    //Ponts de referencia e de swap
  int a,b,c,d;
  //Pivos escolhidos
  int p,q,r;
  
  int len = right-left;
  int auxp, auxq, auxr, ip, iq, ir;
  //Bom senso nunca eh demais
  if(left >= right)
    return;

  p = q3[left];
  r = q3[right];
  q = 0;
  iq = 0;
  ip = left;
  ir = right;
  for(int i = left; i <= right; i++){
    p = min(p, q3[i]);
    r = max(r, q3[i]);
    if(p == q3[i])
      ip = i;
    if(r == q3[i])
      ir = i;
    if(q3[i] > p && q3[i] < r){
      q = q3[i];
      iq = i;
      break;
    }
  }

  if(!(p < q && q < r)){
    quickSort1(q3, left, right);
    *indp = left;
    *indq = left+1;
    *indr = right;
    return;
  }
  
  //cout<<p<<" "<<q<<" "<<r<<" "<<endl;  
    
  swap(q3[left], q3[ip]);
  check(left, ip, &ip, &iq, &ir);
  swap(q3[left+1], q3[iq]);
  check(left+1, iq, &ip, &iq, &ir);
  swap(q3[right], q3[ir]);
  check(left, ip, &ip, &iq, &ir);

  *indp = left;
  *indq = left+1;
  *indr = right;

  a = left+2;
  b = left+2;
  c = right-1;
  d = right-1;

  /*Codigo do Paper, funciona q eh uma beleza*/  
  while(b <= c){
    while(q3[b] < q && b <= c){
      if(q3[b] < p){
	swap(q3[a],q3[b]);
	check(a,b,indp,indq,indr); //check
	a++;
      }
      b++;
    }
    while(q3[c] > q && b<=c){
      if(q3[c]>r){
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	d--;
      }
      c--;
    }
    if(b<=c){
      if(q3[b]>r){
	if(q3[c]<p){
	  swap(q3[b],q3[a]);
	  check(b,a,indp,indq,indr); //check
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  swap(q3[b],q3[c]);
	  check(b,c,indp,indq,indr); //check
	}
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	b++;
	c--;
	d--;
      }
      else {
	if(q3[c]<p){
	  swap(q3[a],q3[b]);
	  check(a,b,indp,indq,indr); //check
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  swap(q3[b],q3[c]);
	}
	b++;
	c--;
      } 
    }
  }
  a--;
  b--;
  c++;
  d++;
  swap(q3[left+1],q3[a]);
  check(left+1,a,indp,indq,indr); //check

  swap(q3[a],q3[b]);
  check(a,b,indp,indq,indr); //check
  a--;

  swap(q3[left],q3[a]);
  check(left,a,indp,indq,indr); //check

  swap(q3[right],q3[d]);
  check(right,d,indp,indq,indr); //check
}

void quickSort3(int* q3, int left,int right) {

  int p = 0, q = 0, r = 0;
  if(left < right){ 
    Particiona3(q3,left,right, &p, &q, &r);
    //cout<<p<<" "<<q<<" "<<r<<endl;
    quickSort3(q3, left, p);
    quickSort3(q3, p+1, q);
    quickSort3(q3, q+1, r);
    quickSort3(q3, r+1, right);
  }
 
}

/**********************/
/* QUICKSORT Hybrid 3 */
/**********************/

//Algoritimo do Paper que faz todo o o hard work
void ParticionaH3(int* q3, int left,int right, int *indp, int *indq, int *indr) {

  //Possiveis pivos
  int pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7;
  //Possiveis indices
  int r1, r2, r3, r4, r5, r6 ,r7;
  //Ponts de referencia e de swap
  int a,b,c,d;
  //Pivos escolhidos
  int p,q,r;
  
  int len = right-left;

  //Bom senso nunca eh demais
  if(left >= right)
    return;

  
  //Parte Hibrida
  if(len < 10){
    for (int i = left+1; i <= right; i++) 
      for (int j = i; j > left && q3[j] < q3[j - 1]; j--)
	swap(q3[j], q3[j - 1]);

    *indp = left;
    *indq = left+1;
    *indr = right;
    return;
  }
    
  
  //do{
    r1 = (rand() % len+1)+left;
    r2 = (rand() % len+1)+left;
    r3 = (rand() % len+1)+left;
    r4 = (rand() % len+1)+left;
    r5 = (rand() % len+1)+left;
    r6 = (rand() % len+1)+left;
    r7 = (rand() % len+1)+left;
    pivot1 = q3[r1];
    pivot2 = q3[r2];
    pivot3 = q3[r3];
    pivot4 = q3[r4];
    pivot5 = q3[r5];
    pivot6 = q3[r6];
    pivot7 = q3[r7];
    //}while(pivot1 == pivot2 || pivot2 == pivot3 || pivot3 == pivot4 || pivot4 == pivot5 || pivot5 == pivot6 || pivot6 == pivot7 || pivot7 == pivot1);

  int pivots[] = {pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7};
  int indexes[] = {r1, r2, r3, r4, r5, r6, r7};
  int ip, iq, ir;

  // Insertion Sort nos pivos
  for (int i = 0; i < 7; i++) {
    for (int j = i; j > 0 && pivots[j] < pivots[j - 1]; j--) {
      swap(pivots[j], pivots[j - 1]);	
      swap(indexes[j], indexes[j - 1]);
    }
  }

  p = q3[indexes[1]];
  q = q3[indexes[3]];
  r = q3[indexes[5]];
  ip = indexes[1];
  iq = indexes[3];
  ir = indexes[5];
  //cout<<p<<" "<<q<<" "<<r<<endl;

  swap(q3[left], q3[ip]);
  check(left, ip, &ip, &iq, &ir);
  swap(q3[left+1], q3[iq]);
  check(left+1, iq, &ip, &iq, &ir);
  swap(q3[right], q3[ir]);
  check(left, ip, &ip, &iq, &ir);

  *indp = left;
  *indq = left+1;
  *indr = right;

  a = left+2;
  b = left+2;
  c = right-1;
  d = right-1;

  /*Codigo do Paper, funciona q eh uma beleza*/

  while(b <= c){
    while(q3[b] < q && b <= c){
      if(q3[b] < p){
	swap(q3[a],q3[b]);
	check(a,b,indp,indq,indr); //check
	a++;
      }
      b++;
    }
    while(q3[c] > q && b<=c){
      if(q3[c]>r){
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	d--;
      }
      c--;
    }
    if(b<=c){
      if(q3[b]>r){
	if(q3[c]<p){
	  swap(q3[b],q3[a]);
	  check(b,a,indp,indq,indr); //check
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  swap(q3[b],q3[c]);
	  check(b,c,indp,indq,indr); //check
	}
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	b++;
	c--;
	d--;
      }
      else {
	if(q3[c]<p){
	  swap(q3[a],q3[b]);
	  check(a,b,indp,indq,indr); //check
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  swap(q3[b],q3[c]);
	}
	b++;
	c--;
      } 
    }
  }
  a--;
  b--;
  c++;
  d++;
  swap(q3[left+1],q3[a]);
  check(left+1,a,indp,indq,indr); //check

  swap(q3[a],q3[b]);
  check(a,b,indp,indq,indr); //check
  a--;

  swap(q3[left],q3[a]);
  check(left,a,indp,indq,indr); //check

  swap(q3[right],q3[d]);
  check(right,d,indp,indq,indr); //check
}
void quickSortH3(int* q3, int left,int right) {

  int p = 0, q = 0, r = 0;
  if(left < right){
    ParticionaH3(q3,left,right, &p, &q, &r);
    //cout<<p<<" "<<q<<" "<<r<<endl;
    quickSortH3(q3, left, p);
    quickSortH3(q3, p+1, q);
    quickSortH3(q3, q+1, r);
    quickSortH3(q3, r+1, right);
  }
 
}

/********/
/* Main */
/********/

int main() {
		
  int left = 0;
  int right = 10;

  srand(time(NULL));
  int input[1000];
  for(int i = 0; i < 1000; i++)
    cin>>input[i];

  int q1[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
  left = 0;
  right = sizeof(q1)/sizeof(int);
	
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
	
  quickSort2(q2, left, right);

  cout<<endl<<"======QuickSort - 2 Pivos======="<<endl;
  for(int i = 0; i < sizeof(q2)/sizeof(int); i++)
    cout<< q2[i] <<" ";
  cout<< endl; 	
	
	
	
	


  int qh1[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
  left = 0;
  right = sizeof(qh1)/sizeof(int);  

  quickSortH1(qh1, left,right);

  cout<<endl<<"======QuickSort Hibrido - 1 Pivo======="<<endl;
  for(int i = 0; i < sizeof(qh1)/sizeof(int); i++)
    cout<< qh1[i] <<" ";
  cout<< endl; 
	
		
	
	

	
  int qh2[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
  left = 0;
  right = sizeof(qh2)/sizeof(int);

  quickSortH2(qh2, left, right);

  cout<<endl<<"======QuickSort Hibrido - 2 Pivos======="<<endl;
  for(int i = 0; i < sizeof(qh2)/sizeof(int); i++)
    cout<< qh2[i] <<" ";
  cout<< endl;  




  int q3[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
  //int q3[] = {6,102,131,59,8,3,24,29,41,11,101,132,59,9,1,34,48,7,111,10,133,50,85,37,19,45,4,110,107,139,53,86,33,32,23,21,113,109,137,15,83,334,2,25,28,114,106,13,5,18,35,22,26,44,115};
  //int q3[] = {5, 13, 54, 1, 3, 10, 23, 15};
  left = 0;
  right = sizeof(input)/sizeof(int);
  cout<<right<<endl;
  quickSort3(input, left, right-1);
  cout<<endl<<"======QuickSort - 3 Pivos======="<<endl;
  for(int i = 0; i < right; i++)
    cout<< input[i] <<" ";
  cout<< endl; 


  int qh3[] = {6,10,13,5,8,3,2,29,4,11,10,13,59,8,3,34,48,4,11,10,13,5,8,3,4,45,4,11,10,13,53,8,3,32,25,4,11,10,13,15,8,3,2,25,4,11,10,13,5,18,3,22,25,44,11};
  //int q3[] = {6,102,131,59,8,3,24,29,41,11,101,132,59,9,1,34,48,7,111,10,133,50,85,37,19,45,4,110,107,139,53,86,33,32,23,21,113,109,137,15,83,334,2,25,28,114,106,13,5,18,35,22,26,44,115};
  //int q3[] = {5, 13, 54, 1, 3, 10, 23, 15};
  left = 0;
  right = sizeof(qh3)/sizeof(int);
  quickSortH3(qh3, left, right-1);
  cout<<endl<<"======QuickSort Hibrido - 3 Pivos======="<<endl;
  for(int i = 0; i < right; i++)
    cout<< qh3[i] <<" ";
  cout<< endl; 
	
  return 0;
}
