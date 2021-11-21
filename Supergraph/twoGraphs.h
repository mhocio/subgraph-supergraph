#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
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

class twoGraphs
{
public:
	twoGraphs();
	twoGraphs(std::string);

	bool initialized();
	void printGraph(std::vector<std::vector<int>>);
	void printSolution();

	std::vector<std::vector<int>> graph1;  // bigger
	std::vector<std::vector<int>> graph2;  // smaller

	// exact solution
	void computeExactSolution();
	ExactSubgraph exactAlgorithm;
	std::vector<std::vector<int>> exactMaximalSubgraph;
	std::vector<std::vector<int>> exactMinimalSupergraph;

	// approximate solution
	void computeApproximateSolution();
	ApproximateMaximalSubgraph approximateMaximalSubgraphAlgorithm;
	ApproximateMinimalSupergraph approximateMinimalSupergraphAlgorithm;
	std::vector<std::vector<int>> approximateMaximalSubgraph;
	std::vector<std::vector<int>> approximateMinimalSupergraph;

	struct graphComarison_t compareGraphs(std::vector<std::vector<int>> G1, std::vector<std::vector<int>> G2);

private:
	void editSolutionAfterTwoAlgorithms();
	bool approximateComputed;
	bool exactComputed;
	bool readFromFfile;
	bool editedSolutionAfterTwoAlgorithms;

	graphComarison_t compareSupergraphs;
	graphComarison_t compareSubgraphs;
};

