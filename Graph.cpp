#include "Graph.h"

using namespace std;

Graph::Graph()
{
	// самый крутой конструктор в мире
	format = n = m = r = w = 0;
}

Graph::Graph(int num, char form)
{
	n = num;
	m = 0;
	format = form;
	r = 0;
	w = 1;

	switch (format){
	case 'C':
		graph.resize(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				graph[i].push_back(0);
			}
		}
		break;
	case 'L':
		graph3.resize(n);
		break;
	case 'E':
		
		break;
	}
}

void Graph::readAdjMatrix(FILE & f) {
	fscanf(&f, "%d%d%d", &n, &r, &w);

	int t;
	graph.resize(n);
	sorted_v.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(&f, "%d", &t);
			graph[i].push_back(t);
			if (graph[i][j])
				m++;
		}
	}

	m /= 2;
}

void Graph::readAdjList(FILE & f) {
	const int MAX_ELEM = 200000;
	char str[MAX_ELEM];

	fscanf(&f, "%d%d%d", &n, &r, &w);
	fgets(str, MAX_ELEM, &f);

	graph2.resize(n);
	graph3.resize(n);
	for (int i = 0; i < n; i++) {
		fgets(str, MAX_ELEM, &f);

		vector<string> arr;
		
		string digit = "";
		for (int j = 0; j < MAX_ELEM; j++) {
			if (str[j] == '\0' || str[j] == '\n') {
				if (digit != "")
					arr.push_back(digit);
				break;
			}

			if (str[j] == ' ' && digit != "") {
				arr.push_back(digit);
				digit = "";
				continue;
			}

			digit += str[j];
		}

		// если в конце был пробел, убираем его
		if (arr[arr.size() - 1] == "")
			arr.pop_back();

		if (w) {
			for (int j = 0; j < arr.size(); j += 2) {
				if (stoi(arr[j])) {
					graph3[i].push_back(make_pair(stoi(arr[j]), stoi(arr[j + 1])));
					m++;
				}
			}
		}
		else {
			for (int j = 0; j < arr.size(); j++) {
				if (stoi(arr[j])) {
					graph2[i].push_back(stoi(arr[j]));
					m++;
				}
			}
		}
	}

	m /= 2;
}

void Graph::readListOfEdges(FILE & f) {
	fscanf(&f, "%d%d%d%d", &n, &m, &r, &w);

	int ai, bi, wi;
	if (w) {
		while (!feof(&f)) {
			fscanf(&f, "%d%d%d", &ai, &bi, &wi);
			graph5.push_back(make_tuple(ai, bi, wi));
		}

		// если в конце завелся дубликат
		if (graph5.size() > 1) {
			int prev_a = get<0>(graph5[graph5.size() - 2]);
			int prev_b = get<1>(graph5[graph5.size() - 2]);
			int curr_a = get<0>(graph5[graph5.size() - 1]);
			int curr_b = get<1>(graph5[graph5.size() - 1]);
			if (prev_a == curr_a && prev_b == curr_b)
				graph5.pop_back();
		}
	}
	else {
		while (!feof(&f)) {
			fscanf(&f, "%d%d", &ai, &bi);
			graph4.push_back(make_pair(ai, bi));
		}

		// если в конце завелся дубликат
		if (graph4.size() > 1) {
			int prev_a = graph4[graph4.size() - 2].first;
			int prev_b = graph4[graph4.size() - 2].second;
			int curr_a = graph4[graph4.size() - 1].first;
			int curr_b = graph4[graph4.size() - 1].second;
			if (prev_a == curr_a && prev_b == curr_b)
				graph4.pop_back();
		}
	}
}

void Graph::readGraph(string fileName){
    const char *cstr = fileName.c_str(); // хз, но string не хотел принимать

	FILE *f;
	f = fopen(cstr, "r");

	fscanf(f, "%c", &format);

    switch(format){
    case 'C': // матрица смежности
		readAdjMatrix(*f);
        break;
    case 'L': // список смежности
		readAdjList(*f);
		break;
    case 'E': // список ребер
		readListOfEdges(*f);
        break;
    }

    fclose(f);
}

