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

using std::filesystem::directory_iterator;

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

void generateIsomorphicAndWrite(int numberOfGraphs, int n, int density) {
    GraphGenerator generator;
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> graphs;

    for (int i = 0; i < numberOfGraphs; i++) {
        graphs = generator.generateIsomorphicGraphs(n, density);
        generator.writeGraphsToFile(graphs,
            "iso_" +
            std::to_string(n) + "_" +
            std::to_string(density) + ".txt");
    }
}

void genSeveralIsomorphicAndWrite() {
    for (int i = 3; i <= 10; i++) {
        generateIsomorphicAndWrite(1, i, 50);
    }

    for (int i = 20; i <= 150; i+=10) {
        generateIsomorphicAndWrite(1, i, 50);
    }
}

using namespace std::chrono;

void gen() {
    //generateIsomorphicAndWrite(5, 6, 60);
    //generateAndWrite(1, 10, 6, 42, 60);
    //generateAndWrite(100, 40, 20, 40, 40);
    //generateAndWrite(100, 60, 30, 40, 40);
    //generateAndWrite(100, 80, 40, 40, 40);
    //generateAndWrite(100, 100, 50, 40, 40);
    genSeveralIsomorphicAndWrite();
    std::string base_path = "Examples/";
    std::string filename;
}

void simpleCaseFromFile() {
    twoGraphs solution = twoGraphs("Examples/input3.txt");
    solution.computeApproximateSolution();
    solution.computeExactSolution();
    solution.printSolution();

    std::system("pause");
}

std::string toLower(std::string data) {
    std::for_each(data.begin(), data.end(), [](char& c) {
        c = ::tolower(c);
        });
    return data;
}

bool is_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool startswith(const std::string& str, const std::string& cmp="yes")
{
    return cmp.compare(0, str.length(), str) == 0;
}

bool runSingleSolution(twoGraphs solution, std::string algo) {
    bool loop = true;
    bool correctInput = true;

    if (algo != "1" && algo != "2" && algo != "3") {
        std::cout << "Wrong algorithm type. Remember to choose number between 1 and 3\n ex.: input1.txt 3\n";
        correctInput = false;
    }

    if (algo == "1" || algo == "2") {
        if (solution.graph1.size() >= 8) {
            if (solution.graph1.size() == 8) {
                std::cout << "Attention. Exact algorithm might take several seconds to compute\n";
            }
            if (solution.graph1.size() == 9) {
                std::cout << "Attention. Exact algorithm might take over a minute to compute\n";
            }
            if (solution.graph1.size() == 10) {
                std::cout << "Attention. Exact algorithm might take over 10mins to compute\n";
            }
            if (solution.graph1.size() > 10) {
                std::cout << "Attention. Exact algorithm might take A LOT (hours?) to compute\n";
            }
            std::cout << "Do you still want to compute exact solution? y/n\n";
            std::string exact;
            std::cin >> exact;
            if (!startswith(toLower(exact))) {
                if (algo == "1") {
                    algo = "3";
                }
                else {
                    correctInput = false;
                }
            }
        }
    }

    if (solution.initialized() && correctInput) {
        if (algo == "1" || algo == "3")
            solution.computeApproximateSolution();
        if (algo == "1" || algo == "2")
            solution.computeExactSolution();
        solution.printSolutionNice();

        //solution.printSeveralGraphsInOneLine({ {solution.graph2, "graph2"} , {solution.graph1, "graph1"}, {solution.graph2, "graph2"} });
    }
    else {
        std::cout << "Error with the input.\n";
    }

    std::cout << "Do you want to test another graph? Type yes or y if so. ";
    std::string ans;
    std::cin >> ans;

    if (!startswith(toLower(ans))) {
        loop = false;
    }

    return loop;
}

void case1() {
    bool loop = true;
    while (loop) {
        system("CLS");  // clear terminal

        std::string base_path = "Examples/";
        std::string filename;
        std::string algo;
        std::cout << "Enter the name of the input file and 1 or 2 or 3 after space for\\
            \n1)both algorithms\n2)only exact algorithms\n3)only approximate algorithms\nExample: C4P2C3_bull.txt 2" << std::endl;
        std::cin >> filename >> algo;
        filename = base_path + filename;
        twoGraphs solution = twoGraphs(filename);

        loop = runSingleSolution(solution, algo);
    }
}

