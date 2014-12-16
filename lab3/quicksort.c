#include "quicksort.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int lesser(int v, int w) {
  g_num_comparacoes++;
  if (v < w)
    return 1;
  else return 0;
}

//Funcao para saber onde fazer as divisorias das 4 particoes
void check(int a, int b, int *indp, int *indq, int *indr) {
  
  if(a == *indp)
    *indp = b;
  else if(b == *indp){
    *indp = a;
    g_num_comparacoes++;
  }

  if(a == *indq)
    *indq = b;
  else if(b == *indq){
    *indq = a;
    g_num_comparacoes++;
  }

  if(a == *indr)
    *indr = b;
  else if(b == *indr){
    *indr = a;
    g_num_comparacoes++;
  }

  g_num_comparacoes = g_num_comparacoes+3;
}


/***************/
/* QUICKSORT 1 */
/***************/

int partition1(int* q1, int left,int right) {

  int x= q1[left];
  int i=left;
  int j;

  for(j=left+1; j<right; j++) {
    g_num_comparacoes++;
    if(q1[j]<=x){
      i=i+1;
      g_num_trocas++;
      swap(q1[i],q1[j]);
    }
  }
  g_num_trocas++;  
  swap(q1[i],q1[left]);
  return i;
}

void quickSort1(int* q1, int left,int right) {
	
  int div;
  g_num_comparacoes++;
  if(left < right) {
    div = partition1(q1, left, right);	// Particiona
    quickSort1(q1, left, div);  		// Subarrays
    quickSort1(q1, div+1, right);
  }
}

void Quicksort1(int v[], int n) {
  quickSort1(v, 0, n);
}


/***************/
/* QUICKSORT 2 */
/***************/

void quickSort2(int* q2, int left, int right) { 
	
  g_num_comparacoes++;
  if (right <= left) return;

  g_num_trocas++;
  if (lesser(q2[right], q2[left])) swap(q2[left], q2[right]);

  int lt = left + 1, gt = right - 1;
  int i = left + 1;
  g_num_comparacoes++;
  while (i <= gt) {
    if       (lesser(q2[i], q2[left])){g_num_trocas++; swap(q2[lt++], q2[i++]);}
    else if  (lesser(q2[right], q2[i])){g_num_trocas++; swap(q2[i], q2[gt--]);}
    else i++;
  }
  g_num_trocas++;
  swap(q2[left], q2[--lt]);
  g_num_trocas++;
  swap(q2[right], q2[++gt]);

  // recursively sort three subarrays
  quickSort2(q2, left, lt-1);
  if (lesser(q2[lt], q2[gt])) quickSort2 (q2, lt+1, gt-1);
  quickSort2(q2, gt+1, right);

}

void Quicksort2(int v[], int n) {
  quickSort2((int*)v, (int)0, (int)n);
}



/***************/
/* QUICKSORT 3 */
/***************/

//Algoritimo do Paper que faz todo o o hard work
void Particiona3(int* q3, int left,int right, int *indp, int *indq, int *indr) {

  //Ponts de referencia e de swap
  int a,b,c,d;
  //Pivos escolhidos
  int p,q,r;
  
  int ip, iq, ir;
  //Bom senso nunca eh demais
  g_num_comparacoes++;
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
    g_num_comparacoes = g_num_comparacoes + 6;
  }

  g_num_comparacoes++;
  if(!(p < q && q < r)){
    quickSort1(q3, left, right);
    *indp = left;
    *indq = left+1;
    *indr = right;
    return;
  }
  //cout<<p<<" "<<q<<" "<<r<<" "<<endl;  
  g_num_trocas++;
  swap(q3[left], q3[ip]);
  check(left, ip, &ip, &iq, &ir);

  g_num_trocas++;
  swap(q3[left+1], q3[iq]);
  check(left+1, iq, &ip, &iq, &ir);

  g_num_trocas++;
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
    g_num_comparacoes++;
    while(q3[b] < q && b <= c){
      g_num_comparacoes++;
      if(q3[b] < p){
	g_num_trocas++;
	swap(q3[a],q3[b]);
	check(a,b,indp,indq,indr); //check
	a++;
      }
      b++;
    }
    g_num_comparacoes++;
    while(q3[c] > q && b<=c){
      g_num_comparacoes++;
      if(q3[c]>r){
	g_num_trocas++;
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	d--;
      }
      c--;
    }
    g_num_comparacoes++;
    if(b<=c){
      g_num_comparacoes++;
      if(q3[b]>r){
	g_num_comparacoes++;
	if(q3[c]<p){
	  g_num_trocas++;
	  swap(q3[b],q3[a]);
	  check(b,a,indp,indq,indr); //check

	  g_num_trocas++;
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  g_num_trocas++;
	  swap(q3[b],q3[c]);
	  check(b,c,indp,indq,indr); //check
	}
	g_num_trocas++;
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	b++;
	c--;
	d--;
      }
      else {
	g_num_comparacoes++;
	if(q3[c]<p){
	  g_num_trocas++;
	  swap(q3[a],q3[b]);
	  check(a,b,indp,indq,indr); //check

	  g_num_trocas++;
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  g_num_trocas++;
	  swap(q3[b],q3[c]);
	}
	b++;
	c--;
      } 
    }
    g_num_comparacoes++;
  }
  a--;
  b--;
  c++;
  d++;
  g_num_trocas++;
  swap(q3[left+1],q3[a]);
  check(left+1,a,indp,indq,indr); //check

  g_num_trocas++;
  swap(q3[a],q3[b]);
  check(a,b,indp,indq,indr); //check
  a--;

  g_num_trocas++;
  swap(q3[left],q3[a]);
  check(left,a,indp,indq,indr); //check
  
  g_num_trocas++;
  swap(q3[right],q3[d]);
  check(right,d,indp,indq,indr); //check
}

