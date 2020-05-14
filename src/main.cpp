#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "./Greedy.cpp"
#include "./Auxiliar.cpp"

using namespace std;

int n;
int seed;

int readInput(int argc, char **argv){ 
    seed = atoi(argv[1]);
    n = atoi(argv[2]);

    return 1;
}

int main(int argc, char *argv[]){
    readInput(argc, argv);

    vector<vector<int>> distances(n, vector<int>(n));
    vector<vector<int>> solution;

    // read input matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distances[i][j];
        }
    }

    // define seed
    srand(seed);

    // give matrix to the algorithm
    solution = Greedy(distances);
    
    //show solution
    showSolution(solution);
    return 0;
}
