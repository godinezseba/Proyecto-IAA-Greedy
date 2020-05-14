#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>
#include "./Entities/Tournament.h"

using namespace std;

int total;
/**
 * Select random rival to the first team
 * in the first date
 * also is random who is local and who is visit
*/
Game startPoint() {
    Game game;
    int opponent = (rand()%(total-1))+2;
    // select local or visit
    if ((rand()%2)) {
        game.local = 1;
        game.visit = opponent;
    }
    else {
        game.local = opponent;
        game.visit = 1;
    }
    return game;
}

/**
 * from a team, see the near teams and select the best option 
 * -) a team cant play more than 3 games in a row local or visit
 * -) if a team is visit and the next game is visit,
 * the distance is between this two cities
 * -) cant play versus the same team in two continuos rows
*/
Game selectRival(int team, vector<int> freeTeams, vector<vector<int>> distances, vector<vector<int>> solution){
    Game game;
    game.local = team;
    game.visit = team;

    return game;
}

/**
 * add teams to the list and eliminate from free
*/
void addToSolution(int row, Game game, vector<vector<int>> &solution, vector<int> &freeTeams) {
    solution[row][game.local-1] = game.visit * -1;
    solution[row][game.visit-1] = game.local;
    freeTeams[game.local-1] = -1;
    freeTeams[game.visit-1] = -1;
}

/**
 * Auxiliar function to make recursion
*/

void NGreedy(int row, vector<vector<int>> &solution, vector<vector<int>> distances){
    if (row == total) return; // stop condition
    // just a auxiliar game
    Game game;
    // list of not selected teams
    vector<int> freeTeams(total); // -1 = team is selected
    iota(freeTeams.begin(), freeTeams.end(), 1);

    // 1.- Iteration for the first row
    if (row == 0){
        // define start point
        game = startPoint();
        // add teams to solution, and eliminate from free teams
        addToSolution(0, game, solution, freeTeams);
    }

    for (long unsigned int i = 0; i < freeTeams.size(); i++) {
        if (freeTeams[i] != -1) { // a team that is not selected in this row
            game = selectRival(i, freeTeams, distances, solution);
        }
    }
}

vector<vector<int>> Greedy(vector<vector<int>> distances){
    total = distances.size();
    // solution is going to be a matrix
    vector<vector<int>> solution(2*(total - 1), vector<int>(total));

    NGreedy(0, solution, distances);

    return solution;
}