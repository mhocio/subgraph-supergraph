#pragma once
#include <vector>
#include <unordered_set>
#include "ApproximateMaximalSubgraph.h"

class ApproximateMinimalSupergraph {
public:
	ApproximateMinimalSupergraph();
	ApproximateMinimalSupergraph(ApproximateMaximalSubgraph _approx);
	void getEmbedding();
	void getMinimalCommonSupergraph();
	void printMinimalCommonSupergraph();

	ApproximateMaximalSubgraph approx;
	std::vector<std::vector<int>> embedding;
	std::vector<std::vector<int>> minimalCommonSupergraph;
};
