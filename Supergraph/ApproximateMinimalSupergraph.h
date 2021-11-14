#pragma once
#include <vector>
#include <unordered_set>
#include "ApproximateMaximalSubgraph.h"

class ApproximateMinimalSupergraph {
public:
	ApproximateMinimalSupergraph(ApproximateMaximalSubgraph _approx);
	void getEmbedding();
	void getMinimalCommonSupergraph();

	ApproximateMaximalSubgraph approx;
	std::vector<std::vector<int>> embedding;
	std::vector<std::vector<int>> minimalCommonSupergraph;
};
