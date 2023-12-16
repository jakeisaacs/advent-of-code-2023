#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

const string 
    validUp = "|F7",
    validDown = "|LJ", 
    validLeft = "-LF", 
    validRight = "-J7";

map<pair<int, int>, char> pipes, interior;
vector<pair<int, int> > coords;

void CheckPipes(vector<string>& maze, char prev, int r, int c, int& steps) {
    
    pipes[make_pair(r,c)] = maze[r][c];

    if (maze[r][c] == 'S') return;

    coords.push_back(make_pair(r+1,c+1));

    switch (maze[r][c]) {
        case '|':
            if (prev == 'N') {
                r++;
                prev = 'N';
            } else {
                r--;
                prev = 'S';
            }
            break;
        case '-':
            if (prev == 'W') {
                c++;
                prev = 'W';
            } else {
                c--;
                prev = 'E';
            }
            break;
        case 'L':
            if (prev == 'N') { 
                c++;
                prev = 'W';
            }
            else {
                r--;
                prev = 'S';
            }
            break;
        case 'J':
            if (prev == 'N') {
                c--;
                prev = 'E';
            }
            else {
                r--;
                prev = 'S';
            }
            break;
        case '7':
            if (prev == 'S') {
                c--;
                prev = 'E';
            }
            else {
                r++;
                prev = 'N';
            }
            break;
        case 'F':
            if (prev == 'S') {
                c++;
                prev = 'W';
            }
            else {
                r++;
                prev = 'N';
            }
            break;
        default: 
            break;
    }

    CheckPipes(maze, prev, r, c, ++steps);
}

void StartPipeSearch(vector<string>& maze, int r, int c, int& steps) {
    if (r > 0 && validUp.find(maze[r-1][c]) != string::npos) {
        CheckPipes(maze, 'S', r-1, c, ++steps);
    } 
    else if (r < maze.size() - 1 && validDown.find(maze[r+1][c]) != string::npos) {
        CheckPipes(maze, 'N', r+1, c, ++steps);
    } 
    else if (c > 0 && validLeft.find(maze[r][c-1]) != string::npos) {
        CheckPipes(maze, 'E', r, c-1, ++steps);
    } 
    else if (c < maze[r].length() - 1 && validRight.find(maze[r][c+1]) != string::npos) {
        CheckPipes(maze, 'W', r, c+1, ++steps);
    } 
}


void PicksTheoremCalc() {
    int sum = 0;
    const int N = coords.size();

    // Using Shoelace formula for interior lattice points
    for (int i=0;i<N;i++) {
        sum += coords[i].first * coords[(i+1)%N].second - coords[i].second * coords[(i+1)%N].first;
    }

    int area = abs(sum/2) - N/2 + 1;

    cout << "Calculated Area: " << area << endl;
}

int main () {
    ifstream f("../input.txt");
    string line;
    vector<string> maze;
    map<pair<int, int>, int> m;
    int i, pos, startrow = -1, startcol = -1;

    i = 0;
    while(f.is_open() && getline(f, line)) {
        maze.push_back(line);
        
        if (startrow < 0) {
            pos = line.find('S');
            if (pos != string::npos) {
                startcol = pos;
                startrow = i;
            }
        }
        i++;
    }

    const int N = i;

    cout << N << " | " << maze[startrow][startcol] << endl;

    int steps = 0;
    int count = 0;

    coords.push_back(make_pair(startrow+1, startcol+1));

    cout << "Start: " << (startrow+1) << ", " << (startcol+1) << endl;

    StartPipeSearch(maze, startrow, startcol, steps);
    cout << "Total steps: " << steps << " Half point: " << (steps/2 + steps%2) << endl;
    
    PicksTheoremCalc();
}