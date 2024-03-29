#include <vector>
#include <string>

class GraphGenerator
{
public:
	GraphGenerator();
	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> generateGraphs(int n1, int n2, int density1, int density2);
	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> generateIsomorphicGraphs(int n, int density);
	void writeGraphsToFile(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> input, std::string filename, std::string relativePath = "Examples/");
};
