#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

class ApproximateMaximalSubgraph {
public:
	ApproximateMaximalSubgraph();
	void getModularGraph();
	std::pair<int, int> getComponentIndices(int v);
	int getModularIndex(std::pair<int, int> v);
	void printModularGraph();
	int getMostConnectedVertex(std::unordered_set<int>& s);
	std::vector<int> getVerticesNotConnected(int v);
	void getMaximalCommonSubgraph();
	void printMaximalCommonSubgraph();
	
	std::vector<std::vector<int>> graph1;
	std::vector<std::vector<int>> graph2;
	std::vector<std::vector<int>> modularGraph;
	std::unordered_set<int> maximalCommonSubgraphVerticesGraph1;
	std::unordered_set<int> maximalCommonSubgraphVerticesGraph2;
	std::unordered_map<int, int> verticesFromGraph2ToGraph1;
	std::vector<std::vector<int>> maximalCommonSubgraph;
};