void case2() {
    bool loop = true;
    while (loop) {
        system("CLS");  // clear terminal

        GraphGenerator generator;
        std::string N, M, d1, d2, algo;

        std::cout << "Enter size of first graph. size of second graph,\ndensity of first graph (from 0 to 100),\\
 density of second graph(from 0 to 100) and number from 1 to 3:\\
            \n1)both algorithms\n2)only exact algorithms\n3)only approximate algorithms\nExample: 7 5 50 60 1" << std::endl;

        std::cin >> N >> M >> d1 >> d2 >> algo;

        if (!is_number(N) || !is_number(M) || !is_number(d1) || !is_number(d2) || !is_number(algo)) {
            std::cout << "Wrong input! (some parameter is not integer)\n";
            twoGraphs solution({ {{}}, {{}} });
            solution.readFromFfile = false;
            loop = runSingleSolution(solution, algo);
        }
        else {
            auto graphs = generator.generateGraphs(std::stoi(N), std::stoi(M), std::stoi(d1), std::stoi(d2));
            twoGraphs solution = twoGraphs(graphs);
            loop = runSingleSolution(solution, algo);
        }
    }
}

void case3() {
    bool loop = true;
    while (loop) {
        system("CLS");  // clear terminal

        GraphGenerator generator;
        std::string N, d, algo;

        std::cout << "Enter size of graphs, their density (from 0 to 100) and number from 1 to 3:\\
            \n1)both algorithms\n2)only exact algorithms\n3)only approximate algorithms\nExample: 7 50 1" << std::endl;

        std::cin >> N >> d >> algo;

        if (!is_number(N) || !is_number(d) || !is_number(algo)) {
            std::cout << "Wrong input! (some parameter is not integer)\n";
            twoGraphs solution({ {{}}, {{}} });
            solution.readFromFfile = false;
            loop = runSingleSolution(solution, algo);
        }
        else {
            auto graphs = generator.generateIsomorphicGraphs(std::stoi(N), std::stoi(d));
            twoGraphs solution = twoGraphs(graphs);
            loop = runSingleSolution(solution, algo);
        }
    }
}

void case4() {
    std::cout << "Graphs which can be used (in the Examples folder):\n";
    std::string path = "Examples/";

    for (const auto& file : directory_iterator(path)) {
        if (!file.is_directory())
            std::cout << file.path().filename() << "\n";
    }

    std::system("pause");
}

void program() {
    bool loop = true;

    while (loop) {
        system("CLS");  // clear terminal
        std::cout << "Choose one of the above options\n";
        std::cout << "1. Run program on the input file\n";
        std::cout << "2. Run program on randomly generated graphs with chosen parameters\n";
        std::cout << "3. Run program on randomly generated isomorphic graphs with chosen parameters\n";
        std::cout << "4. Print graphs from our Example folder\n";
        std::cout << "0. Exit\n";
        std::string input;
        std::cin >> input;

        if (!is_number(input)) {
            continue;
        }

        switch (std::stoi(input))
        {
        case 1:
            case1();
            break;
        case 2:
            case2();
            break;
        case 3:
            case3();
            break;
        case 4:
            case4();
            break;
        case 0:
            loop = false;
            break;
        default:
            break;
        }
    }
    std::system("pause");
}

void perfTest1() {
    // This is a test for the exact algorithm.
    GraphGenerator generator;
    std::vector<int> densities = { 20, 50, 80 };
    std::vector<int> sizes = {3, 4, 5, 6};
    const int iter = 10;
    std::cout << "--------------------EXACT ALGORITHM--------------------" << "\n";
    // Part 1: two graphs of the same size and the same density.
    for (int size: sizes) {
        for (int density : densities) {
            double result = 0.0;
            for (int i = 0; i < iter; ++i) {
                twoGraphs solution(generator.generateGraphs(size, size, density, density));
                solution.computeExactSolution();
                result += solution.exactSolutionTime;
            }
            result /= (double)iter;
            
            std::cout << "SIZE_1 = " << size << " SIZE_2 = " << size << " DENSITY_1 = " << density << " DENSITY_2 = " << density << "\n";
            std::cout << "AVG_TIME = " << result << "\n\n";
        }
    }
    // Part 2: two graphs of the different sizes and of the different densities.
    for (int i = 2; i < sizes.size(); ++i) {
        for (int j = 1; j < densities.size(); ++j) {
            double result = 0.0;
            for (int k = 0; k < iter; ++k) {
                twoGraphs solution(generator.generateGraphs(sizes[i], sizes[i - 2], densities[j], densities[j - 1]));
                solution.computeExactSolution();
                result += solution.exactSolutionTime;
            }
            result /= (double)iter;
            std::cout << "SIZE_1 = " << sizes[i] << " SIZE_2 = " << sizes[i - 2] << " DENSITY_1 = " << densities[j] << " DENSITY_2 = " << densities[j - 1] << "\n";
            std::cout << "AVG_TIME = " << result << "\n\n";
        }
    }
}

