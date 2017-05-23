#pragma once

#include <vector>

using namespace std;

class DSU
{
public:
	vector <int> p;
	vector <int> rank;

	DSU();
	DSU(int);

	int find(int);
	void unite(int, int);

	~DSU();
};

