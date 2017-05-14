#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>
#include <set>
#include <stdio.h>
#include "DSU.h"

using namespace std;

class Graph
{
public:
	Graph();
	Graph(int, char);

	// TRANSFORMERS!!!
	void transformToAdjMatrix();
	void transformToAdjList();
	void transformToListOfEdges();

	// read
	void readGraph(string);

	// write
	void writeGraph(string fileName);

	// add
	void addEdge(int, int, int = 0);

	// remove
	void removeEdge(int, int);

	// change
	int changeEdge(int, int, int = 0);

	// Алгоритмы для получения минимального остовного дерева
	Graph getSpaningTreePrima();
	Graph getSpaningTreeKruscal();
	Graph getSpaningTreeBoruvka();

	string getHello();

	virtual ~Graph();
protected:
private:
	char format; // представление графа

	int n, m, r, w; // обозначения ровно те же, что и в условии

	int max_elem;   // максимальный вес ребра 

	vector <vector <pair <int, int> > > sorted_v;  // отстортированное по весу (если взвешенный)
	                                               // для каждой вершины хранится вес и конечная вершина

	vector<vector<int> >             graph;  // матрица смежности

	vector<vector<int> >             graph2; // список смежности (невзвешенный)
	vector<vector<pair<int, int> > > graph3; // список смежности (взвешенный)

	vector<pair<int, int> >          graph4; // список ребер (невзвешенный)
	vector<tuple<int, int, int> >    graph5; // список ребер (взвешенный)

	// toAdjMatrix
	void transformLToAdjMatrix();
	void transformEToAdjMatrix();

	// toAdjList
	void transformCToAdjList();
	void transformEToAdjList();

	// toListOfEdges
	void transformCToListOfEdges();
	void transformLToListOfEdges();

	// read
	void readAdjMatrix(FILE&);
	void readAdjList(FILE&);
	void readListOfEdges(FILE&);

	// write
	void writeAdjMatrix(FILE&);
	void writeAdjList(FILE&);
	void writeListOfEdges(FILE&);

	// add
	void addAdjMatrix(int, int, int = 0);
	void addAdjList(int, int, int = 0);
	void addListOfEdges(int, int, int = 0);

	// remove
	void removeAdjMatrix(int, int);
	void removeAdjList(int, int);
	void removeListOfEdges(int, int);

	// change
	int changeAdjMatrix(int, int, int = 0);
	int changeAdjList(int, int, int = 0);
	int changeListOfEdges(int, int, int = 0);

};
#endif // GRAPH_H