void Graph::writeAdjMatrix(FILE & f) {
	fprintf(&f, " %d\n%d %d\n", n, r, w);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(&f, "%d ", graph[i][j]);
		}
		fprintf(&f, "\n");
	}
}

void Graph::writeAdjList(FILE & f) {
	fprintf(&f, " %d\n%d %d\n", n, r, w);

	if (w) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < graph3[i].size(); j++) {
				if (graph3[i][j].first && graph3[i][j].second)
					fprintf(&f, "%d %d ", graph3[i][j].first, graph3[i][j].second);
			}
			fprintf(&f, "\n");
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				if (graph2[i][j])
					fprintf(&f, "%d ", &graph2[i][j]);
			}
			fprintf(&f, "\n");
		}
	}
}

void Graph::writeListOfEdges(FILE & f) {
	fprintf(&f, " %d %d\n%d %d\n", n, m, r, w);

	if (w) {
		for (int i = 0; i < m; i++) {
			if (get<0>(graph5[i]) && get<1>(graph5[i]))
				fprintf(&f, "%d %d %d\n", get<0>(graph5[i]), get<1>(graph5[i]), get<2>(graph5[i]));
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			if (graph4[i].first && graph4[i].second)
				fprintf(&f, "%d %d\n", graph4[i].first, graph4[i].second);
		}
	}
}

