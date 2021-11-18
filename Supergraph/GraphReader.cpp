#include "GraphReader.h"
#include <vector>
#include <string>
#include <fstream>

GraphReader::GraphReader() {

}

std::vector<std::vector<int> > GraphReader::createGraphFromFile(const char* filename) {
	std::ifstream file(filename);
	std::vector<std::vector<int> > matrix;
	int a, b;
	int vertices;

	if (file.is_open()) {
		std::string line;
		std::getline(file, line);
		vertices = stoi(line);

		std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices));  // initializing to zero
		while (file >> a >> b) {
			matrix[a][b] = 1;
			matrix[b][a] = 1;

		}
		file.close();
	return matrix;
	}

}