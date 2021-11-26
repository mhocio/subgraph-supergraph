#include "ExactMaximalSubgraph.h"

ExactSubgraph::ExactSubgraph() {
	GraphReader reader;
	reader.readInput("input2.txt");
	// making sure the graph with most number of vertices is assigned first
	if (reader.graph1.size() > reader.graph2.size()) {
		graph1 = reader.graph1;
		graph2 = reader.graph2;
	}
	else {
		graph2 = reader.graph1;
		graph1 = reader.graph2;
	}
}

ExactSubgraph::ExactSubgraph(std::vector<std::vector<int>> g1, std::vector<std::vector<int>> g2)
{
	graph1 = g1;
	graph2 = g2;
}

int ExactSubgraph::_count = 0;

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
	for (int i = 1; i <= size; i++) {
		std::vector<std::vector<int>> appendCombinations = comb(size, i);
		ret.insert(ret.end(), appendCombinations.begin(), appendCombinations.end());
	}
	return ret;
}

std::vector<std::pair<std::vector<int>, std::vector<int> > > ExactSubgraph::getPermutationsOfSize(int size) {
	// (cols, rows)
	std::vector<std::pair<std::vector<int>, std::vector<int> > > ret;
	
	std::vector<int> numbers;
	std::vector<std::vector<int>> perms;
	for (int i = 0; i < size; i++) {
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
		ret.push_back(std::make_pair(perms[i], perms[i]));
	}

	return ret;
}

std::vector<std::vector<int>> ExactSubgraph::generateReorderedGraph(std::pair<std::vector<int>, std::vector<int> > ordering, std::vector<std::vector<int>> G) {
	// of the First graph
	// reorder columns
	std::vector<std::vector<int>> reorderedColumns;
	for (int i = 0; i < G.size(); i++) {
		std::vector<int> row;
		for (int j = 0; j < ordering.first.size(); j++) {
			row.push_back(G[i][ordering.first[j]]);
		}
		reorderedColumns.push_back(row);
	}
	// reorder rows
	std::vector<std::vector<int>> reorderedMatrix;
	for (int i = 0; i < G.size(); i++) {
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

int ExactSubgraph::compareOverlayGraphs(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG) {
	int count = 0;
	// return -1 if they do NOT overlap
	for (int i = 0; i < smallG.size(); i++) {
		for (int j = 0; j < smallG.size(); j++) {
			if (smallG[i][j] != bigG[i][j]) {
				//_count++;
				return -1;
			}
			else if (smallG[i][j] == 1) {
				count++;
			}
		}
	}

	return count;
}

// return -1 if small graph do not overlap on the bigger one
// return number of edges of the smaller graph otherwise
int ExactSubgraph::compareOverlayGraphsForSupergraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG) {
	int count = 0;
	for (int i = 0; i < smallG.size(); i++) {
		for (int j = 0; j < smallG.size(); j++) {
			if (smallG[i][j] != bigG[i][j]) {
				/*// we are missing an edge in the bigger graph
				if (smallG[i][j] == 1) {
					count++; // add that edge
				}
				// we are missing an edge in the smaller graph
				else {
					return -1; // supergraph candidate refused since smaller graph is not contained in the bigger one
				}*/
				count++; // add that edge
			}
		}
	}

	return count;
}

std::vector<std::vector<int>> ExactSubgraph::generateSuperGraph(std::vector<std::vector<int>> bigG, std::vector<std::vector<int>> smallG) {
	std::vector<std::vector<int>> ret = bigG;

	for (int i = 0; i < smallG.size(); i++) {
		for (int j = 0; j < smallG.size(); j++) {
			if (smallG[i][j] != bigG[i][j]) {
				if (smallG[i][j] == 1) {
					ret[i][j] = 1;
				}
			}
		}
	}
	return ret;
}

void printGraph(std::vector<std::vector<int>> G) {
	for (int i = 0; i < G.size(); i++) {
		for (int j = 0; j < G[i].size(); j++) {
			std::cout << G[i][j] << " ";
		}
		std::cout << "\n";
	}
}

// main function of the whole exact algorithm
void ExactSubgraph::generateMaximalCommonSubgraph() {
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

	//printGraph(graph1);
	//printGraph(graph2);

	int maxNumberOfEdges = -1;  // for maximal subgraph
	int minNumberOfEdgesForSupergraph = std::numeric_limits<int>::max();  // for minimal supergraph

	std::vector<std::vector<int>> setOfAllVerticesCandidates = getPerms(graph2.size());
	auto permutationsOfBiggerGraph = getPermutationsOfSize(graph1.size());

	for (auto permOfBiggerGraph : permutationsOfBiggerGraph) {
		auto reorderedGraph = generateReorderedGraph(permOfBiggerGraph, graph1);

		//std::vector<std::vector<int>> setOfAllVerticesCandidates = getPerms(graph2.size());
		for (std::vector<int> verticesOfSmallerGraph : setOfAllVerticesCandidates) {
			auto smallGraphCandidate = generateCandidate(graph2, verticesOfSmallerGraph);
			int numOfEdges = compareOverlayGraphs(reorderedGraph, smallGraphCandidate);

			if (numOfEdges > maxNumberOfEdges) {
				maxNumberOfEdges = numOfEdges;
				maximalCommonSubgraph = smallGraphCandidate;
			}

			// compute minimal Supergraph
			if (smallGraphCandidate.size() == graph2.size()) {
				int numberOfEdgesForSupergraph = compareOverlayGraphsForSupergraph(reorderedGraph, smallGraphCandidate);

				if (numberOfEdgesForSupergraph >= 0 && numberOfEdgesForSupergraph < minNumberOfEdgesForSupergraph) {
					minNumberOfEdgesForSupergraph = numberOfEdgesForSupergraph;
					minimalSupergraph = generateSuperGraph(reorderedGraph, smallGraphCandidate);
				}

				/*if (graph1.size() == graph2.size()) {
					int numberOfEdgesForSupergraphReverse = compareOverlayGraphsForSupergraph(smallGraphCandidate, reorderedGraph);

					if (numberOfEdgesForSupergraphReverse >= 0 && numberOfEdgesForSupergraphReverse < minNumberOfEdgesForSupergraph) {
						minNumberOfEdgesForSupergraph = numberOfEdgesForSupergraphReverse;
						minimalSupergraph = generateSuperGraph(smallGraphCandidate, reorderedGraph);
					}
				}*/
			}
		}
	}

	if (graph2.size() == 0) {
		minimalSupergraph = graph1;
	}

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