#include "ExactMaximalSubgraph.h"

ExactMaximalSubgraph::ExactMaximalSubgraph() {
	GraphReader reader;
	reader.readInput("input2.txt");
	// making sure the graph with most number of vertices is assigned first
	if (graph1.size() > graph2.size()) {
		graph1 = reader.graph1;
		graph2 = reader.graph2;
	}
	else {
		graph2 = reader.graph1;
		graph1 = reader.graph2;
	}
}

// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c/28698654
std::vector<std::vector<int>> comb(int N, int K) {
	std::vector<std::vector<int>> ret;
	std::string bitmask(K, 1); // K leading 1's
	bitmask.resize(N, 0); // N-K trailing 0's

	// generate integers and permute bitmask
	do {
		std::vector<int> combination;
		for (int i = 0; i < N; ++i) // [0..N-1] integers
		{
			if (bitmask[i]) {
				combination.push_back(i);
			}
		}
		ret.push_back(combination);
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));

	return ret;
}

std::vector<std::vector<int>> getPerms(int size) {
	std::vector<std::vector<int>> ret;
	for (int i = 2; i <= size; i++) {
		std::vector<std::vector<int>> appendCombinations = comb(size, i);
		ret.insert(ret.end(), appendCombinations.begin(), appendCombinations.end());
	}
	return ret;
}

std::vector<std::pair<std::vector<int>, std::vector<int> > > ExactMaximalSubgraph::getPermutationsOfBiggerGraph() {
	// (cols, rows)
	std::vector<std::pair<std::vector<int>, std::vector<int> > > ret;
	
	std::vector<int> numbers;
	std::vector<std::vector<int>> perms;
	for (int i = 0; i < graph1.size(); i++) {
		numbers.push_back(i);
	}

	do {
		/*for (int i = 0; i < graph1.size(); i++) {
			std::cout << numbers[i] << " ";
		}
		std::cout << "\n";*/
		perms.push_back(numbers);
	} while (std::next_permutation(numbers.begin(), numbers.end()));

	for (int i = 0; i < perms.size(); i++) {
		for (int j = 0; j < perms.size(); j++) {
			ret.push_back(std::make_pair(perms[i], perms[j]));
		}
	}

	return ret;
}

std::vector<std::vector<int>> ExactMaximalSubgraph::generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> > ordering) {
	// of the First graph
	// reorder columns
	std::vector<std::vector<int>> reorderedColumns;
	for (int i = 0; i < graph1.size(); i++) {
		std::vector<int> row;
		for (int j = 0; j < ordering.first.size(); j++) {
			row.push_back(graph1[i][ordering.first[j]]);
		}
		reorderedColumns.push_back(row);
	}
	// reorder rows
	std::vector<std::vector<int>> reorderedMatrix;
	for (int i = 0; i < graph1.size(); i++) {
		std::vector<int> row;
		for (int j = 0; j < ordering.second.size(); j++) {
			row.push_back(reorderedColumns[ordering.second[i]][j]);
		}
		reorderedMatrix.push_back(row);
	}

	return reorderedMatrix;
}

std::vector<std::vector<int>> generateCandidate(std::vector<std::vector<int>> smallerGraph, std::vector<int> verticesOfSmallerGraph) {
	std::vector<std::vector<int>> ret;

	for (int i = 0; i < smallerGraph.size(); i++) {
		std::vector<int> row;
		for (int j = 0; j < smallerGraph.size(); j++) {
			if ((std::find(verticesOfSmallerGraph.begin(), verticesOfSmallerGraph.end(), i) != verticesOfSmallerGraph.end())
				&& (std::find(verticesOfSmallerGraph.begin(), verticesOfSmallerGraph.end(), j) != verticesOfSmallerGraph.end())) {
				row.push_back(smallerGraph[i][j]);
			}
		}
		if (row.size()) {
			ret.push_back(row);
		}
	}
	return ret;
}

int compareOverlayGraphs(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG) {
	int count = 0;
	// return -1 if they do NOT overlap
	for (int i = 0; i < smallG.size(); i++) {
		for (int j = 0; j < smallG.size(); j++) {
			if (smallG[i][j] != bigG[i][j]) {
				return -1;
			}
			else if (smallG[i][j] == 1) {
				count++;
			}
		}
	}

	return count;
}

void printGraph(std::vector<std::vector<int>> G) {
	for (int i = 0; i < G.size(); i++) {
		for (int j = 0; j < G[i].size(); j++) {
			std::cout << G[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void ExactMaximalSubgraph::generateMaximalCommonSubgraph() {
	// assume 1st graph is bigger or same size
	//std::vector<std::vector<int>> maximalCommonSubgraph;

	//auto a = getPermutationsOfBiggerGraph();

	//std::vector<std::vector<int>> M = generateReorderedGraph({ {1, 0, 2, 3}, { 1,0,2,3 } });

	/*for (int i = 0; i < graph1.size(); i++) {
		for (int j = 0; j < graph1.size(); j++) {
			std::cout << M[i][j] << " ";
		}
		std::cout << "\n";
	}*/

	printGraph(graph1);
	printGraph(graph2);

	int maxNumberOfEdges = 0;
	std::vector<std::vector<int>> maximalCommonSubgraph;

	auto permutationsOfBiggerGraph = getPermutationsOfBiggerGraph();
	for (auto permOfBiggerGraph : permutationsOfBiggerGraph) {
		auto reorderedGraph = generateReorderedGraph(permOfBiggerGraph);

		std::vector<std::vector<int>> setOfAllVerticesCandidates = getPerms(graph2.size());
		for (std::vector<int> verticesOfSmallerGraph : setOfAllVerticesCandidates) {
			auto smallGraphCandidate = generateCandidate(graph2, verticesOfSmallerGraph);
			int numOfEdges = compareOverlayGraphs(reorderedGraph, smallGraphCandidate);

			if (numOfEdges > maxNumberOfEdges) {
				maxNumberOfEdges = numOfEdges;
				maximalCommonSubgraph = smallGraphCandidate;
			}
		}
	}

	std::cout << maxNumberOfEdges << '\n';
	printGraph(maximalCommonSubgraph);

	//auto a = comb(5, 3);
	/*auto a = getPerms(5);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << "\n";
	}*/

	/////////////
	/*std::vector<std::vector<int>> candidate = generateCandidate(graph1, { 0,1,3 });

	for (int i = 0; i < candidate.size(); i++) {
		for (int j = 0; j < candidate.size(); j++) {
			std::cout << candidate[i][j] << " ";
		}
		std::cout << "\n";
	}*/
}