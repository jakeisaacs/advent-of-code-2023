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

vector<long> checkSeed(long seed, vector<vector<vector<long> > >& m) {
    int i, j;
    vector<long> seeds;
    
    i = 0;
    while(i < m.size()) {
        j = 0;
        while (j < m[i].size()) {
            // cout << m[i][j][0] << " " << m[i][j][1] << " " << m[i][j][2] << endl;
            if (seed >= m[i][j][0] && seed < m[i][j][1])
            {
                if(i==0) {
                    seeds.push_back(m[i][j][1]-1);
                }

                seed = m[i][j][2] + (seed - m[i][j][0]);
                // cout << "START: " << m[i][j][0] << " END: " << m[i][j][1] <<  " Match: " << seed << endl;
                break;
            }
            j++;
        }
        // if (j == m[i].size()) {
        //     seed = -1;
        //     break;
        // }
        i++;
    }

    seeds.push_back(seed);

    // cout <<  i << " | " << seeds.size() << " | " << seeds[0] << " | " << seeds[1] << endl; 

    // cout << endl;
    return seeds;
}

int main() {
    fstream f("../input.txt");
    string line, word;
    long min = LONG_MAX;
    vector<long> seeds, tmp;
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

    for (int i=0; i < seeds.size(); i+=2) {
        cout << "Seed: " << seeds[i] << " Range: " << (seeds[i] + seeds[i+1]) << endl;
        for(long j=seeds[i];j<(seeds[i]+seeds[i+1]);j++)
        {
            // cout << i << ": " << j << endl;
            tmp = checkSeed(j, m);
            if (tmp[1] <= 0) break;
            min = tmp[1] < min ? tmp[1] : min;
            // j = tmp[0] > j ? tmp[0] : j;

            // cout << tmp[0] << " --- " << tmp[1] << endl;
        }
        cout << "Index: " << i << "Current Min: " << min << endl;
    }

    cout << "Min value of locations is: " << min << endl;

    return 0;
}