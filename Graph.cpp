#include "Graph.h"

using namespace std;

Graph::Graph()
{
    // Тут пусто...
}

void Graph::readGraph(string fileName){
    const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
    fstream f(cstr);

    f >> format; // представление графа

    switch(format){
    case 'C': // матрица смежности
            f >> n >> w;

            int t;
            for (int i = 0; i < n; i++){
                graph.resize(n);
                for (int j = 0; j < n; j++){
                    f >> t;
                    graph[i].push_back(t);
                }
            }
            break;
    case 'L': // список смежности
            f >> n >> r >> w;

            int bi, wi;
            if (w) {
                for (int i = 0; i < n; i++){

                }
            }
            else {
                for (int i = 0; i < n; i++){

                }
            }

            break;
    case 'E': // список ребер

        break;
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
