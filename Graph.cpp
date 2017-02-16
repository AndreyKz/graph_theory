#include "Graph.h"

using namespace std;

Graph::Graph()
{
	// самый крутой конструктор в мире
	format = n = m = w = 0;
	r = 1;
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
		/*bool flag = false;
		for (int j = 0; j < graph3[from].size(); j++) {
			if (graph3[from][j].first == to + 1)
				flag = true;
		}
		if (!flag)*/
			graph3[from].push_back(make_pair(to + 1, weight));
		if (!r)
			graph3[to].push_back(make_pair(from + 1, weight));
	}
	else {
		/*bool flag = false;
		for (int j = 0; j < graph2[from].size(); j++) {
			if (graph2[from][j] == to + 1)
				flag = true;
		}
		if (!flag)*/
			graph2[from].push_back(to + 1);
		if (!r)
			graph2[to].push_back(from + 1);
	}
}

void Graph::addListOfEdges(int from, int to, int weight) {
	if (w) {
		/*for (int i = 0; i < m; i++) {
			if (!r) {
				if ((get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1) || (get<0>(graph5[i]) == to + 1 && get<1>(graph5[i]) == from + 1))
					return;
			}
			else {
				if (get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1)
					return;
			}
		}*/
		graph5.push_back(make_tuple(from + 1, to + 1, weight));
	}
	else {
		/*for (int i = 0; i < m; i++) {
			if (!r) {
				if ((graph4[i].first == from + 1 && graph4[i].second == to + 1) || (graph4[i].first == to + 1 && graph4[i].second == from + 1))
					return;
			}
			else {
				if (graph4[i].first == from + 1 && graph4[i].second == to + 1)
					return;
			}
		}*/
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

void Graph::removeAdjMatrix(int from, int to) {
	graph[from][to] = 0;
	if (!r)
		graph[to][from] = 0;
}

void Graph::removeAdjList(int from, int to) {
	if (w) {
		for (int i = 0; i < graph3[from].size(); i++) {
			if (graph3[from][i].first == to + 1) {
				graph3[from][i].first = 0;
				graph3[from][i].second = 0;
			}
		}
		if (!r) {
			for (int i = 0; i < graph3[to].size(); i++) {
				if (graph3[to][i].first == from + 1) {
					graph3[to][i].first = 0;
					graph3[to][i].second = 0;
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < graph2[from].size(); i++) {
			if (graph2[from][i] == to + 1) {
				graph2[from][i] = 0;
				graph2[from][i] = 0;
			}
		}
		if (!r) {
			for (int i = 0; i < graph2[to].size(); i++) {
				if (graph2[to][i] == from + 1) {
					graph2[to][i] = 0;
					graph2[to][i] = 0;
					return;
				}
			}
		}
	}
}

void Graph::removeListOfEdges(int from, int to) {
	if (w) {
		for (int i = 0; i < graph5.size(); i++) {
			if (get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1) {
				get<0>(graph5[i]) = 0;
				get<1>(graph5[i]) = 0;
				get<2>(graph5[i]) = 0;
				return;
			}
			if (!r) {
				if (get<0>(graph5[i]) == to + 1 && get<1>(graph5[i]) == from + 1) {
					get<0>(graph5[i]) = 0;
					get<1>(graph5[i]) = 0;
					get<2>(graph5[i]) = 0;
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < graph4.size(); i++) {
			if (graph4[i].first == from + 1 && graph4[i].second == to + 1) {
				graph4[i].first = 0;
				graph4[i].second = 0;
				return;
			}
			if (!r) {
				if (graph4[i].first == to + 1 && graph4[i].second == from + 1) {
					graph4[i].first = 0;
					graph4[i].second = 0;
					return;
				}
			}
		}
	}
}

void Graph::removeEdge(int from, int to) {

	--from;
	--to;

	switch (format) {
	case 'C':
		removeAdjMatrix(from, to);
		break;
	case 'L':
		removeAdjList(from, to);
		break;
	case 'E':
		removeListOfEdges(from, to);
		break;
	}
}

int Graph::changeAdjMatrix(int from, int to, int weight) {
	int old_w = graph[from][to];

	if (graph[from][to]) {
		graph[from][to] = weight;
		if (!r) {
			graph[to][from] = weight;
		}
	}

	return old_w;
}

int Graph::changeAdjList(int from, int to, int weight) {
	int old_w = 0;

	if (w) {
		for (int i = 0; i < graph3[from].size(); i++) {
			if (graph3[from][i].first == to + 1) {
				old_w = graph3[from][i].second;
				graph3[from][i].second = weight;
			}
		}
		if (!r) {
			for (int i = 0; i < graph3[to].size(); i++) {
				if (graph3[to][i].first == from + 1) {
					graph3[to][i].second = weight;
				}
			}
		}
	}

	return old_w;
}

int Graph::changeListOfEdges(int from, int to, int weight) {
	int old_w = 0;

	if (w) {
		for (int i = 0; i < graph5.size(); i++) {
			if (get<0>(graph5[i]) == from + 1 && get<1>(graph5[i]) == to + 1) {
				old_w = get<2>(graph5[i]);
				get<2>(graph5[i]) = weight;
			}
			if (!r) {
				if (get<0>(graph5[i]) == to + 1 && get<1>(graph5[i]) == from + 1) {
					get<2>(graph5[i]) = weight;
				}
			}
		}
	}

	return old_w;
}

int Graph::changeEdge(int from, int to, int weight) {

	--from;
	--to;

	switch (format)
	{
	case 'C':
		return changeAdjMatrix(from, to, weight);
		break;
	case 'L':
		return changeAdjList(from, to, weight);
		break;
	case 'E':
		return changeListOfEdges(from, to, weight);
		break;
	}

	return 0;
}

void Graph::transformLToAdjMatrix() {

	if (w) {
		for (int i = 0; i < graph3.size(); i++) {
			for (int j = 0; j < graph3[i].size(); j++) {
				graph[i][graph3[i][j].first - 1] = graph3[i][j].second;
				if (!r)
					graph[graph3[i][j].first - 1][i] = graph3[i][j].second;
			}
		}
	}
	else {
		for (int i = 0; i < graph2.size(); i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				graph[i][graph2[i][j] - 1] = 1;
				if (!r)
					graph[graph2[i][j] - 1][i] = 1;
			}
		}
	}
}

void Graph::transformEToAdjMatrix() {

	if (w) {
		for (int i = 0; i < graph5.size(); i++) {
			graph[get<0>(graph5[i]) - 1][get<1>(graph5[i]) - 1] = get<2>(graph5[i]);
			if (!r)
				graph[get<1>(graph5[i]) - 1][get<0>(graph5[i]) - 1] = get<2>(graph5[i]);
		}
	}
	else {
		for (int i = 0; i < graph4.size(); i++) {
			graph[graph4[i].first - 1][graph4[i].second - 1] = 1;
			if (!r)
				graph[graph4[i].second - 1][graph4[i].first - 1] = 1;
		}
	}
}

void Graph::transformToAdjMatrix() {
	if (format == 'C') return;

	graph.clear();

	graph.resize(n);
	for (int i = 0; i < graph.size(); i++) {
		graph[i].resize(n);
		for (int j = 0; j < graph[i].size(); j++) {
			graph[i][j] = 0;
		}
	}

	switch (format) {	
	case 'L':
		transformLToAdjMatrix();
		break;
	case 'E':
		transformEToAdjMatrix();
		break;
	}

	format = 'C';
}

void Graph::transformCToAdjList() {
	if (w) {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				if (graph[i][j])
					graph3[i].push_back(make_pair(j + 1, graph[i][j]));
			}
		}
	}
	else {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				if (graph[i][j])
					graph2[i].push_back(j + 1);
			}
		}
	}
}

void Graph::transformEToAdjList() {
	if (w) {
		for (int i = 0; i < graph5.size(); i++) {
			graph3[get<0>(graph5[i]) - 1].push_back(make_pair(get<1>(graph5[i]), get<2>(graph5[i])));
		}
	}
	else {
		for (int i = 0; i < graph4.size(); i++) {
			graph2[graph4[i].first - 1].push_back(graph4[i].second);
		}
	}
}

void Graph::transformToAdjList() {
	if (format == 'L') return;

	graph2.clear();
	graph3.clear();

	if (w) {
		graph3.resize(n);
	}
	else {
		graph2.resize(n);
	}

	switch (format) {
	case 'C':
		transformCToAdjList();
		break;
	case 'E':
		transformEToAdjList();
		break;
	}

	format = 'L';
}

void Graph::transformCToListOfEdges() {
	format = 'E';
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (graph[i][j]) {
				addEdge(i + 1, j + 1, graph[i][j]);
			}
		}
	}

	/*if (w) {
		if (r) {
			for (int i = 0; i < graph.size(); i++) {
				for (int j = 0; j < graph[i].size(); j++) {
					if (graph[i][j]) {
						graph5.push_back(make_tuple(i + 1, j + 1, graph[i][j]));
						m++;
					}
				}
			}
		}
		else {
			for (int i = 0; i < graph.size(); i++) {
				for (int j = i; j < graph[i].size(); j++) {
					if (graph[i][j]) {
						graph5.push_back(make_tuple(i + 1, j + 1, graph[i][j]));
						m++;
					}
				}
			}
		}
	}
	else {
		if (r) {
			for (int i = 0; i < graph.size(); i++) {
				for (int j = 0; j < graph[i].size(); j++) {
					if (graph[i][j]) {
						graph4.push_back(make_pair(i + 1, j + 1));
						m++;
					}
				}
			}
		}
		else {
			for (int i = 0; i < graph.size(); i++) {
				for (int j = i; j < graph[i].size(); j++) {
					if (graph[i][j]) {
						graph4.push_back(make_pair(i + 1, j + 1));
						m++;
					}
				}
			}
		}
	}*/
}

