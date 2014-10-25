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
	//aux = *ordem[j-1];
	//*ordem[j-1] = *ordem[j];
	//*ordem[j] = aux;
      }
      j--;
    }
  }
  return M;
}

void ajusta_ci(vector<vector<uint> > M, uint *seq_vert_ci){
  //Estou usando M.size() pq M sempre eh quadrada
  //Primeiro vou zerar todos os vertices ligados
  //a este que eu quero adicionar nas respostas
  for(uint i = 0; i < M.size(); i++){
    //tanto faz se o i eh linha ou coluna
    //a matriz eh sempre simetrica
    if(seq_vert_ci[i] == 1){
        for(uint j = 0; j < M.size(); j++){
	  //se o cara esta na resposta e esta ligado
	  //com outro da resposta desligue o outro da
	  //resposta
	  if(M[i][j])
	    seq_vert_ci[j] = 0;
	}
    }
  }
}


/* Fiz essas funcoes pq precisamos deletar vertices "aleatorios"
 * no A2, ai ficava meio complicado pra acular tds no final, pq tb
 * vamos precisar rastrear qual o grau deles.
 */
vector<vector<uint> > excluiVertice(vector<vector<uint> > M, uint vertice){
  //  M0 = M;
  M.erase(M.begin()+vertice);
  uint size = M.size();
  for(uint i = 0; i < size; i++){
    M[i].erase(M[i].begin());
  }
  return M;
}

vector<vector<uint> > excluiAdjacentes(vector<vector<uint> > M, uint vertice){
  vector<vector<uint> > M1 = M;
  uint size = M.size();
  for(uint i = 0; i < size; i++){
    if(M[i][vertice])
      M1 = excluiVertice(M,i);
  }
  M1 = excluiVertice(M,vertice);;
  return M1;
}

uint A1(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint *ordem){
  /*
   * n 			=> 	Numero de vertices
   * M 			=> 	Matriz de adjacencia
   * tam_ci 		=> 	Tamanho do Conj. Ind.
   * seq_vert_ci 	=> 	Vertices do CI
   * tempo_maximo => 	Limite de tempo, em segundos, para um algoritmo encontrar o CI
   */

  if(n <= 0) return 0;
  uint G0, G1;
  uint *proxOrdem;

  // Usando M[0][0] como nosso v:
  // M0: v nao esta na solucao	
  vector<vector<uint> >M0(n-1, vector<uint>(n-1,0));	
	
  // for(uint i = 0; i < n-1; i++){	//Pega apenas as linhas e colunas que nao sao de v
  //   for(uint j = 0; j < n-1; j++)
  //     M0[i][j] = M[i+1][j+1];
  // }
  M0 = excluiVertice(M, 0);
	
  //passa o vetor ordem como se comecasse do proximo elemento
  proxOrdem = &(ordem[1]);
  //Chamar recursao M0
  G0 = A1(n-1, M0, tam_ci, seq_vert_ci, tempo_maximo, proxOrdem);
	
	
  // M1: v esta na solucao
	
  uint adj = 0;						// Numero de vertices adjacentes a v
  for(uint i = 0; i < n; i++) if(M[i][0]) adj++;
  // M = insertion_sort(M, n, &ordem);	// Mexe na matriz de forma que 
  // // os adj se acumulam no fundo
  
  vector<vector<uint> >M1(n-1-adj, vector<uint>(n-1-adj,0));
  // for(uint i = 0; i < n-1-adj; i++){	//Pega apenas as linhas e colunas que nao sao de v e nem dos adj
  //   for(uint j = 0; j < n-1-adj; j++)
  //     M1[i][j] = M[i+1][j+1];
  // }
  M1 = excluiAdjacentes(M,0);
  //TODO jogar o v do topo de ordem em *seq_vert_ci; depois tam_ci++;
  //Chamar recursao M1
  G1 = A1(n-1-adj, M1, tam_ci, seq_vert_ci, tempo_maximo, proxOrdem);
  //pelo q eu entendi tem q comparar G0 com G1+1, mas nao tenho crtz
  if (G0 > (G1+1))return G0;
  else{
    seq_vert_ci[ordem[0]] = 1;
    return 1+G1;
  }
}

