#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g = Graph();
    g.readGraph("input.txt");

    cout << g.getHello() << endl;

	//g.addEdge(2, 4, 9);
	//g.removeEdge(2, 1);
	//g.changeEdge(4, 2, 10);

	g.transformToAdjMatrix();

	g.writeGraph("output.txt");

    return 0;
}
