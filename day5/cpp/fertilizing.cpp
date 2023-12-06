#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<long> > mapVals(fstream& f) {
    string line;
    long src, dest, rlen;
    vector<vector<long> > v;
    int i=0;
    while(f.is_open() && getline(f, line) && !line.empty()) {
        stringstream ss (line);
        ss >> dest;
        ss >> src;
        ss >> rlen;

        v.push_back({src, src+rlen, dest});
        // cout << v[i][0] << endl;
        // i++;
    }

    return v;
}

long checkSeed(long seed, vector<vector<vector<long> > >& m) {
    int i, j;

    i = 0;
    while(i < m.size()) {
        j = 0;
        while (j < m[i].size()) {
            // cout << m[i][j][0] << " " << m[i][j][1] << " " << m[i][j][2] << endl;
            if (seed >= m[i][j][0] && seed < m[i][j][1])
            {
                seed = m[i][j][2] + (seed - m[i][j][0]);
                cout << "START: " << m[i][j][0] << " END: " << m[i][j][1] <<  " Match: " << seed << endl;
                break;
            }
            j++;
        }
        i++;
    }

    cout << endl;
    return seed;
}

int main() {
    fstream f("../input.txt");
    string line, word;
    long tmp, min = LONG_MAX;
    vector<long> seeds;
    vector<vector<vector<long> > > m;
    
    while(f.is_open() && getline(f, line)) {

        stringstream ss (line);
        ss >> word;

        if(word == "seeds:") {
            while (ss >> word) {
                seeds.push_back(stol(word));
            }
        } else if (!line.empty()) {
            // cout << line << endl;
            m.push_back(mapVals(f));
        }
    }

    f.close();

    for (long seed : seeds) {
        cout << "Start: " << seed << endl;
        tmp = checkSeed(seed, m);
        min = tmp < min ? tmp : min;
    }

    cout << "Min value of locations is: " << min << endl;

    return 0;
}