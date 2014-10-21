#include<iostream>
#include<vector>
#include<stdio.h>

using namespace std;

int calculaConjuntoIndependente(vector<vector<int> > graph, int vertices){
  
  

  return 0;
}

int main (){

  int nmrDeGrafos, nmrDeVertices, nmrDeArestas, vertice, otoVertice;
  cin>>nmrDeGrafos>>nmrDeVertices>>nmrDeArestas;

  vector<vector<int> >graph(nmrDeVertices, vector<int>(nmrDeVertices,0));

  while(nmrDeGrafos--){
    for(int arestas = 0; arestas < nmrDeArestas; arestas++){
      cin>>vertice>>otoVertice;
      graph[vertice][otoVertice] = 1;
      graph[otoVertice][vertice] = 1;
    }
    for(int i = 0; i < nmrDeVertices; i++){
      for(int j = 0; j < nmrDeVertices; j++)
	cout<<graph[i][j];
      cout<<endl;
    }
    cout<<endl;
  }

  return 0;
}
