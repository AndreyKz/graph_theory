#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Graph
{
    public:
        Graph();



        string getHello();

        virtual ~Graph();
    protected:
    private:
        char format;

        int n, m, r, w;

        vector<vector<int> > graph;
};

#endif // GRAPH_H
