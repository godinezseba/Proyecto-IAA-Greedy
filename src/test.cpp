#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> test(10);

    for (auto i = test.begin(); i != test.end(); ++i) 
        cout << *i << " "; 
    return 0;
}