void Graph::transformLToListOfEdges() {
	format = 'E';
	if (w) {
		for (int i = 0; i < graph3.size(); i++) {
			for (int j = 0; j < graph3[i].size(); j++) {
				addEdge(i + 1, graph3[i][j].first, graph3[i][j].second);
			}
		}
	}
	else {
		for (int i = 0; i < graph2.size(); i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				addEdge(i + 1, graph2[i][j]);
			}
		}
	}
	

	/*if (w) {
		for (int i = 0; i < graph3.size(); i++) {
			for (int j = 0; j < graph3[i].size(); j++) {
				graph5.push_back(make_tuple(i + 1, graph3[i][j].first, graph3[i][j].second));
				m++;
			}
		}
	}
	else {
		for (int i = 0; i < graph2.size(); i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				graph4.push_back(make_pair(i + 1, graph2[i][j]));
				m++;
			}
		}
	}*/
}

void Graph::transformToListOfEdges() {
	if (format == 'E') return;

	graph4.clear();
	graph5.clear();

	switch (format)
	{
	case 'C':
		transformCToListOfEdges();
		break;
	case 'L':
		transformLToListOfEdges();
		break;
	}

	format = 'E';
}

string Graph::getHello(){
    return "Hello World!";
}

Graph::~Graph()
{
    //dtor
}
