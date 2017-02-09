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

        // TODO list
        void readGraph(string);
        void addEdge(int from, int to, int weight);
        void removeEdge(int from, int to);
        int changeEdge(int from, int to, int weight); // return old value of weight
        void transformToAdjList();
        void transformToAdjMatrix();
        void transformToListOfEdges();
        void writeGraph(string fileName);
        // END of TODO list

        string getHello();

        virtual ~Graph();
    protected:
    private:
        char format; // представление графа

        int n, m, r, w; // обозначения ровно те же, что и в условии

        vector<vector<int> > graph; // "хранилище" графа
};

#endif // GRAPH_H
