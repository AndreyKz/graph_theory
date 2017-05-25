#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

    Graph g = Graph();
    g.readGraph("9999adjlist.txt");

    cout << g.getHello() << endl;

	bool circleExist;
	int startVertex;
	vector <int> path;
	if (startVertex = g.checkEuler(circleExist)) {
		cout << "Circle Exist " << circleExist << endl;
		cout << "Start Vertex: " << startVertex << endl;
		path = g.getEuleranTourEffective(startVertex);
	}

	/*for (int i = 0; i < path.size(); i++) {
		cout << path[i] + 1 << " ";
	}*/
	

    return 0;
}