void perfTest2() {
    // This is a test for the approximate algorithm.
    GraphGenerator generator;
    std::vector<int> densities = { 20, 50, 80 };
    std::vector<int> sizes = { 10, 30, 50, 70, 90 };
    const int iter = 10;
    std::cout << "--------------------APPROXIMATE ALGORITHM--------------------" << "\n";
    // Part 1: two graphs of the same size and the same density.
    for (int size : sizes) {
        for (int density : densities) {
            double result = 0.0;
            for (int i = 0; i < iter; ++i) {
                twoGraphs solution(generator.generateGraphs(size, size, density, density));
                solution.computeApproximateSolution();
                result += solution.approximateSolutionTime;
            }
            result /= (double)iter;
            std::cout << "SIZE_1 = " << size << " SIZE_2 = " << size << " DENSITY_1 = " << density << " DENSITY_2 = " << density << "\n";
            std::cout << "AVG_TIME = " << result << "\n\n";
        }
    }
    // Part 2: two graphs of the different sizes and of the different densities.
    for (int i = 2; i < sizes.size(); ++i) {
        for (int j = 1; j < densities.size(); ++j) {
            double result = 0.0;
            for (int k = 0; k < iter; ++k) {
                twoGraphs solution(generator.generateGraphs(sizes[i], sizes[i - 2], densities[j], densities[j - 1]));
                solution.computeApproximateSolution();
                result += solution.approximateSolutionTime;
            }
            result /= (double)iter;
            std::cout << "SIZE_1 = " << sizes[i] << " SIZE_2 = " << sizes[i - 2] << " DENSITY_1 = " << densities[j] << " DENSITY_2 = " << densities[j - 1] << "\n";
            std::cout << "AVG_TIME = " << result << "\n\n";
        }
    }
}

void perfTests(bool writeToFile=false, bool computeAlgorithms=true) {
    GraphGenerator generator;

    int iterations = 10;
    std::vector<int> sizes;
    std::vector<int> densities = { 20, 50, 80 };
    bool computeExact = true;
    int EXACT_N_TRESHHOLD = 8;

    for (int i = 8; i < 10; i++) {
        sizes.push_back(i);
    }
    for (int i = 10; i <= 190; i += 10) {
        sizes.push_back(i);
    }

    for (int size : sizes) {
        for (int i = 1; i < densities.size(); i++) {
            int N = size;
            int M = ceil(double(size) / 2);
            int d1 = densities[i];
            int d2 = densities[i - 1];

            for (int w = 0; w < 4; w++) {
                double resultApprox = 0.0;
                double resultExact = 0.0;
                if (w == 0) {
                    M = ceil(double(size) / 3);
                }
                else if (w == 1) {
                    M = ceil(double(size) / 2);
                }
                else if (w == 2) {
                    M = ceil(double(size) / 3*2);
                }
                else if (w == 3) {
                    M = N;
                }
                for (int k = 0; k < iterations; k++) {
                    twoGraphs solution(generator.generateGraphs(N, M, d1, d2));
                    if (computeAlgorithms)
                        solution.computeApproximateSolution();
                    resultApprox += solution.approximateSolutionTime;
                    if (N <= EXACT_N_TRESHHOLD && computeExact) {
                        if (computeAlgorithms)
                            solution.computeExactSolution();
                        resultExact += solution.exactSolutionTime;
                    }
                    if (writeToFile)
                    generator.writeGraphsToFile({solution.graph1, solution.graph2}, 
                        "test-" + std::to_string(N) + "-" + std::to_string(M) + "-" + 
                        std::to_string(d1) + "-" + std::to_string(d2) + "_" +
                        std::to_string(k) + ".txt");
                }
                resultApprox /= (double)iterations;
                resultExact /= (double)iterations;
                std::cout << N << ";" << M << ";" << d1 << ";" << d2 << ";" << resultApprox;
                if (N <= EXACT_N_TRESHHOLD && computeExact) {
                    std::cout << ";" << resultExact;
                }
                std::cout << "\n";
            }
            //std::cout << "\n";
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    program();
    //gen();  // generate files
    //perfTests();  // run tests
    //perfTests(true, false);  // generate test graph files to the folder

    return 0;
}
