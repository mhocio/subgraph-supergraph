#include "GraphReader.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

GraphReader::GraphReader() {}

int GraphReader::readInput(const char* filename) {
	std::ifstream file(filename);
	int vertices;

	if (file.is_open()) {

		try
		{
			std::string line;

			for (int i = 0; i < 2; ++i) {
				std::vector<std::vector<int> > matrix;
				// not used at the moment
				std::getline(file, line);
				vertices = stoi(line);

				for (int j = 0; j < vertices; j++) {
					std::vector<int> row;
					std::string lineEdges;

					if (file.eof()) {
						std::cout << "File is wrongly constructed: not enough rows in graph.\n";
						throw std::invalid_argument("File is wrongly constructed");
					}

					std::getline(file, lineEdges);
					int countLine = 0;
					for (char& c : lineEdges) {
						if (c != ' ' && c != '1' && c != '0') {
							std::cout << "File is wrongly constructed: wrong character.\n";
							throw std::invalid_argument("File is wrongly constructed");
						}
						if (c != ' ') {
							row.push_back(atoi(&c));
							countLine++;
						}
					}

					if (countLine != vertices) {
						std::cout << "File is wrongly constructed: not enough vertices in line.\n";
						throw std::invalid_argument("File is wrongly constructed");
					}

					matrix.push_back(row);
				}

				if (matrix.size() != vertices) {
					std::cout << "File is wrongly constructed: not enough rows in graph.\n";
					throw std::invalid_argument("File is wrongly constructed");
				}

				if (i == 0)
					graph1 = matrix;
				else
					graph2 = matrix;
			}

			file.close();
		}
		catch (const std::exception& ex)
		{
			std::cout << "Could not read the file\n";
			file.close();
			return 1;
		}

	} else {
		// file not opened
		std::cout << "Could not open the file\n";
		return 1;
	}
	return 0;
}