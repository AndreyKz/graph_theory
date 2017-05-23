#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

    Graph g = Graph();
	Graph ng;
    g.readGraph("tests/test_le_big.txt");

    cout << g.getHello() << endl;

	//g.transformToAdjMatrix();
	ng = g.getSpaningTreeBoruvka();
	g.writeGraph("output.txt");
 	ng.writeGraph("output2.txt");

	

    return 0;
}
