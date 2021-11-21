// Supergraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <direct.h>
#include <chrono>
#include "ApproximateMaximalSubgraph.h"
#include "ApproximateMinimalSupergraph.h"
#include "ExactMaximalSubgraph.h"
#include "twoGraphs.h"
#include "GraphGenerator.h"

void generateAndWrite(int numberOfGraphs, int n1, int n2, int density1, int density2) {
    GraphGenerator generator;
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> graphs;

    for (int i = 0; i < numberOfGraphs; i++) {
        graphs = generator.generateGraphs(n1, n2, density1, density2);
        generator.writeGraphsToFile(graphs,
            "gen_" +
            std::to_string(n1) + "-" +
            std::to_string(n2) + "-" +
            std::to_string(density1) + "-" +
            std::to_string(density2) + "__" +
            std::to_string(i) + ".txt");
    }
}

using namespace std::chrono;

int main(int argc, char* argv[])
{
    generateAndWrite(1, 9, 6, 40, 40);
    //generateAndWrite(100, 40, 20, 40, 40);
    //generateAndWrite(100, 60, 30, 40, 40);
    //generateAndWrite(100, 80, 40, 40, 40);
    //generateAndWrite(100, 100, 50, 40, 40);
    std::string base_path = "Examples/";
    std::string filename;
    //std::cout << "Enter the name of the input file, e.g. name.txt" << std::endl;
    //std::cin >> filename;
    //filename = base_path + filename;
    //twoGraphs solution = twoGraphs(filename);

    //std::cout << "-------------twoGraphs solution-----------\n";

    char buff[256];
    _getcwd(buff, 256);
    std::string current_working_dir(buff);  // not used yet

    //auto start = high_resolution_clock::now();

    twoGraphs solution = twoGraphs("Examples/input5.txt");
    solution.computeApproximateSolution();
    solution.computeExactSolution();
    solution.printSolution();

    std::system("pause");
    /*auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken by function: " << (double)duration.count()/1000000 << " seconds\n";*/

    //ExactSubgraph exact;
    //exact.generateMaximalCommonSubgraph();

}

// Supergraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*#include <iostream>
#include "ApproximateMaximalSubgraph.h"
#include "ApproximateMinimalSupergraph.h"
#include "ExactMaximalSubgraph.h"
#include "twoGraphs.h"

void main(void)
{
    std::string base_path = "./../Examples/";
    std::string filename;
    std::cout << "Enter the name of the input file, e.g. name.txt" << std::endl;
    std::cin >> filename;
    filename = base_path + filename;
    twoGraphs solution = twoGraphs(filename);
    solution.computeApproximateSolution();
    solution.computeExactSolution();
    solution.printSolution();

    std::system("pause");

}*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu