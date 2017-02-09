#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    Graph g = Graph();
    g.readGraph("input.txt");

    cout << g.getHello() << endl;

    return 0;
}
