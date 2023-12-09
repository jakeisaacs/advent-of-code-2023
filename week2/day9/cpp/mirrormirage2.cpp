#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

int GetNextVal(vector<int>& v) {
    vector<vector<int> > diffs;
    int diff, indx, i = 1;
    bool allZeroes = false;

    diffs.push_back(v);

    while (!allZeroes) {
        allZeroes = true;
        diffs.push_back(vector<int>());
        for(int j=0;j<diffs[i-1].size()-1;j++) {
            diff = diffs[i-1][j+1] - diffs[i-1][j];
            diffs[i].push_back(diff);
            allZeroes = allZeroes && diff == 0;
        }
        i++;
    }

    const int N = i - 1;

    diffs[N].push_back(0);

    for(i=0;i<N;i++) {
        vector<int> tmp = diffs[i];
        reverse(tmp.begin(), tmp.end());
        diffs[i] = tmp;
    }

    for(i=N;i>0;i--) {
        indx = diffs[i].size()-1;
        diffs[i-1].push_back(diffs[i-1][indx] - diffs[i][indx]); 
    }
    
    return diffs[0][diffs[0].size()-1];
}

int main () {
    ifstream f("../input.txt");
    string line;
    vector<vector<int> > lines;
    string tmp;
    int i, sum = 0;

    i = 0;
    while(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        lines.push_back(vector<int>());
        while (ss >> tmp) {
            lines[i].push_back(stoi(tmp));
        }
        i++;
    }

    const int N = i;

    for (i=0;i<N;i++) {
        sum += GetNextVal(lines[i]);
    }
    
    cout << "Total: " << sum << endl;
}