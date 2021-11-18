#pragma once
#include <vector>

class GraphReader
{
public:

	GraphReader();
	std::vector<std::vector<int> > createGraphFromFile(const char* filename);

	//std::ifstream file;
	//std::string line;
};

