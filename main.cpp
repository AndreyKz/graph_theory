#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

    Graph g = Graph();
	Graph ng;
    g.readGraph("tests/test_al_min.txt");

    cout << g.getHello() << endl;

	// g.transformToAdjMatrix();
	ng = g.getSpaningTreePrima();
	g.writeGraph("output.txt");
	ng.writeGraph("output2.txt");

	////g.addEdge(2, 4, 9);
	////g.removeEdge(2, 1);
	////g.changeEdge(4, 2, 10);

	////g.transformToAdjMatrix();
	////g.transformToAdjList();
	////g.transformToListOfEdges();

	//g.addEdge(1, 4);
	//g.removeEdge(2, 1);
	////g.changeEdge(4, 2, 10);

	//g.writeGraph("output.txt");

	//g.transformToAdjMatrix();
	//g.addEdge(2, 1);
	////g.changeEdge(3, 4, 6);
	//g.removeEdge(1, 3);

	//g.writeGraph("output.txt");

	//g.transformToListOfEdges();
	//g.addEdge(2, 3);
	////g.changeEdge(2, 3, 88);
	//g.removeEdge(1, 4);




	//g.writeGraph("output.txt");

    return 0;
}
