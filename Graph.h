#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

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

        vector<vector<int> > graph; // матрица смежности

        vector<vector<int> > graph2; // список смежности (невзвешенный)
        vector<vector<pair<int, int> > > graph3; // список смежности (взвешенный)

        vector<vector<pair<int, int> > > graph4; // список ребер (невзвешенный)
        vector<vector<tuple<int, int, int> > > graph5; // список ребер (взвешенный)


#endif // GRAPH_H
