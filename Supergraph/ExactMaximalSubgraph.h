#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "GraphReader.h"

class ExactMaximalSubgraph
{
public:
	ExactMaximalSubgraph();
	void generateMaximalCommonSubgraph();
	std::vector<std::pair<std::vector<int>, std::vector<int> > > getPermutationsOfBiggerGraph();
	std::vector<std::vector<int>> generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> >);

	std::vector<std::vector<int>> graph1;
	std::vector<std::vector<int>> graph2;
	std::vector<std::vector<int>> maximalCommonSubgraph;
};

