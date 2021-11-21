// Supergraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <direct.h>
#include <chrono>
#include <stdlib.h>
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

void gen() {
    generateAndWrite(1, 10, 6, 42, 60);
    //generateAndWrite(100, 40, 20, 40, 40);
    //generateAndWrite(100, 60, 30, 40, 40);
    //generateAndWrite(100, 80, 40, 40, 40);
    //generateAndWrite(100, 100, 50, 40, 40);
    std::string base_path = "Examples/";
    std::string filename;
}

void menu() {
    //std::cout << "Enter the name of the input file, e.g. name.txt" << std::endl;
    //std::cin >> filename;
    //filename = base_path + filename;
    //twoGraphs solution = twoGraphs(filename);

    //twoGraphs solution = twoGraphs("Examples/input5.txt");
    twoGraphs solution = twoGraphs("Examples/input3.txt");
    solution.computeApproximateSolution();
    solution.computeExactSolution();
    solution.printSolution();

    std::system("pause");
}

void program() {
    bool loop = true;
    while (loop) {
        system("CLS");  // clear terminal

        std::string base_path = "Examples/";
        std::string filename;
        std::cout << "Enter the name of the input file, e.g. name.txt" << std::endl;
        std::cin >> filename;
        filename = base_path + filename;
        twoGraphs solution = twoGraphs(filename);

        if (solution.initialized()) {
            solution.computeApproximateSolution();
            solution.computeExactSolution();
            solution.printSolution();
        }
        else {
            std::cout << "Could not read the file.\n";
        }

        std::cout << "Do you want to test another graph? Type yes or y if so. ";
        std::string ans;
        std::cin >> ans;
        if (ans != "yes" && ans != "y") {
            loop = false;
        }
    }

    std::system("pause");
}

int main(int argc, char* argv[])
{
    //gen();
    program();
    //menu();
}

/*
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

/*
char buff[256];
_getcwd(buff, 256);
std::string current_working_dir(buff);  // not used yet*/