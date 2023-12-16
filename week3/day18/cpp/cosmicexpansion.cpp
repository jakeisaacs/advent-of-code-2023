#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

void ExpandUniverse() {

}

int main () {
    ifstream f("../input.txt");
    string line;
    vector<string> universe, expanded_universe;
    vector<int> rows, columns; 
    vector<pair<long, long>> coords;
    int i=0, j=0;
    int rowadder, coladder;
    bool isGalaxy;

    while(f.is_open() && getline(f, line)) {
        universe.push_back(line);
        rows.push_back(0);

        for(j=0;j<line.length();j++) {
            isGalaxy = line[j] == '#' ? 1 : 0;

            if (isGalaxy) {
                coords.push_back(make_pair(i, j));
            }
            
            if(j >= columns.size())
                columns.push_back(0);

            rows[i] += isGalaxy;
            columns[j] += isGalaxy;
        }
        i++;
    }

    const int N = rows.size(), M = columns.size();
    int first, second, stepsize;

    stepsize = 1000000;

    for (i=0;i<coords.size();i++) {
        first = coords[i].first;
        second = coords[i].second;

        for(j=0;j<first;j++) {
            if(rows[j] == 0)
                coords[i].first += stepsize-1;
        }
        for(j=0;j<second;j++) {
            if(columns[j] == 0)
                coords[i].second += stepsize-1;
        }
    }

    long dist, totaldist = 0;

    for (i=0;i<coords.size()-1;i++) {
        for(j=i+1;j<coords.size();j++) {
            dist = abs(coords[j].first - coords[i].first) + abs(coords[j].second - coords[i].second);
            totaldist += dist;
        }
    }

    cout << "Total Distance: " << totaldist << endl;

}