void Graph::writeGraph(string fileName) {
	const char *cstr = fileName.c_str(); // хз, но string не хотел принимать
	
	FILE *f;
	f = fopen(cstr, "w");

	fprintf(f, "%c", format);

	switch (format) {
	case 'C': 
		writeAdjMatrix(*f);
		break;

	case 'L':
		writeAdjList(*f);
		break;

	case 'E':
		writeListOfEdges(*f);
		break;
	}

	fclose(f);
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

Graph Graph::getSpaningTreePrima()
{
	Graph ng = Graph(n, format);             // новый граф для возвращения

	// находим максимум в исходном графе
	int max_w = 0;
	if (format == 'C') {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j] > max_w) {
					max_w = graph[i][j];
				}
			}
		}
	}
	else if (format == 'L') {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < graph3[i].size(); j++) {
				if (graph3[i][j].second > max_w) {
					max_w = graph3[i][j].second;
				}
			}
		}
	}
	else if (format == 'E') {
		for (int i = 0; i < graph5.size(); i++) {
			if (get<2>(graph5[i]) > max_w) {
				max_w = get<2>(graph5[i]);
			}
		}
	}

	vector <bool> visited(n, false);      // посещенные вершины
	vector <int> min_e(n, max_w + 1);     // минимальные ребра
	vector <int> sel_e(n, -1);            // вершины
	set <pair<int, int> > q;
	int totalMSTSum = 0;                  // сумма всех весов MST

	if (format == 'C') {
		min_e[0] = 0;

		// основной цикл
		for (int i = 0; i < n; i++) {
			int v = -1;
			for (int j = 0; j < n; j++) {
				if (!visited[j] && (v == -1 || min_e[j] < min_e[v])) {
					v = j;
				}
			}

			visited[v] = true;
			for (int to = 0; to < n; to++) {
				if (!visited[to] && graph[v][to] != 0 && graph[v][to] < min_e[to]) {
					min_e[to] = graph[v][to];
					sel_e[to] = v;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (sel_e[i] != -1) {
				ng.addEdge(sel_e[i] + 1, i + 1, graph[sel_e[i]][i]);
				totalMSTSum += graph[sel_e[i]][i];
			}
		}
	}
	else if (format == 'L' || format == 'E') {
		if (format == 'E') {
			this->transformToAdjList();
		}

		int start = 0;
		while (start < n) {
			min_e[start] = 0;
			q.insert(make_pair(0, start));

			while (!q.empty()) {
				int v = q.begin()->second;
				q.erase(q.begin());
				visited[v] = true;

				for (size_t j = 0; j < graph3[v].size(); j++) {
					int to = graph3[v][j].first - 1,
						cost = graph3[v][j].second;
					if (!visited[to] && cost < min_e[to]) {
						q.erase(make_pair(min_e[to], to));
						min_e[to] = cost;
						sel_e[to] = v;
						q.insert(make_pair(min_e[to], to));
					}
				}
			}

			while (start < n && visited[start]) {
				start++;
			}
		}

		for (int i = 0; i < n; i++) {
			if (sel_e[i] != -1) {
				ng.addEdge(sel_e[i] + 1, i + 1, min_e[i]);
				totalMSTSum += min_e[i];
			}
		}
	}

	/*for (int i = 0; i < n; i++) {
		cout << sel_e[i] << " " << min_e[i] << " " << endl;
	}*/

	cout << "Sum: " << totalMSTSum << endl;

	return ng;
}

// сортировка по стобцу
bool sortcol(const tuple<int, int, int>& v1,
	const tuple<int, int, int>& v2) {
	return get<2>(v1) < get<2>(v2);
}

Graph Graph::getSpaningTreeKruscal()
{
	char transformedFrom = 'E';
	if (format != 'E') {
		transformedFrom = format;
		this->transformToListOfEdges();
	}

	Graph ng = Graph(n, transformedFrom);
	int cost = 0;
	vector <pair<int, int> > res;
	DSU dsu = DSU(n);

	sort(graph5.begin(), graph5.end(), sortcol);

	/*for (int i = 0; i < graph5.size(); i++) {
		cout << get<0>(graph5[i]) << " " << get<1>(graph5[i]) << " " << get<2>(graph5[i]) << endl;
	}*/

	for (int i = 0; i < m; i++) {
		int a = get<0>(graph5[i]) - 1,
			b = get<1>(graph5[i]) - 1,
			w = get<2>(graph5[i]);

		if (dsu.find(a) != dsu.find(b)) {
			cost += w;
			res.push_back(make_pair(a, b));
			dsu.unite(a, b);
			ng.addEdge(a + 1, b + 1, w);
		}
	}

	cout << cost << endl;
	cout << endl;
	/*for (int i = 0; i < res.size(); i++) {
		cout << res[i].first << " " << res[i].second << endl;
	}*/

	switch (transformedFrom) {
	case 'C':
		this->transformToAdjMatrix();
		break;
	case 'L':
		this->transformToAdjList();
		break;
	}

	return ng;
}

Graph Graph::getSpaningTreeBoruvka()
{
	Graph ng = Graph(n , format);

	DSU dsu = DSU(n);
	vector <int> minEdge(n);
	vector <int> sel_e(n);
	int cost = 0;

	int INF = 0;  // ищем максимум
	if (format == 'E') {
		for (int k = 0; k < graph5.size(); k++) {
			if (get<2>(graph5[k]) > INF)
				INF = get<2>(graph5[k]) + 1;
		}
	}
	else if (format == 'L') {
		for (int k = 0; k < graph3.size(); k++) {
			for (int j = 0; j < graph3[k].size(); j++) {
				if (graph3[k][j].second > INF)
					INF = graph3[k][j].second + 1;
			}
		}
	}
	else if (format == 'C') {
		for (int k = 0; k < graph.size(); k++) {
			for (int j = 0; j < graph[k].size(); j++) {
				if (graph[k][j] > INF)
					INF = graph[k][j] + 1;
			}
		}
	}

	// основной цикл
	int ng_m = 0;  // количество пройденных ребер
	while (ng_m < n - 1) {
		for (int i = 0; i < minEdge.size(); i++) {
			minEdge[i] = INF;
		}

		for (int i = 0; i < sel_e.size(); i++) {
			sel_e[i] = -1;
		}
		
		if (format == 'E') {
			for (int i = 0; i < graph5.size(); i++) {
				int a = dsu.find(get<0>(graph5[i]) - 1);
				int b = dsu.find(get<1>(graph5[i]) - 1);
				int w = get<2>(graph5[i]);
				if (a != b) {
					if (minEdge[a] > w) {
						minEdge[a] = w;
						sel_e[a] = b;
					}
					if (minEdge[b] > w) {
						minEdge[b] = w;
						sel_e[b] = a;
					}
				}
			}
		}
		else if (format == 'L') {
			for (int i = 0; i < graph3.size(); i++) {
				for (int j = 0; j < graph3[i].size(); j++) {
					int a = dsu.find(i);
					int b = dsu.find(graph3[i][j].first - 1);
					int w = graph3[i][j].second;
					if (a != b) {
						if (minEdge[a] > w) {
							minEdge[a] = w;
							sel_e[a] = b;
						}
						if (minEdge[b] > w) {
							minEdge[b] = w;
							sel_e[b] = a;
						}
					}
				}
			}
		}
		else if (format == 'C') {
			for (int i = 0; i < graph.size(); i++) {
				for (int j = 0; j < graph[i].size(); j++) {
					int a = dsu.find(i);
					int b = dsu.find(j);
					int w = graph[i][j];
					if (w != 0 && a != b) {
						if (minEdge[a] > w) {
							minEdge[a] = w;
							sel_e[a] = b;
						}
						if (minEdge[b] > w) {
							minEdge[b] = w;
							sel_e[b] = a;
						}
					}
				}
			}
		}

		// если больше нет ребер, то выходим
		bool noEdges = true;
		for (int i = 0; i < sel_e.size(); i++) {
			if (sel_e[i] != -1)
				noEdges = false;
		}
		if (noEdges)
			break;

		// добавляем ребра в граф
		for (int i = 0; i < minEdge.size(); i++) {
			if (minEdge[i] != INF && sel_e[i] != -1 && dsu.find(i) != dsu.find(sel_e[i])) {
				ng.addEdge(i + 1, sel_e[i] + 1, minEdge[i]);
				cost += minEdge[i];
				dsu.unite(i, sel_e[i]);
				ng_m++;
				//cout << i + 1 << " " << sel_e[i] + 1 << " " << minEdge[i] << endl;
			}
		}
	}

	cout << "MST: " << cost << endl;

	return ng;
}

int Graph::checkEuler(bool &circleExist)
{
	circleExist = false;

	vector <int> degree(n, 0); // степени вершин
	DSU dsu = DSU(n);

	if (format == 'C') {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j]) {
					degree[i]++;
					dsu.unite(i, j);
				}
			}
		}
	}
	else if (format == 'L') {
		if (!w) {
			for (int i = 0; i < graph2.size(); i++) {
				for (int j = 0; j < graph2[i].size(); j++) {
					dsu.unite(i, graph2[i][j] - 1);
					degree[i]++;
				}
			}
		}
		else {
			for (int i = 0; i < graph3.size(); i++) {
				for (int j = 0; j < graph3[i].size(); j++) {
					dsu.unite(i, graph3[i][j].first - 1);
					degree[i]++;
				}
			}
		}
	}
	else if (format == 'E') {
		if (!w) {
			for (int i = 0; i < graph4.size(); i++) {
				dsu.unite(graph4[i].first - 1, graph4[i].second - 1);
				degree[graph4[i].first - 1]++;
			}
		}
		else {
			for (int i = 0; i < graph5.size(); i++) {
				dsu.unite(get<0>(graph5[i]) - 1, get<1>(graph5[i]) - 1);
				degree[get<0>(graph5[i]) - 1]++;
			}
		}
	}

	int countOddDegree = 0;
	int startVertex = 0;
	for (int i = 0; i < degree.size(); i++) {
		if (degree[i] % 2 == 1) {
			countOddDegree++;
			startVertex = i + 1;
		}
	}

	int countCons = 0;  // количество областей связности с больше чем одной вершиной
	for (int i = 0; i < dsu.rank.size(); i++) {
		if (dsu.rank[i] > 1) {
			countCons++;
			if (!countOddDegree) {
				startVertex = i + 1;
			}
		}
	}

	if (!countOddDegree)
		circleExist = true;

	if (countOddDegree > 2 || countCons > 1) {
		return 0;
	}
	else {
		return startVertex;
	}
}

