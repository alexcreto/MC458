#include<iostream>
#include<vector>
#include<stdio.h>

typedef unsigned int uint;

using namespace std;

vector<vector<uint> > insertion_sort(vector<vector<uint> > M, int n, uint *ordem[]) {
	uint i, j , a[n], aux;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0 && M[j - 1][0] > M[j][0]) {
			M[j].swap(M[j - 1]);
			for(uint i = 0; i < n; i++){
				a[i] = M[i][j];
				M[i][j] = M[i][j-1];
				M[i][j-1] = a[i];
				aux = *ordem[j-1];
				*ordem[j-1] = *ordem[j];
				*ordem[j] = aux;
			}

			j--;
		}
	}
	return M;
}

int calculaConjuntoIndependente(vector<vector<uint> > graph, uint vertices){
  
  

  return 0;
}

uint A1(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]){
	/*
	 * n 			=> 	Numero de vertices
	 * M 			=> 	Matriz de adjacencia
	 * tam_ci 		=> 	Tamanho do Conj. Ind.
	 * seq_vert_ci 	=> 	Vertices do CI
	 * tempo_maximo => 	Limite de tempo, em segundos, para um algoritmo encontrar o CI
	 */

	if(n <= 0) return 0;
	uint G0, G1;
	
	// Usando M[0][0] como nosso v:
	// M0: v nao esta na solucao	
	vector<vector<uint> >M0(n-1, vector<uint>(n-1,0));	
	
	for(uint i = 0; i < n-1; i++){	//Pega apenas as linhas e colunas que nao sao de v
      for(uint j = 0; j < n-1; j++)
		M0[i][j] = M[i+1][j+1];
    }
	
	//Chamar recursao M0
	G0 = A1(n-1, M0, tam_ci, seq_vert_ci, tempo_maximo, ordem);
	
	
	// M1: v esta na solucao
	
	uint adj = 0;						// Numero de vertices adjacentes a v
	for(uint i = 0; i < n; i++) if(M[i][0]) adj++;
	M = insertion_sort(M, n, &ordem);	// Mexe na matriz de forma que 
										// os adj se acumulam no fundo
	
	vector<vector<uint> >M1(n-1-adj, vector<uint>(n-1-adj,0));
	for(uint i = 0; i < n-1-adj; i++){	//Pega apenas as linhas e colunas que nao sao de v e nem dos adj
      for(uint j = 0; j < n-1-adj; j++)
		M1[i][j] = M[i+1][j+1];
    }
	
	//Chamar recursao M1
	G1 = A1(n-1-adj, M1, tam_ci, seq_vert_ci, tempo_maximo, ordem);
	
	if (G0 > G1) return G0;
	else return 1+G1;
}

uint A2(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]); 	// A2 do enunciado
uint A3(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]);	// Algoritmo que devemos bolar que supere A1 e A2


int main (){

  int nmrDeGrafos, nmrDeVertices, nmrDeArestas, vertice, otoVertice;
  cin>>nmrDeGrafos>>nmrDeVertices>>nmrDeArestas;

  vector<vector<uint> >graph(nmrDeVertices, vector<uint>(nmrDeVertices,0));

  while(nmrDeGrafos--){
	uint ordem[nmrDeVertices];
		
    for(uint arestas = 0; arestas < nmrDeArestas; arestas++){
      cin>>vertice>>otoVertice;
      graph[vertice][otoVertice] = 1;
      graph[otoVertice][vertice] = 1;
    }
    for(uint i = 0; i < nmrDeVertices; i++){
		for(uint j = 0; j < nmrDeVertices; j++){
			cout<<graph[i][j];
			ordem[i] = i;
		}
      cout<<endl;
    }
    cout<<endl;
	  
	cout<<A1(nmrDeVertices, graph, 0,0,0, ordem);
  }
  
  return 0;
}
