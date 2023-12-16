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


void CheckPipes(vector<string>& maze, char prev, int r, int c, int& steps) {
    // cout << "Row: " << r << " Col: " << c << " Val: " << maze[r][c] << " Steps: " << steps << endl;
    
    if (maze[r][c] == 'S') return;

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

    StartPipeSearch(maze, startrow, startcol, steps);
    cout << "Total steps: " << steps << " Half point: " << (steps/2 + steps%2) << endl;
}