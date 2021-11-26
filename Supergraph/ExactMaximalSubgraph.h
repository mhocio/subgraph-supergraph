#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include "GraphReader.h"

class ExactSubgraph
{
public:
	ExactSubgraph();
	ExactSubgraph(std::vector<std::vector<unsigned __int8>>, std::vector<std::vector<unsigned __int8>>);
	void generateMaximalCommonSubgraph();
	std::vector<std::pair<std::vector<unsigned __int8>, std::vector<unsigned __int8> > > getPermutationsOfSize(int size);
	std::vector<std::vector<unsigned __int8>> generateReorderedGraph(std::pair<std::vector<unsigned __int8>, std::vector<unsigned __int8> >, std::vector<std::vector<unsigned __int8>>);
	int compareOverlayGraphs(std::vector<std::vector<unsigned __int8>> bigG, std::vector<std::vector<unsigned __int8>> smallG);
	int compareOverlayGraphsForSupergraph(std::vector<std::vector<unsigned __int8>> bigG, std::vector<std::vector<unsigned __int8>> smallG);

	std::vector<std::vector<unsigned __int8>> generateSuperGraph(std::vector<std::vector<unsigned __int8>> bigG, std::vector<std::vector<unsigned __int8>> smallG);

	std::vector<std::vector<unsigned __int8>> graph1;
	std::vector<std::vector<unsigned __int8>> graph2;
	std::vector<std::vector<unsigned __int8>> maximalCommonSubgraph;
	std::vector<std::vector<unsigned __int8>> minimalSupergraph;

	static int _count;
};

