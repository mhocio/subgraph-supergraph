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
	ExactSubgraph(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
	void generateMaximalCommonSubgraph();
	std::vector<std::pair<std::vector<int>, std::vector<int> > > getPermutationsOfBiggerGraph();
	std::vector<std::vector<int>> generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> >);
	int compareOverlayGraphs(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);
	int compareOverlayGraphsForSupergraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);

	std::vector<std::vector<int>> generateSuperGraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);

	std::vector<std::vector<int>> graph1;
	std::vector<std::vector<int>> graph2;
	std::vector<std::vector<int>> maximalCommonSubgraph;
	std::vector<std::vector<int>> minimalSupergraph;

	static int _count;
};

