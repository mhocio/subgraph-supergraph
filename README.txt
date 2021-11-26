# subgraph-supergraph

Supervisor:
prof. Władysław Homenda

Authors:
Radosław Dubiel
Mikołaj Hościło 
Antoni Karpiński

The program computes and displays maximal common subgraph and minimal common supergraph, 
using both approximate and exact algorithms. The description of the algorithms is contained in the Doc folder.

Upon starting the program the user has 3 modes of operating with the program:
1. entering the name of the file, which is contained in the Examples folder and type of algorithm which user wants to run(1 is both, 2 is only exact, 3 is only approximate). Users    can create theirs own graphs, following the format of example inputs e.g. input1.txt 1 
2. generating 2 random graphs, by passing, respectively, number of vertices of the first graph, number of vertices of the second graph, 
   density (percentage of vertices connected by edges) of the first graph, density of the second graph, and a digit (1 - compute using both algortihms,
   2 - compute using approximate algorithm only; 3 - compute using exact algorithm only), e.g. 10 5 70 70 1   
3. display all predefined and pregenerated input files which can be used in the first option later

First and second cases validate input given by the user.