// возвращает true если дошел до вершины b
// принимает ребро (a, b) которое нужно удалить
bool Graph::bfs(int a, int b) {
	vector <bool> visited(n, false); // посещенные вершины
	queue <int> q;

	q.push(a);
	visited[a] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();

		if (format == 'C') {
			for (int i = 0; i < graph[v].size(); i++) {
				int to = i;

				if (v == a && b == to)
					continue;

				if (!visited[to] && graph[v][i]) {
					visited[to] = true;
					q.push(to);
				}
			}
		}
		else if (format == 'L') {
			if (!w) {
				for (int i = 0; i < graph2[v].size(); i++) {
					int to = graph2[v][i] - 1;

					if (v == a && b == to)
						continue;

					if (!visited[to]) {
						visited[to] = true;
						q.push(to);
					}
				}
			}
			else {
				for (int i = 0; i < graph3[v].size(); i++) {
					int to = graph3[v][i].first - 1;

					if (v == a && b == to)
						continue;

					if (!visited[to]) {
						visited[to] = true;
						q.push(to);
					}
				}
			}
		}
		else if (format == 'E') {
			// TODO
		}
	}

	/*for (int i = 0; i < visited.size(); i++) {
		cout << visited[i] << " ";
	}*/

	if (visited[b])
		return true;

	return false;
}

