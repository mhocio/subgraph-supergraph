#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "GraphReader.h"

class ExactSubgraph
{
public:
	ExactSubgraph();
	void generateMaximalCommonSubgraph();
	std::vector<std::pair<std::vector<int>, std::vector<int> > > getPermutationsOfBiggerGraph();
	std::vector<std::vector<int>> generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> >);
	int compareOverlayGraphs(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);

	std::vector<std::vector<int>> graph1;
	std::vector<std::vector<int>> graph2;
	std::vector<std::vector<int>> maximalCommonSubgraph;

	static int _count;
};

