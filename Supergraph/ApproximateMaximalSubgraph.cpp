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

void ApproximateMaximalSubgraph::getMaximalCommonSubgraph() {
	std::unordered_set<int> sub;
	std::unordered_set<int> rest;
	for (int i = 0; i < size1 * size2; ++i) {
		rest.insert(i);
	}
}