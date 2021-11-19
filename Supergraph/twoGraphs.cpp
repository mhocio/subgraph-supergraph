#include "twoGraphs.h"

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
		if (compareGraphs(exactAlgorithm.minimalSupergraph, approximateMinimalSupergraphAlgorithm.minimalCommonSupergraph)) {
			std::cout << "Supergraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Supergraphs of two algorithms are NOT same...\n";
		}

		if (compareGraphs(exactAlgorithm.maximalCommonSubgraph, approximateMaximalSubgraphAlgorithm.maximalCommonSubgraph)) {
			std::cout << "Common subgraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Common subgraphs of two algorithms are NOT same...\n";
		}
	}
}

bool twoGraphs::compareGraphs(std::vector<std::vector<int>> G1, std::vector<std::vector<int>> G2) {
	auto permutationsOfExactGraph = exactAlgorithm.getPermutationsOfSize(G1.size());

	bool correctMappingFound = false;

	for (auto permOfExactGraph : permutationsOfExactGraph) {
		auto reorderedGraph = exactAlgorithm.generateReorderedGraph(permOfExactGraph, G1);
		correctMappingFound = true;

		for (int i = 0; i < G1.size(); i++) {
			for (int j = 0; j < G1[i].size(); j++) {
				if (reorderedGraph[i][j] != G2[i][j]) {
					correctMappingFound = false;
				}
			}
		}
		if (correctMappingFound) {
			return correctMappingFound;
		}
	}

	return false;
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
