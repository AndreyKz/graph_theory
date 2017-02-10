#include "Graph.h"

using namespace std;

Graph::Graph()
{
    // Тут пусто...
}

void Graph::readGraph(string fileName){
    const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
    ifstream f(cstr);

	//f.open(cstr, ios_base::in | ios_base::binary);

    f >> format; // представление графа

	int ai, bi, wi;
	//char c;

	string str;

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
		getline(f, str);

		graph2.resize(n);
		graph3.resize(n);
		for (int i = 0; i < n; i++) {

			/*f >> c;
			if (c == '\n')
				continue;
			while (c != '\n') {
				str.push_back(c);
				f >> c;
			};*/

			getline(f, str);

			vector<string> arr;
			string delim(" ");
			size_t prev = 0;
			size_t next;
			size_t delta = delim.length();

			arr.clear();

			while ((next = str.find(delim, prev)) != string::npos) {
				//Отладка-start
				string tmp = str.substr(prev, next - prev);
				//Отладка-end
				arr.push_back(str.substr(prev, next - prev));
				prev = next + delta;
			}
			//Отладка-start
			string tmp = str.substr(prev);
			//Отладка-end
			arr.push_back(str.substr(prev));

			if (w) {
				for (int j = 0; j < arr.size(); j += 2) {
					graph3[i].push_back(make_pair(stoi(arr[j]), stoi(arr[j + 1])));
				}
			}
			else {
				for (int j = 0; j < arr.size(); j++) {
					graph2[i].push_back(stoi(arr[j]));
				}
			}
		}
		
		break;
    case 'E': // список ребер
            f >> n >> m >> r >> w;

            if (w){
                for (int i = 0; i < m; i++){
                    f >> ai >> bi >> wi;
                    graph5.push_back(make_tuple(ai, bi, wi));
                }
            }
            else {
                for (int i = 0; i < m; i++){
                    f >> ai >> bi;
                    graph4.push_back(make_pair(ai, bi));
                }
            }

            break;
    }

    f.close();
}

void Graph::writeGraph(string fileName) {
	const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
	fstream f(cstr);

	f << format;

	switch (format) {
	case 'C': 
		f << " " << n << " " << w << endl;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				f << graph[i][j] << " ";
			}
			f << endl;
		}
		break;

	case 'L':
		f << " " << n << endl << r << " " << w << endl;

		if (w) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < graph3[i].size(); j++) {
					f << graph3[i][j].first << " " << graph3[i][j].second << " ";
				}
				f << endl;
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < graph2[i].size(); j++) {
					f << graph2[i][j] << " ";
				}
				f << endl;
			}
		}
		
		break;

	case 'E':
		f << " " << n << " " << m << endl << r << " " << w << endl;

		if (w) {
			for (int i = 0; i < m; i++) {
				f << get<0>(graph5[i]) << " " << get<1>(graph5[i]) << " " << get<2>(graph5[i]) << endl;
			}
		}
		else {
			for (int i = 0; i < m; i++) {
				f << graph4[i].first << " " << graph4[i].second << endl;
			}
		}
		break;
	}
}

string Graph::getHello(){
    return "Hello World!";
}

Graph::~Graph()
{
    //dtor
}
