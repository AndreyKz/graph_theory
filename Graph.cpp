#include "Graph.h"

using namespace std;

Graph::Graph()
{
    fstream f("input.txt");

    f >> format;

    switch(format){
    case 'C':ь
            int t;
            f >> n >> w;
            for (int i = 0; i < n; i++){
                graph.resize(n);
                for (int j = 0; j < n; j++){
                    f >> t;
                    graph[i].push_back(t);
                }
            }
            break;
    case 'L':
            f >> n >> r >> w;
            for (int i = 0; i < n; i++){

            }
            break;
    case 'E': break;
    }

    f.close();
}

string Graph::getHello(){
    return "Hello World!";
}

Graph::~Graph()
{
    //dtor
}
