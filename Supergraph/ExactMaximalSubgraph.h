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
	std::vector<std::pair<std::vector<int>, std::vector<int> > > getPermutationsOfSize(int size);
	std::vector<std::vector<int>> generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> >, std::vector<std::vector<int>>);
	int compareOverlayGraphs(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);
	std::pair<int, bool> compareOverlayGraphsForSupergraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);

	std::vector<std::vector<int>> generateSuperGraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG);

	std::vector<std::vector<int>> graph1;
	std::vector<std::vector<int>> graph2;

	std::vector<std::vector<int>> maximalCommonSubgraph;
	std::vector<std::vector<int>> reorderedGraphForSubgraph;
	std::pair<std::vector<int>, std::vector<int> > permOfBiggerGraphForSubgraph;

	std::vector<std::vector<int>> minimalSupergraph;
	std::vector<std::vector<int>> reorderedGraphForSupergraph;
	std::vector<std::vector<int>> smallGraphCandidateForSupergraph;
	std::pair<std::vector<int>, std::vector<int> > permOfBiggerGraphForSupergraph;

	bool isSupergraphInduced = false;
	std::vector<std::vector<int>> minimalInducedSupergraph;

	static int _count;
};