void quickSort3(int* q3, int left,int right) {

  int p = 0, q = 0, r = 0;
  g_num_comparacoes++;
  if(left < right){ 
    Particiona3(q3,left,right, &p, &q, &r);
    //cout<<p<<" "<<q<<" "<<r<<endl;
    quickSort3(q3, left, p);
    quickSort3(q3, p+1, q);
    quickSort3(q3, q+1, r);
    quickSort3(q3, r+1, right);
  }
 
}

void Quicksort3(int v[], int n) {
  quickSort3((int*)v, (int)0, (int)n-1);
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
      g_num_trocas++;
      swap(pivots[j], pivots[j - 1]);
      g_num_trocas++;
      swap(indexes[j], indexes[j - 1]);
    }
  }
	
  // Pivo passa a ser o primeiro
  g_num_trocas++;
  swap(q1[left], q1[indexes[2]]);

  for(j=left+1; j<right; j++) {
    g_num_comparacoes++;
    if(q1[j]<=x){
      i=i+1;
      g_num_trocas++;
      swap(q1[i],q1[j]);
    }
    g_num_comparacoes++;
  }
  g_num_trocas++;
  swap(q1[i],q1[left]);
  return i;
}

void quickSortH1(int* q1, int left,int right) {
	
  int len = right - left;
  g_num_comparacoes++;
  g_T_ins_sort=27;
  if (len < 27) {							// Insertion Sort
    for (int i = left + 1; i <= right; i++) {
      for (int j = i; j > left && q1[j] < q1[j - 1]; j--) {
	g_num_trocas++;
	swap(q1[j], q1[j - 1]);
	g_num_comparacoes++;
      }
      g_num_comparacoes++;
    }
    return;
  }
	
  int div;
  g_num_comparacoes++;
  if(left < right) {
    div = partition1(q1, left, right);	// Particiona
    quickSort1(q1, left, div);  		// Subarrays
    quickSort1(q1, div+1, right);
  }
}
void QuicksortH1(int v[], int n) {
  quickSortH1(v, 0, n);
}


