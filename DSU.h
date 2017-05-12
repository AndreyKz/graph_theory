#pragma once

#include <vector>

using namespace std;

class DSU
{
private:
	vector <int> p;
	vector <int> rank;
public:
	DSU();
	DSU(int);

	int find(int);
	void unite(int, int);

	~DSU();
};

