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
	std::vector<std::vector<unsigned __int8>> bestGraph;
};

using namespace std::chrono;

class twoGraphs
{
public:
	twoGraphs(std::string);
	twoGraphs(std::pair<std::vector<std::vector<unsigned __int8>>, std::vector<std::vector<unsigned __int8>>> graphs);
	void printSolution();
	void printExecutionTime();

	std::vector<std::vector<unsigned __int8>> graph1;  // bigger
	std::vector<std::vector<unsigned __int8>> graph2;  // smaller

	// exact solution
	void computeExactSolution();
	double exactSolutionTime;

	// approximate solution
	void computeApproximateSolution();
	double approximateSolutionTime;

	struct graphComarison_t compareGraphs(std::vector<std::vector<unsigned __int8>> G1, std::vector<std::vector<unsigned __int8>> G2);
	bool initialized();

private:
	twoGraphs();

	ExactSubgraph exactAlgorithm;
	std::vector<std::vector<unsigned __int8>> exactMaximalSubgraph;
	std::vector<std::vector<unsigned __int8>> exactMinimalSupergraph;

	ApproximateMaximalSubgraph approximateMaximalSubgraphAlgorithm;
	ApproximateMinimalSupergraph approximateMinimalSupergraphAlgorithm;
	std::vector<std::vector<unsigned __int8>> approximateMaximalSubgraph;
	std::vector<std::vector<unsigned __int8>> approximateMinimalSupergraph;

	void printGraph(std::vector<std::vector<unsigned __int8>>);
	void editSolutionAfterTwoAlgorithms();

	bool approximateComputed;
	bool exactComputed;
	bool readFromFfile;
	bool editedSolutionAfterTwoAlgorithms;
	graphComarison_t compareSupergraphs;
	graphComarison_t compareSubgraphs;
};

