#include "ApproximateMaximalSubgraph.h"
#include "ApproximateMinimalSupergraph.h"

ApproximateMinimalSupergraph::ApproximateMinimalSupergraph(ApproximateMaximalSubgraph _approx) {
	approx = _approx;
}

void ApproximateMinimalSupergraph::getEmbedding() {
	// This function computes emb(K, graph2), where K is the approximate maximal subgraph.
	// Then it maps it to graph1.
	int n = approx.graph1.size();
	embedding = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
	for (int i = 0; i < approx.graph2.size(); ++i) {
		for (int j = 0; j < approx.graph2.size(); ++j) {
			if ((approx.maximalCommonSubgraphVerticesGraph2.find(i) != approx.maximalCommonSubgraphVerticesGraph2.end() &&
				approx.maximalCommonSubgraphVerticesGraph2.find(j) == approx.maximalCommonSubgraphVerticesGraph2.end()) ||

				(approx.maximalCommonSubgraphVerticesGraph2.find(i) == approx.maximalCommonSubgraphVerticesGraph2.end() &&
					approx.maximalCommonSubgraphVerticesGraph2.find(j) != approx.maximalCommonSubgraphVerticesGraph2.end())) {

				embedding[approx.verticesFromGraph2ToGraph1[i]][approx.verticesFromGraph2ToGraph1[j]] = 1;
			}

		}
	}

}

void ApproximateMinimalSupergraph::getMinimalCommonSupergraph() {
	minimalCommonSupergraph = approx.graph1;

}