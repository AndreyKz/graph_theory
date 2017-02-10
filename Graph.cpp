#include "Graph.h"

using namespace std;

Graph::Graph()
{
	format = n = m = r = w = 0;
}

void Graph::readAdjMatrix(ifstream & f) {
	f >> n >> w;

	int t;
	for (int i = 0; i < n; i++) {
		graph.resize(n);
		for (int j = 0; j < n; j++) {
			f >> t;
			graph[i].push_back(t);
		}
	}
}

void Graph::readAdjList(ifstream & f) {
	string str;

	f >> n >> r >> w;
	getline(f, str);

	graph2.resize(n);
	graph3.resize(n);
	for (int i = 0; i < n; i++) {
		getline(f, str);

		vector<string> arr;
		string delim(" ");
		size_t prev = 0;
		size_t next;
		size_t delta = delim.length();

		arr.clear();

		while ((next = str.find(delim, prev)) != string::npos) {
			string tmp = str.substr(prev, next - prev);

			arr.push_back(str.substr(prev, next - prev));
			prev = next + delta;
		}

		string tmp = str.substr(prev);

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
}

void Graph::readListOfEdges(ifstream & f) {
	f >> n >> m >> r >> w;

	int ai, bi, wi;
	if (w) {
		for (int i = 0; i < m; i++) {
			f >> ai >> bi >> wi;
			graph5.push_back(make_tuple(ai, bi, wi));
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			f >> ai >> bi;
			graph4.push_back(make_pair(ai, bi));
		}
	}
}

void Graph::readGraph(string fileName){
    const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
    ifstream f(cstr);

	//f.open(cstr, ios_base::in | ios_base::binary);

    f >> format; // представление графа

    switch(format){
    case 'C': // матрица смежности
		readAdjMatrix(f);
        break;
    case 'L': // список смежности
		readAdjList(f);
		break;
    case 'E': // список ребер
		readListOfEdges(f);
        break;
    }

    f.close();
}

void Graph::writeAdjMatrix(ofstream & f) {
	f << " " << n << " " << w << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			f << graph[i][j] << " ";
		}
		f << endl;
	}
}

void Graph::writeAdjList(ofstream & f) {
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
}

void Graph::writeListOfEdges(ofstream & f) {
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
}

void Graph::writeGraph(string fileName) {
	const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
	ofstream f(cstr);

	f << format;

	switch (format) {
	case 'C': 
		writeAdjMatrix(f);
		break;

	case 'L':
		writeAdjList(f);
		break;

	case 'E':
		writeListOfEdges(f);
		break;
	}
}

void Graph::addAdjMatrix(int from, int to, int weight) {
	if (graph[from][to]) {
		cout << "ERROR! The edge is already exists!";
		return;
	}

	graph[from][to] = weight;
	if (!r) {
		graph[to][from] = weight;
	}
}

void Graph::addAdjList(int from, int to, int weight) {
	if (w) {
		bool flag = false;
		for (int j = 0; j < graph3[from].size(); j++) {
			if (graph3[from][j].first == to + 1)
				flag = true;
		}
		if (!flag)
			graph3[from].push_back(make_pair(to + 1, weight));
		if (!r)
			graph3[to].push_back(make_pair(from + 1, weight));
	}
	else {
		bool flag = false;
		for (int j = 0; j < graph2[from].size(); j++) {
			if (graph2[from][j] == to + 1)
				flag = true;
		}
		if (!flag)
			graph2[from].push_back(to + 1);
		if (!r)
			graph2[to].push_back(from + 1);
	}
}

void Graph::addListOfEdges(int from, int to, int weight) {
	if (w) {
		for (int i = 0; i < m; i++) {
			if (!r) {
				if ((get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1) || (get<0>(graph5[i]) == to + 1 && get<1>(graph5[i]) == from + 1))
					return;
			}
			else {
				if (get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1)
					return;
			}
		}
		graph5.push_back(make_tuple(from + 1, to + 1, weight));
	}
	else {
		for (int i = 0; i < m; i++) {
			if (!r) {
				if ((graph4[i].first == from + 1 && graph4[i].second == to + 1) || (graph4[i].first == to + 1 && graph4[i].second == from + 1))
					return;
			}
			else {
				if (graph4[i].first == from + 1 && graph4[i].second == to + 1)
					return;
			}
		}
		graph4.push_back(make_pair(from + 1, to + 1));
	}

	m++;
}

void Graph::addEdge(int from, int to, int weight) {
	if (!w) weight = 1;

	--from;
	--to;

	switch (format) {
	case 'C':
		addAdjMatrix(from, to, weight);
		break;

	case 'L':
		addAdjList(from, to, weight);
		break;

	case 'E':
		addListOfEdges(from, to, weight);
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
