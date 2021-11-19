#include "GraphReader.h"
#include <vector>
#include <string>
#include <fstream>

GraphReader::GraphReader() {}

int GraphReader::readInput(const char* filename) {
	std::ifstream file(filename);
	int vertices;

	if (file.is_open()) {
		std::string line;

		for (int i = 0; i < 2; ++i) {
			std::vector<std::vector<int> > matrix;
			// not used at the moment
			std::getline(file, line);
			vertices = stoi(line);

			for (int j = 0; j < vertices; j++) {
				std::vector<int> row;
				std::getline(file, line);
				for (char& c : line) {
					if (c != ' ') {
						row.push_back(atoi(&c));
					}
				}

				matrix.push_back(row);

			}
			if (i == 0)
				graph1 = matrix;
			else 
				graph2 = matrix;
		}
		
		file.close();

	}
	return 0;
}