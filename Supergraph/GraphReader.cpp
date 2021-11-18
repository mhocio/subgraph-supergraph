#include "GraphReader.h"
#include <vector>
#include <string>
#include <fstream>

GraphReader::GraphReader() {

}

std::vector<std::vector<int> > GraphReader::createGraphFromFile(const char* filename) {
	std::ifstream file(filename);
	std::vector<std::vector<int> > matrix;
	std::vector<int> row;
	int vertices;

	if (file.is_open()) {
		std::string line;
		std::getline(file, line);
		// not used at the moment
		vertices = stoi(line);

		while (std::getline(file, line)) {
			std::vector<int> row;

			for (char& c : line) {
				if (c != ' ') {
					row.push_back(atoi(&c));
				}
			}

			matrix.push_back(row);
		}
		
		file.close();

	return matrix;

	}

}