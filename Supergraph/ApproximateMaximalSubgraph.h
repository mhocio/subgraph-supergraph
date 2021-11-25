#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

class ApproximateMaximalSubgraph {
public:
	ApproximateMaximalSubgraph();
	ApproximateMaximalSubgraph(std::vector<std::vector<unsigned __int8>>, std::vector<std::vector<unsigned __int8>>);
	void getModularGraph();
	std::pair<int, int> getComponentIndices(int v);
	int getModularIndex(std::pair<int, int> v);
	void printModularGraph();
	int getMostConnectedVertex(std::unordered_set<int>& s);
	std::vector<int> getVerticesNotConnected(int v);
	void getMaximalCommonSubgraph();
	void printMaximalCommonSubgraph();
	
	std::vector<std::vector<unsigned __int8>> graph1;
	std::vector<std::vector<unsigned __int8>> graph2;
	std::vector<std::vector<unsigned __int8>> modularGraph;
	std::unordered_set<int> maximalCommonSubgraphVerticesGraph1;
	std::unordered_set<int> maximalCommonSubgraphVerticesGraph2;
	std::unordered_map<int, int> verticesFromGraph2ToGraph1;
	std::vector<std::vector<unsigned __int8>> maximalCommonSubgraph;
};