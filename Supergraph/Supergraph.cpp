// Supergraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <direct.h>
#include "ApproximateMaximalSubgraph.h"
#include "ApproximateMinimalSupergraph.h"
#include "ExactMaximalSubgraph.h"
#include "twoGraphs.h"

int main(int argc, char* argv[])
{
    /*ApproximateMaximalSubgraph maximalSubgraph;
    maximalSubgraph.getMaximalCommonSubgraph();
    maximalSubgraph.printMaximalCommonSubgraph();
    ApproximateMinimalSupergraph minimalSupergraph(maximalSubgraph);
    minimalSupergraph.getMinimalCommonSupergraph();
    minimalSupergraph.printMinimalCommonSupergraph();
    std::cout << minimalSupergraph.approx.graph1.size() << "\n";*/

    //std::cout << "-------------twoGraphs solution-----------\n";

    char buff[256];
    _getcwd(buff, 256);
    std::string current_working_dir(buff);  // not used yet

    twoGraphs solution = twoGraphs("graphs/input2.txt");
    solution.computeApproximateSolution();
    solution.computeExactSolution();
    solution.printSolution();

    //ExactSubgraph exact;
    //exact.generateMaximalCommonSubgraph();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
