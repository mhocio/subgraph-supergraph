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
	approximateMinimalSupergraphAlgorithm = ApproximateMinimalSupergraph(approximateMaximalSubgraphAlgorithm);
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
		std::cout << "approximateMinimalSupergraph\n";
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
}

void twoGraphs::computeExactSolution()
{
	exactAlgorithm.generateMaximalCommonSubgraph();
	exactMaximalSubgraph = exactAlgorithm.maximalCommonSubgraph;

	exactComputed = true;
}

void twoGraphs::computeApproximateSolution()
{
	approximateMaximalSubgraphAlgorithm.getMaximalCommonSubgraph();
	//approximateMaximalSubgraphAlgorithm.printMaximalCommonSubgraph();
	approximateMaximalSubgraph = approximateMaximalSubgraphAlgorithm.maximalCommonSubgraph;

	approximateMinimalSupergraphAlgorithm.getMinimalCommonSupergraph();
	approximateMinimalSupergraph = approximateMinimalSupergraphAlgorithm.minimalCommonSupergraph;

	approximateComputed = true;
}
