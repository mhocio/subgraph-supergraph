#include "ApproximateMaximalSubgraph.h"

ApproximateMaximalSubgraph::ApproximateMaximalSubgraph() {
	size1 = 3;
	graph1 = { {0, 1, 0}, {1, 0, 1}, {0, 1, 0} };
	size2 = 3;
	graph2 = { {0, 1, 0}, {1, 0, 1}, {0, 1, 0} };
	modularGraph = std::vector<std::vector<int>>(size1 * size2, std::vector<int>(size1 * size2, 0));
}

void ApproximateMaximalSubgraph::getModularGraph() {
	for (int i = 0; i < size1 * size2; ++i) {
		for (int j = 0; j < size1 * size2; ++j) {
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
	result.first = v / size1;
	result.second = v % size1;
	return result;
}

int ApproximateMaximalSubgraph::getModularIndex(std::pair<int, int> v) {
	return v.first * size1 + v.second;
}

void ApproximateMaximalSubgraph::printModularGraph() {
	for (int i = 0; i < size1 * size2; ++i) {
		for (int j = 0; j < size1 * size2; ++j) {
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
	for (int i = 0; i < size1 * size2; ++i) {
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
	for (int i = 0; i < size1 * size2; ++i) {
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
	maximalCommonSubgraph = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// We project onto the first graph (the second graph might be used as well).
			int projected_vi = getComponentIndices(subVertices[i]).first;
			int projected_vj = getComponentIndices(subVertices[j]).first;
			if (graph1[projected_vi][projected_vj] == 1) {
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
}