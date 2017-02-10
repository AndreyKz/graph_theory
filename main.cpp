#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g = Graph();
    g.readGraph("input.txt");

    cout << g.getHello() << endl;

	g.addEdge(2, 4, 9);

	g.writeGraph("output.txt");

    return 0;
}
