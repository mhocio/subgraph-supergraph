#pragma once
#include <vector>

class GraphReader
{
public:

	GraphReader();
	int readInput(const char* filename);
	

	std::vector<std::vector<int> > graph1, graph2;
};

