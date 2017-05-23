#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

    Graph g = Graph();
    g.readGraph("tests/test_al_min_2.txt");

    cout << g.getHello() << endl;

	bool circleExist;
	cout << g.checkEuler(circleExist) << endl;

	

    return 0;
}
