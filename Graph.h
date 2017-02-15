#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

class Graph
{
public:
	Graph();

	// TRANSFORMERS!!!
	void transformToAdjMatrix();
	void transformLToAdjMatrix();
	void transformEToAdjMatrix();

	void transformToAdjList();
	void transformCToAdjList();
	void transformEToAdjList();

	void transformToListOfEdges();
	void transformCToListOfEdges();
	void transformLToListOfEdges();

	// read
	void readGraph(string);
	void readAdjMatrix(ifstream&);
	void readAdjList(ifstream&);
	void readListOfEdges(ifstream&);

	// write
	void writeGraph(string fileName);
	void writeAdjMatrix(ofstream&);
	void writeAdjList(ofstream&);
	void writeListOfEdges(ofstream&);

	// add
	void addEdge(int, int, int = 0);
	void addAdjMatrix(int, int, int = 0);
	void addAdjList(int, int, int = 0);
	void addListOfEdges(int, int, int = 0);

	// remove
	void removeEdge(int, int);
	void removeAdjMatrix(int, int);
	void removeAdjList(int, int);
	void removeListOfEdges(int, int);

	// change
	int changeEdge(int, int, int = 0);
	int changeAdjMatrix(int, int, int = 0);
	int changeAdjList(int, int, int = 0);
	int changeListOfEdges(int, int, int = 0);


	string getHello();

	virtual ~Graph();
protected:
private:
	char format; // представление графа

	int n, m, r, w; // обозначения ровно те же, что и в условии

	vector<vector<int> > graph; // матрица смежности

	vector<vector<int> > graph2; // список смежности (невзвешенный)
	vector<vector<pair<int, int> > > graph3; // список смежности (взвешенный)

	vector<pair<int, int> > graph4; // список ребер (невзвешенный)
	vector<tuple<int, int, int> > graph5; // список ребер (взвешенный)

};
#endif // GRAPH_H