vector<int> Graph::getEuleranTourFleri(int start)
{
	vector <int> path;  // путь вершин
	set <pair <int, int> > visited;  // посещенные ребра

	bool transformed = false;
	if (format == 'E') {
		this->transformToAdjList();
		transformed = true;
	}

	int v = --start; // начальная вершина
	if (format == 'C') {
		while (visited.size() < m) {
			int bridge = -1;
			int old_v = v; // сохраняем
			for (int i = 0; i < graph[v].size(); i++) {
				if (v == i)
					continue;

				if (bridge == -1 && !bfs(v, i)) { // если мост
					bridge = i;
					continue;
				}

				bool visited_e = false;  // посещено ребро или нет
				if (v < i)
					visited_e = visited.find(make_pair(v, i)) != visited.end();
				else
					visited_e = visited.find(make_pair(i, v)) != visited.end();

				if (graph[v][i] && !visited_e) {  // если не посещено и есть ребро
					if (v < i)
						visited.insert(make_pair(v, i));
					else
						visited.insert(make_pair(i, v));

					path.push_back(v);

					v = i;  // теперь с этой вершины продолжаем

					continue;
				}
			}

			if (v == old_v && bridge != -1) { // никуда не ушли - идем по мосту если есть
				if (v < bridge)
					visited.insert(make_pair(v, bridge));
				else
					visited.insert(make_pair(bridge, v));

				path.push_back(v);

				v = bridge;  // теперь с этой вершины продолжаем
			}
		}
		path.push_back(v);
	}
	else if (format == 'L') {
		if (!w) {
			while (visited.size() < m) {
				int bridge = -1;
				int old_v = v; // сохраняем
				for (int i = 0; i < graph2[v].size(); i++) {
					int to = graph2[v][i] - 1;

					if (bridge == -1 && !bfs(v, to)) { // если мост
						bridge = to;
						continue;
					}

					bool visited_e = false;  // посещено ребро или нет
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) {  // если не посещено и есть ребро
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						path.push_back(v);

						v = to;  // теперь с этой вершины продолжаем

						continue;
					}
				}

				if (v == old_v && bridge != -1) { // никуда не ушли - идем по мосту если есть
					if (v < bridge)
						visited.insert(make_pair(v, bridge));
					else
						visited.insert(make_pair(bridge, v));

					path.push_back(v);

					v = bridge;  // теперь с этой вершины продолжаем
				}
			}
			path.push_back(v);
		}
		else {
			while (visited.size() < m) {
				int bridge = -1;
				int old_v = v; // сохраняем
				for (int i = 0; i < graph3[v].size(); i++) {
					int to = graph3[v][i].first - 1;

					if (bridge == -1 && !bfs(v, to)) { // если мост
						bridge = to;
						continue;
					}

					bool visited_e = false;  // посещено ребро или нет
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) {  // если не посещено и есть ребро
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						path.push_back(v);

						v = to;  // теперь с этой вершины продолжаем

						continue;
					}
				}

				if (v == old_v && bridge != -1) { // никуда не ушли - идем по мосту если есть
					if (v < bridge)
						visited.insert(make_pair(v, bridge));
					else
						visited.insert(make_pair(bridge, v));

					path.push_back(v);

					v = bridge;  // теперь с этой вершины продолжаем
				}
			}
			path.push_back(v);
		}
	}
	else if (format == 'E') {
		// TODO
	}

	if (transformed) {
		this->transformToListOfEdges();
	}


	return path;
}