/****************/
/* QUICKSORT H2 */
/****************/
void quickSortH2(int* q2, int left, int right) { 
	
  int len = right - left;
  g_num_comparacoes++;
  g_T_ins_sort=27;
  if (len < 27) {							// Insertion Sort
    for (int i = left + 1; i <= right; i++) {
      for (int j = i; j > left && q2[j] < q2[j - 1]; j--) {
	g_num_trocas++;
	swap(q2[j], q2[j - 1]);
	g_num_comparacoes++;
      }
      g_num_comparacoes++;
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
      g_num_trocas++;
      g_num_trocas++;
      swap(pivots[j], pivots[j - 1]);	
      swap(indexes[j], indexes[j - 1]);
      g_num_comparacoes++;
    }
    g_num_comparacoes++;
  }
	
  // Primeiro pivo passa a ser o primeiro
  g_num_trocas++;
  swap(q2[left], q2[indexes[2]]);
  // Segundo pivo passa a ser o ultimo
  g_num_trocas++;
  swap(q2[right], q2[indexes[4]]);

  g_num_comparacoes++;
  if (right <= left) return;
  g_num_comparacoes++;
  if (lesser(q2[right], q2[left])){g_num_trocas++; swap(q2[left], q2[right]);}

  int lt = left + 1, gt = right - 1;
  int i = left + 1;
  while (i <= gt) {
    if       (lesser(q2[i], q2[left])){g_num_trocas++; swap(q2[lt++], q2[i++]);}
    else if  (lesser(q2[right], q2[i])){g_num_trocas++; swap(q2[i], q2[gt--]);}
    else i++;
    g_num_comparacoes++;
  }
  g_num_trocas++;
  g_num_trocas++;
  swap(q2[left], q2[--lt]);
  swap(q2[right], q2[++gt]);

  // recursively sort three subarrays
  quickSortH2(q2, left, lt-1);
  if (lesser(q2[lt], q2[gt])) quickSort2 (q2, lt+1, gt-1);
  quickSortH2(q2, gt+1, right);

}
void QuicksortH2(int v[], int n) {
  quickSortH2((int*)v, (int)0, (int)n);
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
  g_num_comparacoes++;
  if(left >= right)
    return;

  
  //Parte Hibrida
  g_num_comparacoes++;
  g_T_ins_sort= 10;
  if(len < 10){
    for (int i = left+1; i <= right; i++){
      for (int j = i; j > left && q3[j] < q3[j - 1]; j--){
	g_num_trocas++;
	swap(q3[j], q3[j - 1]);
	g_num_comparacoes++;
      }
      g_num_comparacoes++;
    }

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
      g_num_trocas++;
      g_num_trocas++;
      swap(pivots[j], pivots[j - 1]);	
      swap(indexes[j], indexes[j - 1]);
      g_num_comparacoes++;
    }
    g_num_comparacoes++;
  }

  p = q3[indexes[1]];
  q = q3[indexes[3]];
  r = q3[indexes[5]];
  ip = indexes[1];
  iq = indexes[3];
  ir = indexes[5];
  //cout<<p<<" "<<q<<" "<<r<<endl;

  g_num_trocas++;
  swap(q3[left], q3[ip]);
  check(left, ip, &ip, &iq, &ir);

  g_num_trocas++;
  swap(q3[left+1], q3[iq]);
  check(left+1, iq, &ip, &iq, &ir);

  g_num_trocas++;
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
    g_num_comparacoes++;
    while(q3[b] < q && b <= c){
      g_num_comparacoes++;
      if(q3[b] < p){
	g_num_trocas++;
	swap(q3[a],q3[b]);
	check(a,b,indp,indq,indr); //check
	a++;
      }
      b++;
    }
    g_num_comparacoes++;
    while(q3[c] > q && b<=c){
      g_num_comparacoes++;
      if(q3[c]>r){
	g_num_trocas++;
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	d--;
      }
      c--;
    }
    g_num_comparacoes++;
    if(b<=c){
      g_num_comparacoes++;
      if(q3[b]>r){
	g_num_comparacoes++;
	if(q3[c]<p){
	  g_num_trocas++;
	  swap(q3[b],q3[a]);
	  check(b,a,indp,indq,indr); //check

	  g_num_trocas++;
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  g_num_trocas++;
	  swap(q3[b],q3[c]);
	  check(b,c,indp,indq,indr); //check
	}
	g_num_trocas++;
	swap(q3[c],q3[d]);
	check(c,d,indp,indq,indr); //check
	b++;
	c--;
	d--;
      }
      else {
	g_num_comparacoes++;
	if(q3[c]<p){
	  g_num_trocas++;
	  swap(q3[a],q3[b]);
	  check(a,b,indp,indq,indr); //check

	  g_num_trocas++;
	  swap(q3[a],q3[c]);
	  check(a,c,indp,indq,indr); //check
	  a++;
	}
	else{
	  g_num_trocas++;
	  swap(q3[b],q3[c]);
	}
	b++;
	c--;
      } 
    }
    g_num_comparacoes++;
  }
  a--;
  b--;
  c++;
  d++;
  g_num_trocas++;
  swap(q3[left+1],q3[a]);
  check(left+1,a,indp,indq,indr); //check

  g_num_trocas++;
  swap(q3[a],q3[b]);
  check(a,b,indp,indq,indr); //check
  a--;

  g_num_trocas++;
  swap(q3[left],q3[a]);
  check(left,a,indp,indq,indr); //check
  
  g_num_trocas++;
  swap(q3[right],q3[d]);
  check(right,d,indp,indq,indr); //check

}
void quickSortH3(int* q3, int left, int right) {

  int p = 0, q = 0, r = 0;
  g_num_comparacoes++;
  if(left < right){
    ParticionaH3(q3,left,right, &p, &q, &r);
    //cout<<p<<" "<<q<<" "<<r<<endl;
    quickSortH3(q3, left, p);
    quickSortH3(q3, p+1, q);
    quickSortH3(q3, q+1, r);
    quickSortH3(q3, r+1, right);
  }
 
}

void QuicksortH3(int v[], int n) {
  quickSortH3(v, 0, n-1);
}
