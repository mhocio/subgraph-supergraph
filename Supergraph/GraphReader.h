#pragma once
#include <vector>

class GraphReader
{
public:

	GraphReader();
	int readInput(const char* filename);
	

	std::vector<std::vector<unsigned __int8> > graph1, graph2;
};