vector<int> Graph::getEuleranTourEffective(int start)
{
	vector <int> path;  // путь вершин
	set <pair <int, int> > visited;  // посещенные ребра
	stack <int> q;

	bool transformed = false;
	if (format == 'E') {
		this->transformToAdjList();
		transformed = true;
	}

	q.push(start - 1);
	while (!q.empty()) {
		int v = q.top();

		if (format == 'C') {
			for (int i = 0; i < graph[v].size(); i++) {
				int to = i;
				if (v == to)
					continue;

				bool visited_e = false;  // посещено ребро или нет
				if (v < to)
					visited_e = visited.find(make_pair(v, to)) != visited.end();
				else
					visited_e = visited.find(make_pair(to, v)) != visited.end();

				if (graph[v][to] && !visited_e) {  // если не посещено и есть ребро
					if (v < to)
						visited.insert(make_pair(v, to));
					else
						visited.insert(make_pair(to, v));

					q.push(to);
					break;
				}
			}
		}
		else if (format == 'L') {
			if (!w) {
				for (int i = 0; i < graph2[v].size(); i++) {
					int to = graph2[v][i] - 1;

					bool visited_e = false;  // посещено ребро или нет
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) {  // если не посещено и есть ребро
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						q.push(to);
						break;
					}
				}
			}
			else {
				for (int i = 0; i < graph3[v].size(); i++) {
					int to = graph3[v][i].first - 1;

					bool visited_e = false;  // посещено ребро или нет
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) {  // если не посещено и есть ребро
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						q.push(to);
						break;
					}
				}
			}
		}
		else if (format == 'E') {
			// TODO
		}

		if (v == q.top()) {
			q.pop();
			path.push_back(v);
		}
	}

	if (transformed) {
		this->transformToListOfEdges();
	}

	return path;
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
				if (graph3[i][j].first) {
					graph[i][graph3[i][j].first - 1] = graph3[i][j].second;
					if (!r)
						graph[graph3[i][j].first - 1][i] = graph3[i][j].second;
				}
			}
		}
	}
	else {
		for (int i = 0; i < graph2.size(); i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				if (graph2[i][j]) {
					graph[i][graph2[i][j] - 1] = 1;
					if (!r)
						graph[graph2[i][j] - 1][i] = 1;
				}
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
		graph3.resize(n);
		for (int i = 0; i < graph5.size(); i++) {
			bool next = false;
			for (int j = 0; j < graph3[get<0>(graph5[i]) - 1].size(); j++) {
				if (graph3[get<0>(graph5[i]) - 1][j].first == get<1>(graph5[i])) {
					next = true;
					break;
				}
			}
			if (next)
				continue;

			graph3[get<0>(graph5[i]) - 1].push_back(make_pair(get<1>(graph5[i]), get<2>(graph5[i])));
			if (!r) {
				graph3[get<1>(graph5[i]) - 1].push_back(make_pair(get<0>(graph5[i]), get<2>(graph5[i])));
			}
		}
	}
	else {
		graph2.resize(n);
		for (int i = 0; i < graph4.size(); i++) {
			bool next = false;
			for (int j = 0; j < graph2[graph4[i].first - 1].size(); j++) {
				if (graph2[graph4[i].first - 1][j] == graph4[i].second) {
					next = true;
					break;
				}
			}
			if (next)
				continue;

			graph2[graph4[i].first - 1].push_back(graph4[i].second);
			if (!r) {
				graph2[graph4[i].second - 1].push_back(graph4[i].first);
			}
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
				if (graph3[i][j].first)
					addEdge(i + 1, graph3[i][j].first, graph3[i][j].second);
			}
		}
	}
	else {
		for (int i = 0; i < graph2.size(); i++) {
			for (int j = 0; j < graph2[i].size(); j++) {
				if (graph2[i][j])
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
