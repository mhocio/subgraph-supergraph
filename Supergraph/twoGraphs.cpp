#include "twoGraphs.h"

struct graphComarison_t {
	bool correctMappingFound; // if graph are same
	int missingEdges;
	int redundantEdges;
	std::vector<std::vector<int>> bestGraph;
};

twoGraphs::twoGraphs()
{
	approximateComputed = false;
	exactComputed = false;
	readFromFfile = false;
}

twoGraphs::twoGraphs(std::string inputFile)
{
	GraphReader reader;
	reader.readInput(inputFile.c_str());
	// making sure the graph with most number of vertices is assigned first
	if (reader.graph1.size() > reader.graph2.size()) {
		graph1 = reader.graph1;
		graph2 = reader.graph2;
	}
	else {
		graph2 = reader.graph1;
		graph1 = reader.graph2;
	}
	approximateMaximalSubgraphAlgorithm = ApproximateMaximalSubgraph(graph1, graph2);
	exactAlgorithm = ExactSubgraph(graph1, graph2);

	approximateComputed = false;
	exactComputed = false;
	readFromFfile = true;
}

bool twoGraphs::initialized()
{
	if (readFromFfile || (graph1.size() && graph2.size()))
		return true;
	return false;
}

void twoGraphs::printGraph(std::vector<std::vector<int>> G)
{
	if (G.empty()) {
		return;
	}

	int n = G.size();
	std::cout << n << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << G[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void twoGraphs::printSolution()
{
	if (approximateComputed) {
		std::cout << "Approximate algorithm computed\n";
		std::cout << "approximateMaximalSubgraph\n";
		printGraph(approximateMaximalSubgraph);
		std::cout << "approximateMinimalSupergraph\n";
		printGraph(approximateMinimalSupergraph);
	}

	if (exactComputed) {
		std::cout << "Exact algorithm computed\n";
		std::cout << "exactMinimalSupergraph\n";
		printGraph(exactMinimalSupergraph);
		std::cout << "exactMaximalSubgraph\n";
		printGraph(exactMaximalSubgraph);
	}

	if (exactComputed && approximateComputed) {
		auto compareSupergraphs = compareGraphs(exactAlgorithm.minimalSupergraph, approximateMinimalSupergraphAlgorithm.minimalCommonSupergraph);
		if (compareSupergraphs.correctMappingFound) {
			std::cout << "Supergraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Supergraphs of two algorithms are NOT same...\n";
		}

		auto compareSubgraphs = compareGraphs(exactAlgorithm.maximalCommonSubgraph, approximateMaximalSubgraphAlgorithm.maximalCommonSubgraph);
		if (compareSubgraphs.correctMappingFound) {
			std::cout << "Common subgraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Common subgraphs of two algorithms are NOT same...\n";
		}
	}
}

// second graph must be bigger or equal to the second one
struct graphComarison_t twoGraphs::compareGraphs(std::vector<std::vector<int>> G1, std::vector<std::vector<int>> G2) {
	if (G1.size() > G2.size()) {
		std::swap(G1, G2);
	}

	auto permutationsOfExactGraph = exactAlgorithm.getPermutationsOfSize(G1.size());

	bool finalCorrectMappingFound = false;
	int minMissingEdges = std::numeric_limits<int>::max();
	int minRedundantEdges = std::numeric_limits<int>::max();
	std::vector<std::vector<int>> bestGraph;
	graphComarison_t ret;

	for (auto permOfExactGraph : permutationsOfExactGraph) {
		auto reorderedGraph = exactAlgorithm.generateReorderedGraph(permOfExactGraph, G1);
		bool correctMappingFound = true;
		int missingEdges = 0;
		int redundantEdges = 0;

		for (int i = 0; i < G1.size(); i++) {
			for (int j = 0; j < G1[i].size(); j++) {
				if (reorderedGraph[i][j] != G2[i][j]) {
					correctMappingFound = false;
					/*if (reorderedGraph[i][j] == 0) {
						missingEdges++;
					}
					else {
						redundantEdges++;
					}*/
				}
			}
		}

		if (correctMappingFound) {
			finalCorrectMappingFound = true;
		}
		else if ((minMissingEdges + minRedundantEdges) > (missingEdges + redundantEdges)) {
			minMissingEdges = missingEdges;
			minRedundantEdges = redundantEdges;
			bestGraph = reorderedGraph;
		}
	}

	ret.correctMappingFound = finalCorrectMappingFound;
	ret.missingEdges = minMissingEdges;
	ret.redundantEdges = minRedundantEdges;
	ret.bestGraph = bestGraph;

	return ret;
}

void twoGraphs::computeExactSolution()
{
	exactAlgorithm.generateMaximalCommonSubgraph();
	exactMaximalSubgraph = exactAlgorithm.maximalCommonSubgraph;
	exactMinimalSupergraph = exactAlgorithm.minimalSupergraph;

	exactComputed = true;
}

void twoGraphs::computeApproximateSolution()
{
	approximateMaximalSubgraphAlgorithm.getMaximalCommonSubgraph();
	approximateMaximalSubgraph = approximateMaximalSubgraphAlgorithm.maximalCommonSubgraph;

	// this can be used only after getMaximalCommonSubgraph() method was called
	approximateMinimalSupergraphAlgorithm = ApproximateMinimalSupergraph(approximateMaximalSubgraphAlgorithm);
	approximateMinimalSupergraphAlgorithm.getMinimalCommonSupergraph();
	approximateMinimalSupergraph = approximateMinimalSupergraphAlgorithm.minimalCommonSupergraph;

	approximateComputed = true;
}
