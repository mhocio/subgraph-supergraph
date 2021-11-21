#include "GraphGenerator.h"
#include <random>
#include <iostream>
#include <fstream>

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>> graph) {
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			out << graph[i][j];
			if (j < graph.size() - 1) {
				out << " ";
			}
		}
		out << std::endl;
	}
	return out;
}

GraphGenerator::GraphGenerator() {

}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> GraphGenerator::generateGraphs(int n1, int n2, int density1, int density2) {
	std::vector<std::vector<int>> graph1(n1, std::vector<int>(n1, 0));
	std::vector<std::vector<int>> graph2(n2, std::vector<int>(n2, 0));
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 100);

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < i; j++) {
			int rand = dis(gen);

			// density should be in percentages
			if (rand < density1 && i != j) {
				graph1[i][j] = 1;
				graph1[j][i] = 1;
			}
		}
	}


	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < i; j++) {
			int rand = dis(gen);

			// density should be in percentages
			if (rand < density2 && i != j) {
				graph2[i][j] = 1;
				graph2[j][i] = 1;
			}
		}
	}

	

	return std::make_pair(graph1, graph2);

}

void GraphGenerator::writeGraphsToFile(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> input, std::string filename) {
	std::string basepath = "Examples/Generated/";
	std::ofstream outfile(basepath + filename);
	outfile << input.first.size() << std::endl << input.first << input.second.size() << std::endl << input.second;

}