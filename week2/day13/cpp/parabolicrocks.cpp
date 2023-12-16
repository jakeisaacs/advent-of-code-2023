#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

int main () {
    ifstream f("../input.txt");
    string line;
    vector<string> platform;

    while(f.is_open() && getline(f, line)) {
        platform.push_back(line);
    }

    const int N = platform.size(), M = platform[0].length();
    vector<int> minpos(M, 0);
    int sum = 0;

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            // cout << platform[i][j] << " ";
            if(platform[i][j] == 'O') {
                sum += N - minpos[j];
                minpos[j]++;
            } else if (platform[i][j] == '#') {
                minpos[j] = i + 1;
            }
        }
        // cout << endl;
    }

    cout << "Total sum: " << sum << endl;
}