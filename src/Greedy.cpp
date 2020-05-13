#include <vector>
#include <cstdlib>

using namespace std;

int startPoint(int total) {
    int side = (rand()%2) ? 1 : -1; // local or visit
    int opponent = (rand()%(total-1))+2;

    return opponent*side;
}

vector<vector<int>> Greedy(vector<vector<int>> distances){
    int total = distances.size();
    vector<vector<int>> solution(2*(total - 1), vector<int>(total));
    int opponent;

    // define start point
    int point = startPoint(total);
    opponent = abs(point) - 1;

    solution[0][0] = point;
    solution[0][opponent] = point > 0 ? -1 : 1;

    

    return solution;
}