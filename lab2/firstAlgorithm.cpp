#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

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
  M.erase(M.begin()+vertice);
  uint size = M.size();
  for(uint i = 0; i < size; i++){
    M[i].erase(M[i].begin()+vertice);
  }
  return M;
}

vector<vector<uint> > excluiAdjacentes(vector<vector<uint> > M, uint vertice, vector<int> *grau){
  vector<vector<uint> > M1 = M;
  uint size = M.size();
  if(size > 1){
    for(uint i = 0; i < size; i++){
      if(M[i][vertice] >= 1 || i == vertice){
    	(*grau)[i] = -9;
    	//M1 = excluiVertice(M,i,grau);
    	//if(!grau->empty())grau->erase(grau->begin()+i);
      }
    }
    for(int i = size-1; i >= 0; i--){
      if(grau->size() == 0)
	break;
      if((*grau)[i] == -9){
	M1 = excluiVertice(M1,i);
	grau->erase(grau->begin()+i);
      }
    }
  }
  //  M1 = excluiVertice(M1,vertice);
  //grau->erase(grau->begin());
  //if(!grau->empty())grau->erase(grau->begin());
  return M1;
}


uint A1(uint n, vector<vector<uint> > M, vector<int> grau, uint *seq_vert_ci, uint tempo_maximo, uint *ordem){
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
  vector<int>modGrau = grau;
  // Usando M[0][0] como nosso v:
  // M0: v nao esta na solucao	
  vector<vector<uint> >M0(n-1, vector<uint>(n-1,0));	
  
  

  // for(uint i = 0; i < n-1; i++){	//Pega apenas as linhas e colunas que nao sao de v
  //   for(uint j = 0; j < n-1; j++)
  //     M0[i][j] = M[i+1][j+1];
  // }
  M0 = excluiVertice(M, 0);
  grau.erase(grau.begin());
	
  //passa o vetor ordem como se comecasse do proximo elemento
  proxOrdem = &(ordem[1]);
  //Chamar recursao M0
  G0 = A1(n-1, M0, grau, seq_vert_ci, tempo_maximo, proxOrdem);
	
	
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
 

  M1 = excluiAdjacentes(M,0,&modGrau);

  //TODO jogar o v do topo de ordem em *seq_vert_ci; depois tam_ci++;
  //Chamar recursao M1
  G1 = A1(n-1-adj, M1, modGrau, seq_vert_ci, tempo_maximo, proxOrdem)+1;
  //pelo q eu entendi tem q comparar G0 com G1+1, mas nao tenho crtz
  if (G0 > G1)return G0;
  else{
    seq_vert_ci[ordem[0]] = 1;
    return G1;
  }
}



uint A2(uint n, vector<vector<uint> > M, vector<int> grau, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]){// A2 do enunciado
    /*
   * n 			=> 	Numero de vertices
   * M 			=> 	Matriz de adjacencia
   * grau 		=> 	Vetor com grau de cada vertice
   * seq_vert_ci 	=> 	Vertices do CI
   * tempo_maximo => 	Limite de tempo, em segundos, para um algoritmo encontrar o CI
   */

  if(n <= 0 || grau.size() == 0) return 0;
  uint GN = 0, G0 = 0, G1 = 0, G3 = 0;
  uint MaxGN_0,MaxG1_3, Max;
  uint *proxOrdem;
  vector<int> grauN = grau, grau1 = grau, grau3 = grau, grau0 = grau;
  //passa o vetor ordem como se comecasse do proximo elemento
  proxOrdem = &(ordem[1]);

  uint adj = 0; // Numero de vertices adjacentes a v
  for(uint i = 0; i < n; i++) if(M[i][0]) adj++;

  //Cria copias pros varios possiveis grafos
 




  for(int k = n-1; k >= 0; k--){
    //caso o grau seja 0, trivialmente ele estara na resposta
    if(grau[k] == 0){
      vector<vector<uint> >M0(n-1, vector<uint>(n-1,0));
      M0 = excluiVertice(M, k);
      grau0.erase(grau0.begin()+k);
      G0 = A2(n-1, M0, grau0, seq_vert_ci, tempo_maximo, proxOrdem) + 1;
    }
    //caso grau seja 1, ele tb estara na resposta
    else if(grau[k] == 1){
      vector<vector<uint> >M1(n-2, vector<uint>(n-2,0));
      M1 = excluiAdjacentes(M, k, &grau1);
      G1 = A2(n-2, M1, grau1, seq_vert_ci, tempo_maximo, proxOrdem) + 1;
    }
    //de resto continua td igual
    else{
      vector<vector<uint> >MN(n-1, vector<uint>(n-1,0));
      MN = excluiVertice(M, k);
      grauN.erase(grauN.begin()+k);
      GN = A2(n-1, MN, grauN, seq_vert_ci, tempo_maximo, proxOrdem);
      
      vector<vector<uint> >M3(n-1-adj, vector<uint>(n-1-adj,0));
      M3 = excluiAdjacentes(M, k, &grau3);
      G3 = A2(n-1-adj, M3, grau3, seq_vert_ci, tempo_maximo, proxOrdem) + 1;
    }
  }
  
  MaxGN_0 = max(GN, G0);
  MaxG1_3 = max(G1, G3);
  Max = max(MaxG1_3, MaxGN_0);
  return Max;
}
uint A3(uint n, vector<vector<uint> > M, uint *tam_ci, uint *seq_vert_ci, uint tempo_maximo, uint ordem[]);		// Algoritmo que devemos bolar que supere A1 e A2


int main (){

  int nmrDeGrafos, nmrDeVertices, nmrDeArestas, vertice, otoVertice;
  cin>>nmrDeGrafos>>nmrDeVertices>>nmrDeArestas;

  vector<vector<uint> >graph(nmrDeVertices, vector<uint>(nmrDeVertices,0));

  while(nmrDeGrafos--){
    uint ordem[nmrDeVertices], seq_vert_ci[nmrDeVertices], seq_vert_ci2[nmrDeVertices];
    vector<int> grau(nmrDeVertices,0);

    for(uint i = 0; i < nmrDeVertices; i++){
      //for(uint j = 0; j < nmrDeVertices; j++){
      //cout<<graph[i][j];
      ordem[i] = i;
      seq_vert_ci[i] = 0;
      seq_vert_ci2[i] = 0;
      //}
      //cout<<endl;
    }	
    
    for(uint arestas = 0; arestas < nmrDeArestas; arestas++){
      cin>>vertice>>otoVertice;
      graph[vertice][otoVertice] = 1;
      graph[otoVertice][vertice] = 1;
      grau[vertice] += 1;
      grau[otoVertice] += 1;
    }
    
    //cout<<endl;

    //cout<<A1(nmrDeVertices, graph, grau,(uint *)&seq_vert_ci,0, (uint *)&ordem)<<endl<<endl;
    cout<<A2(nmrDeVertices, graph, grau,(uint *)&seq_vert_ci2,0, (uint *)&ordem)<<endl<<endl;
    ajusta_ci(graph, (uint *)&seq_vert_ci);
    for(uint i = 0; i < nmrDeVertices; i++)
      //cout<<ordem[i]<<" ";
      //cout<<seq_vert_ci[i]<<" ";
    
    graph = vector<vector<uint> >(graph.size(),vector<uint>(graph.size(),0));
  }
  
  return 0;
}
