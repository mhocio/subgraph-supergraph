#include "ApproximateMaximalSubgraph.h"
#include "GraphReader.h"

ApproximateMaximalSubgraph::ApproximateMaximalSubgraph() {
	/*GraphReader reader;
	reader.readInput("input2.txt");
	// making sure the graph with most number of vertices is assigned first
	if (reader.graph1.size() > reader.graph2.size()) {
		graph1 = reader.graph1;
		graph2 = reader.graph2;
	}
	else {
		graph2 = reader.graph1;
		graph1 = reader.graph2;
	}
	modularGraph = std::vector<std::vector<int>>(graph1.size() * graph2.size(), std::vector<int>(graph1.size() * graph2.size(), 0));*/
}

ApproximateMaximalSubgraph::ApproximateMaximalSubgraph(std::vector<std::vector<int>> g1, std::vector<std::vector<int>> g2)
{
	graph1 = g1;
	graph2 = g2;
	modularGraph = std::vector<std::vector<int>>(graph1.size() * graph2.size(), std::vector<int>(graph1.size() * graph2.size(), 0));
}

void ApproximateMaximalSubgraph::getModularGraph() {
	for (int i = 0; i < graph1.size() * graph2.size(); ++i) {
		for (int j = 0; j < graph1.size() * graph2.size(); ++j) {
			std::pair<int, int> uv1 = getComponentIndices(i);
			std::pair<int, int> uv2 = getComponentIndices(j);
			if (uv1.first != uv2.first && uv1.second != uv2.second) {
				if ((graph1[uv1.first][uv2.first] == 1 && graph2[uv1.second][uv2.second] == 1) ||
					(graph1[uv1.first][uv2.first] == 0 && graph2[uv1.second][uv2.second] == 0)) {
					modularGraph[i][j] = 1;
				}
			}
		}
	}
}

std::pair<int, int> ApproximateMaximalSubgraph::getComponentIndices(int v) {
	std::pair<int, int> result;
	result.first = v / graph2.size();
	result.second = v % graph2.size();
	return result;
}

int ApproximateMaximalSubgraph::getModularIndex(std::pair<int, int> v) {
	return v.first * graph2.size() + v.second;
}

void ApproximateMaximalSubgraph::printModularGraph() {
	for (int i = 0; i < graph1.size() * graph2.size(); ++i) {
		for (int j = 0; j < graph1.size() * graph2.size(); ++j) {
			std::cout << modularGraph[i][j] << " ";
		}
		std::cout << "\n";
	}
}

int ApproximateMaximalSubgraph::getMostConnectedVertex(std::unordered_set<int>& s) {
	int result;
	std::vector<int> vertices(s.begin(), s.end());
	int global_max = 0;
	int global_vertex = vertices[0]; // We assume that s is non-empty;
	for (int v1 : vertices) {
		int local_max = 0;
		for (int v2 : vertices) {
			if (modularGraph[v1][v2] == 1) {
				++local_max;
			}
		}
		if (local_max > global_max) {
			global_vertex = local_max;
			global_vertex = v1;
		}
	}
	return global_vertex;
}

std::vector<int> ApproximateMaximalSubgraph::getVerticesNotConnected(int v) {
	std::vector<int> result;
	for (int i = 0; i < graph1.size() * graph2.size(); ++i) {
		if (modularGraph[v][i] == 0) {
			result.push_back(i);
		}
	}
	return result;
}

void ApproximateMaximalSubgraph::getMaximalCommonSubgraph() {
	std::unordered_set<int> sub;
	std::unordered_set<int> rest;
	getModularGraph();
	// An approximate algorithm for finding the largest clique in the modular graph.
	for (int i = 0; i < graph1.size() * graph2.size(); ++i) {
		rest.insert(i);
	}
	while (!rest.empty()) {
		int y = getMostConnectedVertex(rest);
		sub.insert(y);
		std::vector<int> toRemove = getVerticesNotConnected(y);
		for (int v : toRemove) {
			if (rest.find(v) != rest.end()) {
				rest.erase(v);
			}
		}
	}
	std::vector<int> subVertices(sub.begin(), sub.end());
	int n = subVertices.size();
	maximalCommonSubgraphVerticesGraph1.clear();
	maximalCommonSubgraphVerticesGraph2.clear();
	// Store vertices of the projections of the maximal common subgraph into
	// both input graphs.
	for (int i = 0; i < n; ++i) {
		int first = getComponentIndices(subVertices[i]).first;
		int second = getComponentIndices(subVertices[i]).second;
		maximalCommonSubgraphVerticesGraph1.insert(first);
		maximalCommonSubgraphVerticesGraph2.insert(second);
		verticesFromGraph2ToGraph1[second] = first;
	}
	// Get the mapping from graph2 (smaller) to graph1 (larger).
	int j = 0;
	for (int i = 0; i < graph2.size(); ++i) {
		if (maximalCommonSubgraphVerticesGraph2.find(i) == maximalCommonSubgraphVerticesGraph2.end()) {
			while (maximalCommonSubgraphVerticesGraph1.find(j) != maximalCommonSubgraphVerticesGraph1.end()) {
				++j;
			}
			verticesFromGraph2ToGraph1[i] = j;
		}
	}
	
	// Build the maximal common subgraph.
	maximalCommonSubgraph = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// We project onto the second, smaller graph.
			int projected_vi = getComponentIndices(subVertices[i]).second;
			int projected_vj = getComponentIndices(subVertices[j]).second;
			//if (projected_vi < graph1.size() && projected_vj < graph1.size())
			if (graph2[projected_vi][projected_vj] == 1) {
				maximalCommonSubgraph[i][j] = 1;
			}
		}
	}
}

void ApproximateMaximalSubgraph::printMaximalCommonSubgraph() {
	if (maximalCommonSubgraph.empty()) {
		return;
	}
	int n = maximalCommonSubgraph.size();
	std::cout << n << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << maximalCommonSubgraph[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}