#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "./Greedy.cpp"
#include "./Auxiliar.cpp"

using namespace std;

int main(int argc, char const *argv[]){
    int total = 4;
    vector<vector<int>> distances(total, vector<int>(total));
    vector<vector<int>> solution;

    // read input matrix
    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
            cin >> distances[i][j];
        }
    }

    // define seed
    srand(time(NULL));

    // give matrix to the algorithm
    solution = Greedy(distances);
    
    //show solution
    showSolution(solution);
    return 0;
}
