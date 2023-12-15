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
    string line, tmp;
    vector<string> records;
    vector<vector<int> > sequences;

    int i = 0;
    while(f.is_open() && getline(f, line)) {
        int splitpos = line.find(' ');
        sequences.push_back(vector<int>());

        records.push_back(line.substr(0, splitpos));
        tmp = line.substr(splitpos+1, line.length() - splitpos - 1);

        for(int j=0;j<tmp.length();j+=2) {
            sequences[i].push_back((tmp[j] - '0'));
            cout << sequences[i][j/2] << " ";
        }
        i++;
        cout << endl;
    }

}