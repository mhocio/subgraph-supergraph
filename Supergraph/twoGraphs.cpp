#include "twoGraphs.h"

void printGraphComarison_t(graphComarison_t g) {
	std::cout << "Number of missing edges: " << g.missingEdges;
	std::cout << " Number of redundant edges: " << g.redundantEdges << "\n";
}

twoGraphs::twoGraphs()
{
	approximateComputed = false;
	exactComputed = false;
	readFromFfile = false;
	editedSolutionAfterTwoAlgorithms = false;
}

twoGraphs::twoGraphs(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> graphs) {
	if (graphs.first.size() > graphs.second.size()) {
		graph1 = graphs.first;
		graph2 = graphs.second;
	}
	else {
		graph1 = graphs.second;
		graph2 = graphs.first;
	}
	approximateMaximalSubgraphAlgorithm = ApproximateMaximalSubgraph(graph1, graph2);
	exactAlgorithm = ExactSubgraph(graph1, graph2);

	readFromFfile = true;
}

twoGraphs::twoGraphs(std::string inputFile)
{
	twoGraphs();
	GraphReader reader;
	int ret = reader.readInput(inputFile.c_str());

	if (ret == 0) {

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

		readFromFfile = true;
	}
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

void twoGraphs::editSolutionAfterTwoAlgorithms() {
	if (exactComputed && approximateComputed) {
		compareSupergraphs = compareGraphs(exactMinimalSupergraph, approximateMinimalSupergraph);
		// change the bigger graph to be simillar to the smaller one
		// as they were different and we try to show how much similar they are
		if (!compareSupergraphs.correctMappingFound) {
			if (exactMinimalSupergraph.size() >= approximateMinimalSupergraph.size()) {
				exactMinimalSupergraph = compareSupergraphs.bestGraph;
			}
			else {
				approximateMinimalSupergraph = compareSupergraphs.bestGraph;
			}
		}

		compareSubgraphs = compareGraphs(exactMaximalSubgraph, approximateMaximalSubgraph);
		// change the bigger graph to be simillar to the smaller one
		if (!compareSubgraphs.correctMappingFound) {
			if (exactMaximalSubgraph.size() >= approximateMaximalSubgraph.size()) {
				exactMaximalSubgraph = compareSubgraphs.bestGraph;
			}
			else {
				approximateMaximalSubgraph = compareSubgraphs.bestGraph;
			}
		}

		editedSolutionAfterTwoAlgorithms = true;
	}
}

void twoGraphs::printExecutionTime() {
	if (approximateComputed)
		std::cout << "Approximate algorithm computed in " << approximateSolutionTime << " seconds\n";
	if (exactComputed)
		std::cout << "Exact algorithm computed in " << exactSolutionTime << " seconds\n";
}

void twoGraphs::printSeveralGraphsInOneLine(std::vector < std::pair < std::vector<std::vector<int>>, std::string >> graphs) {
	int maxSize = 0;
	int sum = 0;
	for (auto graph : graphs) {
		sum += graph.first.size();
		if (graph.first.size() > maxSize) {
			maxSize = graph.first.size();
		}
	}

	// print labels
	for (auto graph : graphs) {
		std::cout << graph.second << " ";
		if (graph.second.size() < graph.first.size() * 2) {
			for (int i = 0; i < graph.first.size() * 2 - graph.second.size(); i++) {
				std::cout << " ";
			}
		}
	}
	std::cout << "\n";

	// print sizes
	int k = 1;
	for (auto graph : graphs) {
		std::cout << graph.first.size();
		auto a = std::to_string(graph.first.size()).length();

		if (k < graphs.size()) {
			if (graph.first.size() > a) {
				for (int i = 0; i <= graph.first.size() - a; i++) {
					std::cout << "  ";
				}
			}
		}
		
		k++;
	}
	std::cout << "\n";

	std::vector<int> rowsGraphNumber;
	std::vector<int> graphsColumn;
	int graphNo = 0;
	for (auto graph : graphs) {
		for (int i = 0; i < graph.first.size(); i++) {
			rowsGraphNumber.push_back(graphNo);
			graphsColumn.push_back(i);
		}
		if (graphNo < (graphs.size() - 1)) {
			rowsGraphNumber.push_back(-1);  // break between graphs
			graphsColumn.push_back(-1);
		}
		graphNo++;
	}

	graphNo = 0;

	// print lines
	for (int i = 0; i < maxSize; i++) {
		// print rows
		graphNo = 0;
		for (int j = 0; j < sum + graphs.size() - 1; j++) {
			if (i < graphs[graphNo].first.size()) {
				if (rowsGraphNumber[j] != -1) {
					std::cout << graphs[rowsGraphNumber[j]].first[i][graphsColumn[j]] << " ";
				}
				else {
					std::cout << " ";  // break between graphs
					graphNo++;
				}
			}
			else {
				std::cout << " ";
				if (rowsGraphNumber[j] != -1) {
					std::cout << " ";
				}
				else {
					graphNo++;  // break between graphs
				}
			}
		}
		std::cout << "\n";
	}
}

void twoGraphs::printSolutionNice() {
	std::cout << "\nINPUT\n";
	printSeveralGraphsInOneLine({ {graph1, "graph1"}, {graph2, "graph2"} });

	if (exactComputed && approximateComputed && editedSolutionAfterTwoAlgorithms) {
		std::cout << "\n";
		if (compareSupergraphs.correctMappingFound) {
			std::cout << "Supergraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Supergraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSupergraphs);
		}

		if (compareSubgraphs.correctMappingFound) {
			std::cout << "Common subgraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Common subgraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSubgraphs);
		}
	}

	if (exactComputed) {
		std::cout << "\nEXACT ALGORITHM computed in " << exactSolutionTime << " seconds\n";;
		printSeveralGraphsInOneLine({ {exactMinimalSupergraph, "exactMinimalSupergraph"}, {exactMaximalSubgraph, "exactMaximalSubgraph"} });
	}
	if (approximateComputed) {
		std::cout << "\nAPPROXIMATE ALGORITHM computed in " << approximateSolutionTime << " seconds\n";;
		printSeveralGraphsInOneLine({ {approximateMinimalSupergraph, "approximateMinimalSupergraph"}, {approximateMaximalSubgraph, "approximateMaximalSubgraph"} });
	}
}

void twoGraphs::printSolution()
{
	if (exactComputed && approximateComputed && editedSolutionAfterTwoAlgorithms) {
		if (compareSupergraphs.correctMappingFound) {
			std::cout << "Supergraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Supergraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSupergraphs);
		}

		if (compareSubgraphs.correctMappingFound) {
			std::cout << "Common subgraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Common subgraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSubgraphs);
		}
	}


	if (approximateComputed)
		std::cout << "Approximate algorithm computed in " << approximateSolutionTime << " seconds\n";
	if (exactComputed) 
		std::cout << "Exact algorithm computed in " << exactSolutionTime << " seconds\n";

	if (approximateComputed) {
		std::cout << "approximateMaximalSubgraph\n";
		printGraph(approximateMaximalSubgraph);
		std::cout << "approximateMinimalSupergraph\n";
		printGraph(approximateMinimalSupergraph);
	}

	if (exactComputed) {
		std::cout << "exactMinimalSupergraph\n";
		printGraph(exactMinimalSupergraph);
		std::cout << "exactMaximalSubgraph\n";
		printGraph(exactMaximalSubgraph);
	}
}

// return changed bigger graph simillar to the smaller one
struct graphComarison_t twoGraphs::compareGraphs(std::vector<std::vector<int>> G1, std::vector<std::vector<int>> G2) {
	// first graph must be bigger or equal to the second one
	// as we permutate the bigger graph
	if (G1.size() < G2.size()) {
		std::swap(G1, G2);
	}

	auto permutationsOfExactGraph = exactAlgorithm.getPermutationsOfSize(G1.size());

	bool finalCorrectMappingFound = false;
	int minMissingEdges = std::numeric_limits<int>::max();
	int minRedundantEdges = std::numeric_limits<int>::max();
	std::vector<std::vector<int>> bestGraph;
	graphComarison_t ret;

	for (auto permOfExactGraph : permutationsOfExactGraph) {
		auto reorderedGraph = exactAlgorithm.generateReorderedGraph(permOfExactGraph, G1);  // bigger graph
		bool correctMappingFound = true;
		int missingEdges = 0;
		int redundantEdges = 0;

		for (int i = 0; i < G1.size(); i++) {
			for (int j = 0; j < G1[i].size(); j++) {

				if (i < G2.size() && j < G2.size()) { // G2 within the bigger graph (G1)
					if (reorderedGraph[i][j] != G2[i][j]) {
						correctMappingFound = false;
						if (reorderedGraph[i][j] == 1) {
							missingEdges++;
						}
						else {
							redundantEdges++;
						}
					}
				} else if (reorderedGraph[i][j] == 1){ // G1 biggger than G1
					missingEdges++;
					correctMappingFound = false;
				}
			}
		}

		if (correctMappingFound) {
			finalCorrectMappingFound = true;
		}
		else if (((long long int)minMissingEdges + (long long int)minRedundantEdges) > ((long long int)missingEdges + (long long int)redundantEdges)) {
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
	auto start = high_resolution_clock::now();

	exactAlgorithm.generateMaximalCommonSubgraph();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	exactSolutionTime = (double)duration.count() / 1000000; // in seconds

	exactMaximalSubgraph = exactAlgorithm.maximalCommonSubgraph;
	exactMinimalSupergraph = exactAlgorithm.minimalSupergraph;

	exactComputed = true;

	if (!editedSolutionAfterTwoAlgorithms) {
		editSolutionAfterTwoAlgorithms();
	}
}

void twoGraphs::computeApproximateSolution()
{
	auto start = high_resolution_clock::now();
	approximateMaximalSubgraphAlgorithm.getMaximalCommonSubgraph();
	approximateMaximalSubgraph = approximateMaximalSubgraphAlgorithm.maximalCommonSubgraph;

	// this can be used only after getMaximalCommonSubgraph() method was called
	approximateMinimalSupergraphAlgorithm = ApproximateMinimalSupergraph(approximateMaximalSubgraphAlgorithm);
	approximateMinimalSupergraphAlgorithm.getMinimalCommonSupergraph();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	approximateSolutionTime = (double)duration.count() / 1000000; // in seconds

	approximateMinimalSupergraph = approximateMinimalSupergraphAlgorithm.minimalCommonSupergraph;

	approximateComputed = true;

	if (!editedSolutionAfterTwoAlgorithms) {
		editSolutionAfterTwoAlgorithms();
	}
}
