#include <vector>

using namespace std;

struct Game {
    int local;
    int visit;
};

struct GreedyTournament {
    vector<int> lastRival; // negative is because the rival is visit
    vector<int> trip; // positive = local, negative = visit
    vector<vector<int>> schedule; // a solution
};
