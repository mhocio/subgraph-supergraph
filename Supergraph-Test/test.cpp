#include "pch.h"
#include "../Supergraph/graphGenerator.h"
#include "../Supergraph/twoGraphs.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

//bool compareGraphs(std::vector<std::vector<int>> g1, std::vector<std::vector<int>> g2) {
//	auto compare1 = twoGraphs(std::make_pair(g1, g2));
//	return compare1.compareGraphs(compare1.graph1, compare1.graph2).correctMappingFound;
//}

TEST(InputTest, Input1) {
	twoGraphs solution = twoGraphs("input1.txt");
	solution.computeApproximateSolution();
	solution.computeExactSolution();

	std::vector<std::vector<int>> approximateMaximalSubgraph = { {0, 1}, {1, 0} };
	std::vector<std::vector<int>> approximateMinimalSupergraph = { { 0, 1, 1, 1 }, { 1, 0, 1, 0 }, { 1, 1, 0, 1 }, { 1, 0, 1, 0 } };

	std::vector<std::vector<int>> exactMaximalSubgraph = { {0, 1}, {1, 0} };
	std::vector<std::vector<int>> exactMinimalSupergraph = { { 0, 1, 1, 1 }, { 1, 0, 1, 0 }, { 1, 1, 0, 1 }, { 1, 0, 1, 0 } };

	/*EXPECT_TRUE(compareGraphs(solution.getApproximateMaximalSubgraph(), approximateMaximalSubgraph));
	EXPECT_TRUE(compareGraphs(solution.getApproximateMinimalSupergraph(), approximateMinimalSupergraph));
	EXPECT_TRUE(compareGraphs(solution.getExactMaximalSubgraph(), exactMaximalSubgraph));
	EXPECT_TRUE(compareGraphs(solution.getExactMinimalSupergraph(), exactMinimalSupergraph));*/

}