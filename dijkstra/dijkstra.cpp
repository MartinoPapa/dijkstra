//dijkstra, il file di input contiene una matrice di adiacenza

#include "pch.h"
#include<vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <limits.h> //int max
#include <string>

using namespace std;

ifstream input("input.txt");

int VertexNum;

int **graph; //matrice di adiacenza
vector<int> dist; // array di distanze dalla sorgente
vector<bool> sureVertex; // vertici già accertati
vector<string> percorso; //memorizzazione percorso compiuto

// 
void printSolution()
{
	cout << "Vertex\tDistance" << endl;
	for (int i = 0; i < VertexNum; i++)
	{
		cout << "vertex: " << i << endl;
		cout << "distance: " << dist[i] << endl;
		cout << "path: " << percorso[i] << endl << endl; //stampa del percorso compiuto
	}
}

// trovo il vertice non accertato di distanza minima
int minDistance()
{
	int min = INT_MAX;
	int min_index;

	for (int v = 0; v < VertexNum; v++) 
		if (!sureVertex[v] && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// 
void dijkstra(int src)
{

	// inizializzo tutte le distanze a +infinito
	for (int i = 0; i < VertexNum; i++)	dist[i] = INT_MAX, sureVertex[i] = false;

	// la distanza della sorgente è ovviamente 0
	dist[src] = 0;

	// trovo il percorso più corto verso ogni vertice
	for (int count = 0; count < VertexNum - 1; count++)
	{
		// prendo il veritce non accertato con la distanza minima
		int u = minDistance();

		// il vertice ora è stato accertato
		sureVertex[u] = true;

		// aggiorno la distanza dei vertici adiacenti a quello considerato (u)
		for (int v = 0; v < VertexNum; v++)
		{
			// se il nodo non è accertato e somma tra la distanza del nodo u dalla sorgente e il valore dell'arco (se esiste) che lo collega a u è minore della distanza di v
			// allora la distanza v assume questo valore.
			//accertarsi del fatto che non siano uguali ad INT_MAX previene errori di overflow
			if (!sureVertex[v] && (graph[u][v] && dist[u] != INT_MAX) && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				percorso[v] = percorso[u] + " --> " + to_string(v); //memorizzazione del percorso compiuto
			}			
		}			
	}
}

int main()
{
	cout << "Dijkstra" << endl;
	input >> VertexNum;

	graph = new int*[VertexNum];
	for (int i = 0;i < VertexNum;i++)
		graph[i] = new int[VertexNum];

	dist.resize(VertexNum);
	sureVertex.resize(VertexNum);

		for (int i = 0; i < VertexNum; i++) 
			for (int j = 0; j < VertexNum; j++) 
				input >> graph[i][j];
	
	int origin;

	cout << "select an origin" << endl;
	cin >> origin;

	for (int i = 0; i < VertexNum; i++) 
		percorso.push_back(to_string(origin));

	dijkstra(origin);

	printSolution(); //stampa delle soluzioni

	system("PAUSE");
	return 0;
}





