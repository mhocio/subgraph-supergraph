#include <vector>
#include <string>

class GraphGenerator
{
public:
	GraphGenerator();
	std::pair<std::vector<std::vector<unsigned __int8>>, std::vector<std::vector<unsigned __int8>>> generateGraphs(int n1, int n2, int density1, int density2);
	void writeGraphsToFile(std::pair<std::vector<std::vector<unsigned __int8>>, std::vector<std::vector<unsigned __int8>>> input, std::string filename);

};
