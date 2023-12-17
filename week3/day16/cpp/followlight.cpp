#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

void DirectLight(vector<string>& grid, map<pair<int, int>, string>& m, int r, int c, char dir) {
    const int N = grid.size(), M = grid[0].length();
    int rinc = 0, cinc = 0;
    pair<int, int> p;

    if (dir == 'N')
        rinc = -1;
    else if (dir == 'S')
        rinc = 1;
    else if (dir == 'E')
        cinc = 1;
    else if (dir == 'W')
        cinc = -1;

    while (r >= 0 && r < N && c >=0 && c < M) {
        p = make_pair(r, c);

        if (m.find(p) != m.end() && m[p].find(dir) != string::npos) {
            return;
        }

        m[p] += dir;

        if (grid[r][c] == '\\') {
            char newdir = dir == 'N' ? 'W' : dir == 'S' ? 'E' : dir == 'E' ? 'S' : 'N'; 
            int newr = newdir == 'N' ? r-1 : newdir == 'S' ? r+1 : r, newc = newdir == 'E' ? c+1 : newdir == 'W' ? c-1 : c;
            DirectLight(grid, m, newr, newc, newdir);
            return;
        }
        if (grid[r][c] == '/') {
            char newdir = dir == 'N' ? 'E' : dir == 'S' ? 'W' : dir == 'E' ? 'N' : 'S'; 
            int newr = newdir == 'N' ? r-1 : newdir == 'S' ? r+1 : r, newc = newdir == 'E' ? c+1 : newdir == 'W' ? c-1 : c;
            DirectLight(grid, m, newr, newc, newdir);
            return;
        }
        if (grid[r][c] == '|' && (dir == 'E' || dir == 'W')) {
            DirectLight(grid, m, r-1, c, 'N');
            DirectLight(grid, m, r+1, c, 'S');
            return;
        }
        if (grid[r][c] == '-' && (dir == 'N' || dir == 'S')) {
            DirectLight(grid, m, r, c+1, 'E');
            DirectLight(grid, m, r, c-1, 'W');
            return;
        }

        r += rinc;
        c += cinc;
    }
}

int CountMap(map<pair<int, int>, string>& m) {
    map<pair<int, int>, string>::iterator it;
    int counter = 0;

    for(it = m.begin();it != m.end();it++)
        counter++;
    
    m.clear();
    return counter;
}

int main () {
    ifstream f("../input.txt");
    string line;
    vector<string> grid;
    map<pair<int, int>, string> m;
    int maxVal = 0;

    while(f.is_open() && getline(f, line)) {
        grid.push_back(line);
    }

    const int N = grid.size()-1, M = grid[0].length()-1;

    for(int i=0;i<=N;i++) {
        DirectLight(grid, m, i, 0, 'E');
        maxVal = max(maxVal, CountMap(m));
        DirectLight(grid, m, i, M, 'W');
        maxVal = max(maxVal, CountMap(m));
    }

    for(int i=0;i<=M;i++) {
        DirectLight(grid, m, 0, i, 'S');
        maxVal = max(maxVal, CountMap(m));
        DirectLight(grid, m, N, i, 'N');
        maxVal = max(maxVal, CountMap(m));
    }
    
    cout << "Total Energized: " << maxVal << endl;
}