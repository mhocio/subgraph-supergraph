#include "twoGraphs.h"

void printGraphComarison_t(graphComarison_t g, bool printReverse=false) {
	// printReverse to true is used when the first and changed graph is the graph
	// computed with approx algorithm, which means that we counted missing and redundant edges
	// of the exact graph in comparison to the approximated one.
	// Therefore if we want to print still the information of missing edges of approx graph in respect to
	// the exact graph we need to print no of redundant edges (if an edge was redundant in exact graph
	// then it is really missing in approx) in that case.
	if (!printReverse) {
		std::cout << "Number of missing edges: " << g.missingEdges;
		std::cout << " Number of redundant edges: " << g.redundantEdges << "\n";
	}
	else {
		std::cout << "Number of missing edges: " << g.redundantEdges;
		std::cout << " Number of redundant edges: " << g.missingEdges << "\n";
	}
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
	if (readFromFfile && (graph1.size() && graph2.size()))
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
		compareSupergraphs = compareGraphs(approximateMinimalSupergraph, exactMinimalSupergraph);
		// change the bigger graph to be simillar to the smaller one
		// as they were different and we try to show how much similar they are
		if (!compareSupergraphs.correctMappingFound) {
			/*/if (exactMinimalSupergraph.size() >= approximateMinimalSupergraph.size()) {
				exactMinimalSupergraph = compareSupergraphs.bestGraph;
			}
			else {
				approximateMinimalSupergraph = compareSupergraphs.bestGraph;
			}*/
			// supergraphs are of the same size
			approximateMinimalSupergraph = compareSupergraphs.bestGraph;
		}

		compareSubgraphs = compareGraphs(approximateMaximalSubgraph, exactMaximalSubgraph);
		// change the bigger graph to be simillar to the smaller one
		if (!compareSubgraphs.correctMappingFound) {
			if (exactMaximalSubgraph.size() > approximateMaximalSubgraph.size()) {
				exactMaximalSubgraphReordered = compareSubgraphs.bestGraph;
				exactMaximalSubgraphReordered_b = true;
				approximateMaximalSubgraphReordered_b = false;
			}
			else {
				approximateMaximalSubgraphReordered = compareSubgraphs.bestGraph;
				approximateMaximalSubgraphReordered_b = true;
				exactMaximalSubgraphReordered_b = false;
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
	int i = 1;
	for (auto graph : graphs) {
		std::cout << "[" << graph.second << "]";
		if (i++ < graphs.size()) {
			std::cout << "; ";
		}
		if (graph.second.size() < graph.first.size() * 2 - 3) {
			for (int i = 0; i < graph.first.size() * 2 - graph.second.size() - 3; i++) {
				std::cout << " ";
			}
		}
	}
	std::cout << "\n";

	// print sizes
	int k = 1;
	for (auto graph : graphs) {
		std::cout << graph.first.size();
		auto a = std::to_string(graph.first.size() + 1).length();

		if (k < graphs.size()) {
			if (graph.first.size() > a) {
				for (int i = 0; i <= graph.first.size() * 2 - a; i++) {
					std::cout << " ";
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

void printWithColor(std::string s, bool endWithNewLine=false, int color = 31) {
	/*
	*   Name            FG  BG
		Black           30  40
		Red             31  41
		Green           32  42
		Yellow          33  43
		Blue            34  44
		Magenta         35  45
		Cyan            36  46
		White           37  47
		Bright Black    90  100
		Bright Red      91  101
		Bright Green    92  102
		Bright Yellow   93  103
		Bright Blue     94  104
		Bright Magenta  95  105
		Bright Cyan     96  106
		Bright White    97  107
	*/
	std::cout << "\x1B[" <<color << "m" << s << "\033[0m\t\t";
	if (endWithNewLine) {
		std::cout << "\n";
	}
}

void printPermChanges(std::pair<std::vector<int>, std::vector<int> > perm, std::string nameOfGraph="subgraph") {
	std::cout << "Reordered vertices of the bigger graph for computing " << nameOfGraph << ", number of the first vertex is 1 (after remapping->original number) : \n";
	int i = 1;
	for (auto v : perm.first) {
		std::cout << "(" << i++ << " -> " << v + 1 << ")";
		if (i < perm.first.size() + 1) {
			std::cout << ", ";
		}
	}
}

void twoGraphs::printSolutionNice() {
	printWithColor("=== INPUT ===", true);
	//std::cout << "\n=== INPUT ===\n";
	//std::cout << "\x1B[31mTexting\033[0m\t\t\n";

	printSeveralGraphsInOneLine({ {graph1, "graph1"}, {graph2, "graph2"} });

	if (exactComputed) {
		std::cout << "\n";
		printWithColor("=== EXACT ALGORITHM computed in " + std::to_string(exactSolutionTime) + " seconds ===", true);

		std::vector < std::pair < std::vector<std::vector<int>>, std::string >> graphsToPrint =
		{ {exactAlgorithm.reorderedGraphForSubgraph, "Reordered bigger (first) graph for finding the maximal common induced subgraph"} ,
			{exactMaximalSubgraph, "exactMaximalSubgraph"} };

		if (exactMaximalSubgraphReordered_b) {
			graphsToPrint.push_back({ exactMaximalSubgraphReordered , {"reordered subgraph to compare with approximate result"}});
		}

		printSeveralGraphsInOneLine(graphsToPrint);
		printPermChanges(exactAlgorithm.permOfBiggerGraphForSubgraph);
		std::cout << "\n\n";
		
		printSeveralGraphsInOneLine({ {exactAlgorithm.reorderedGraphForSupergraph, "Reordered bigger graph for finding the minimal supergraph"}, {exactAlgorithm.smallGraphCandidateForSupergraph, "smallGraphCandidateForSupergraph"} ,{exactMinimalSupergraph, "exactMinimalSupergraph"}});
		printPermChanges(exactAlgorithm.permOfBiggerGraphForSupergraph, "supergraph");
		std::cout << "\n\n";
	}
	if (approximateComputed) {
		std::cout << "\n";
		printWithColor("=== APPROXIMATE ALGORITHM computed in " + std::to_string(approximateSolutionTime) + " seconds ===", true);
		printSeveralGraphsInOneLine({ {approximateMinimalSupergraph, "approximateMinimalSupergraph"}, {approximateMaximalSubgraph, "approximateMaximalSubgraph"} });
	}

	if (exactComputed && approximateComputed && editedSolutionAfterTwoAlgorithms) {
		std::cout << "\n";
		if (compareSupergraphs.correctMappingFound) {
			std::cout << "Supergraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Supergraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSupergraphs, true);
		}

		if (compareSubgraphs.correctMappingFound) {
			std::cout << "Common subgraphs of two algorithms are same!\n";
		}
		else {
			std::cout << "Common subgraphs of two algorithms are NOT same... ";
			printGraphComarison_t(compareSubgraphs);
		}
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
