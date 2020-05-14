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
    } else {
        game.local = opponent;
        game.visit = 1;
    }
    return game;
}

/**
 * add teams to the list and eliminate from free
*/
void addToSolution(int row, Game game, GreedyTournament &tournament, vector<int> &freeTeams) {
    int local = game.local - 1;
    int visit = game.visit -1;
    // add to tournament
    tournament.schedule[row][local] = game.visit * -1;
    tournament.schedule[row][visit] = game.local;
    // "eliminate" from free teams
    freeTeams[local] = -1;
    freeTeams[visit] = -1;
    // update lastRival list
    tournament.lastRival[local] = game.visit * -1;
    tournament.lastRival[visit] = game.local;
    // update trip list
    // if local is in a visit trip reset, else add 1
    if (tournament.trip[local] < 0) tournament.trip[local] = 1;
    else tournament.trip[local]++; 
    // if visit is in a home stand reset, else rest 1
    if (tournament.trip[visit] > 0) tournament.trip[visit] = -1;
    else tournament.trip[visit]--; 
}

/**
 * from a team, see the near teams and select the option that accept: 
 * -) a team cant play more than 3 games in a row local or visit
 * -) if a team is visit and the next game is visit,
 * the distance is between this two cities
 * -) cant play versus the same team in two continuos rows
*/
Game selectRival(int team, vector<int> freeTeams, vector<vector<int>> distances, GreedyTournament &tournament){
    Game game;
    int lastGame = tournament.lastRival[team];
    
    vector<int> priorityList; // list of posible movements
    vector<int> priorityValues; // list of value of the movement

    if (lastGame < 0 && tournament.trip[team] > -3) { // team can play as visit
        lastGame = abs(lastGame) - 1;
        // find rival considering team is in other city
        for(long unsigned int i = 0; i < distances[lastGame].size(); i++) {
            if ((int) i != lastGame && freeTeams[i] != -1){ // check if the team is free and is not the actual team
                // add team to the list in order
                vector<int>::iterator j;
                for (j = priorityValues.begin(); j != priorityValues.end(); j++) {
                    if (distances[lastGame][i] < *j) break;
                }
                priorityList.insert(j, i*-1); // TODO CHECK THIS
                priorityValues.insert(j, distances[lastGame][i]);
            }
        }
    }

    for (auto &&i : priorityList) cout << i << " ";
    cout << endl;
    for (auto &&i : priorityValues) cout << i << " ";
    cout << endl;

    if (lastGame >= 0 && tournament.trip[team] < 3) { // team can play as local
        for(int &city : freeTeams) { // add the other freeTeams
            if (city != -1 && city - 1 != team) {
                priorityValues.push_back(0);
                priorityList.push_back(-1 * (city - 1));
            }
        }
    }
    
    // for (auto &&i : priorityList) cout << i << " ";
    // cout << endl;
    // for (auto &&i : priorityValues) cout << i << " ";
    // cout << endl;



    // if move to home is the best movement, select a random team
    return game;
}

/**
 * Auxiliar function to make recursion
*/
void NGreedy(int row, GreedyTournament &tournament, vector<vector<int>> distances){
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
        addToSolution(row, game, tournament, freeTeams);
    }

    // add games to the row
    for (long unsigned int i = 0; i < freeTeams.size(); i++) { // move between free teams
        if (freeTeams[i] != -1) { // a team that is not selected in this row
            game = selectRival(i, freeTeams, distances, tournament);
            addToSolution(row, game, tournament, freeTeams);
        }
    }

    // move to the next row
    NGreedy(row+1, tournament, distances);
}

vector<vector<int>> Greedy(vector<vector<int>> distances){
    total = distances.size();
    GreedyTournament tournament;
    // solution is going to be a matrix
    tournament.schedule = vector<vector<int>>(2*(total - 1), vector<int>(total));
    tournament.trip = vector<int>(total);
    tournament.lastRival = vector<int>(total);

    NGreedy(0, tournament, distances);

    return tournament.schedule;
}