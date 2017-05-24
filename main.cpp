#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

    Graph g = Graph();
    g.readGraph("input.txt");

    cout << g.getHello() << endl;

	bool circleExist;
	if (g.checkEuler(circleExist)) {
		g.getEuleranTourFleri();
	}

	

    return 0;
}
