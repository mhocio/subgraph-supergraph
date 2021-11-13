#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>

class ApproximateMaximalSubgraph {
public:
	ApproximateMaximalSubgraph();
	void getModularGraph();
	std::pair<int, int> getComponentIndices(int v);
	int getModularIndex(std::pair<int, int> v);
	void printModularGraph();
	void getMaximalCommonSubgraph();
	int getMostConnectedVertex(std::unordered_set<int>& s);
	
	std::vector<std::vector<int>> graph1;
	int size1;
	std::vector<std::vector<int>> graph2;
	int size2;
	std::vector<std::vector<int>> modularGraph;
	std::vector<std::vector<int>> maximalCommonSubgraph;
};