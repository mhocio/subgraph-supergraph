#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <chrono>
#include "GraphReader.h"
#include "ApproximateMaximalSubgraph.h"
#include "ApproximateMinimalSupergraph.h"
#include "ExactMaximalSubgraph.h"

struct graphComarison_t {
	bool correctMappingFound; // if graph are same
	int missingEdges;
	int redundantEdges;
	std::vector<std::vector<int>> bestGraph;
};

using namespace std::chrono;

class twoGraphs
{
public:
	twoGraphs(std::string);
	twoGraphs(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> graphs);
	void printSolution();
	void printExecutionTime();
	void printSeveralGraphsInOneLine(std::vector < std::pair < std::vector<std::vector<int>>, 
		std::string >> graphs, std::vector<std::pair<int, int> > colors, int color, 
		std::vector<int> coloredLabels);
	void printSolutionNice();

	std::vector<std::vector<int>> graph1;  // bigger
	std::vector<std::vector<int>> graph2;  // smaller

	// exact solution
	void computeExactSolution();
	double exactSolutionTime;

	// approximate solution
	void computeApproximateSolution();
	double approximateSolutionTime;

	struct graphComarison_t compareGraphs(std::vector<std::vector<int>> G1, 
		std::vector<std::vector<int>> G2);
	bool initialized();
	bool readFromFfile;

private:
	twoGraphs();

	ExactSubgraph exactAlgorithm;
	std::vector<std::vector<int>> exactMaximalSubgraph;
	std::vector<std::vector<int>> exactMaximalSubgraphReordered;
	bool exactMaximalSubgraphReordered_b;
	std::vector<std::vector<int>> exactMinimalSupergraph;

	ApproximateMaximalSubgraph approximateMaximalSubgraphAlgorithm;
	ApproximateMinimalSupergraph approximateMinimalSupergraphAlgorithm;
	std::vector<std::vector<int>> approximateMaximalSubgraph;
	std::vector<std::vector<int>> approximateMaximalSubgraphReordered;
	bool approximateMaximalSubgraphReordered_b;
	std::vector<std::vector<int>> approximateMinimalSupergraph;

	void printGraph(std::vector<std::vector<int>>);
	void editSolutionAfterTwoAlgorithms();

	bool approximateComputed;
	bool exactComputed;
	bool editedSolutionAfterTwoAlgorithms;
	graphComarison_t compareSupergraphs;
	graphComarison_t compareSubgraphs;
};