uint A2(uint n, vector<vector<uint> > M, uint *grau, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]){// A2 do enunciado
    /*
   * n 			=> 	Numero de vertices
   * M 			=> 	Matriz de adjacencia
   * grau 		=> 	Vetor com grau de cada vertice
   * seq_vert_ci 	=> 	Vertices do CI
   * tempo_maximo => 	Limite de tempo, em segundos, para um algoritmo encontrar o CI
   */

  if(n <= 0) return 0;
  uint GN, G0, G1, G3;
  uint *proxOrdem;

  // Usando M[0][0] como nosso v:
  // M0: v nao esta na solucao	
	
  // for(uint i = 0; i < n-1; i++){	//Pega apenas as linhas e colunas que nao sao de v
  //   for(uint j = 0; j < n-1; j++)
  //     M0[i][j] = M[i+1][j+1];
  // }
  vector<vector<uint> >MN(n-1, vector<uint>(n-1,0));
  MN = excluiVertice(M, 0);
  //passa o vetor ordem como se comecasse do proximo elemento
  proxOrdem = &(ordem[1]);
  //Chamar recursao M0

	
	
  // M1: v esta na solucao
	
  uint adj = 0;						// Numero de vertices adjacentes a v
  for(uint i = 0; i < n; i++) if(M[i][0]) adj++;
  // M = insertion_sort(M, n, &ordem);	// Mexe na matriz de forma que 
  // // os adj se acumulam no fundo
  

  // for(uint i = 0; i < n-1-adj; i++){	//Pega apenas as linhas e colunas que nao sao de v e nem dos adj
  //   for(uint j = 0; j < n-1-adj; j++)
  //     M1[i][j] = M[i+1][j+1];
  // }
  vector<vector<uint> >M3(n-1-adj, vector<uint>(n-1-adj,0));
  M3 = excluiAdjacentes(M,0);
  //TODO jogar o v do topo de ordem em *seq_vert_ci; depois tam_ci++;
  //Chamar recursao M1

  vector<vector<uint> >M0(n-1, vector<uint>(n-1-adj,0));
  vector<vector<uint> >M1(n-2, vector<uint>(n-1-adj,0));
  for(uint k = 0; k < n; k++){
    if(grau[k] == 0)
      G0 = A2(n-1, M0, grau, seq_vert_ci, tempo_maximo, proxOrdem);
    else if(grau[k] == 1)
      G1 = A2(n-2, M1, grau, seq_vert_ci, tempo_maximo, proxOrdem);
    else{
      GN = A2(n-1, MN, grau, seq_vert_ci, tempo_maximo, proxOrdem);
      G3 = A2(n-1-adj, M3, grau, seq_vert_ci, tempo_maximo, proxOrdem);
    }
  }
  
  if (GN > G3)return GN;
  else{
    seq_vert_ci[ordem[0]] = 1;
    return 1+G3;
  }
}
uint A3(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]);		// Algoritmo que devemos bolar que supere A1 e A2


int main (){

  int nmrDeGrafos, nmrDeVertices, nmrDeArestas, vertice, otoVertice;
  cin>>nmrDeGrafos>>nmrDeVertices>>nmrDeArestas;

  vector<vector<uint> >graph(nmrDeVertices, vector<uint>(nmrDeVertices,0));

  while(nmrDeGrafos--){
    uint ordem[nmrDeVertices], seq_vert_ci[nmrDeVertices];
	
    for(uint arestas = 0; arestas < nmrDeArestas; arestas++){
      cin>>vertice>>otoVertice;
      graph[vertice][otoVertice] = 1;
      graph[otoVertice][vertice] = 1;
    }
    for(uint i = 0; i < nmrDeVertices; i++){
      //for(uint j = 0; j < nmrDeVertices; j++){
	//cout<<graph[i][j];
	ordem[i] = i;
	seq_vert_ci[i] = 0;
	//}
      //cout<<endl;
    }
    //cout<<endl;

    cout<<A1(nmrDeVertices, graph, 0,(uint *)&seq_vert_ci,0, (uint *)&ordem)<<endl<<endl;
    ajusta_ci(graph, (uint *)&seq_vert_ci);
    for(uint i = 0; i < nmrDeVertices; i++)
      cout<<seq_vert_ci[i]<<" ";
    
    graph = vector<vector<uint> >(graph.size(),vector<uint>(graph.size(),0));
  }
  
  return 0;
}
