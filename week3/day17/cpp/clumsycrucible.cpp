#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

int FindMinPath(vector<vector<int> >& grid, vector<vector<int> >& visited, int r, int c, char dir, int spaces) {
    const int N = grid.size()-1, M = grid[0].size()-1;
    int minVal;

    cout << "Checking: " << r << "," << c  << " Direction: " << dir << endl;

    if(r == N && c == M)
        return grid[r][c];

    visited[r][c] = 1;

    minVal = INT_MAX;

    if (dir == 'E') {
        if (spaces > 0 && c < M && !visited[r][c+1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c+1, 'E', spaces-1));
        if (r > 0 && !visited[r-1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r-1, c, 'N', 2));
        if (r < N && !visited[r+1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r+1, c, 'S', 2));
    } else if (dir == 'W') {
        if (spaces > 0 && c > 0 && !visited[r][c-1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c-1, 'W', spaces-1));
        if (r > 0 && !visited[r-1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r-1, c, 'N', 2));
        if (r < N && !visited[r+1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r+1, c, 'S', 2));
    } else if (dir == 'N') {
        if (spaces > 0 && r > 0 && !visited[r-1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r-1, c, 'N', spaces-1));
        if (c > 0 && !visited[r][c-1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c-1, 'W', 2));
        if (c < M && !visited[r][c+1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c+1, 'E', 2));
    } else if (dir == 'S') {
        if (spaces > 0 && r < N && !visited[r+1][c])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r+1, c, 'S', spaces-1));
        if (c > 0 && !visited[r][c-1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c-1, 'W', 2));
        if (c < M && !visited[r][c+1])
            minVal = min(minVal, grid[r][c] + FindMinPath(grid, visited, r, c+1, 'E', 2));
    }

    // visited[r][c] = 0;

    return minVal;
}

int main () {
    ifstream f("../input.txt");
    string line, gridval;
    vector<vector<int> > grid;
    int row = 0, minVal;

    while(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        grid.push_back(vector<int>());

        for(int i=0;i<line.length();i++){
            grid[row].push_back(line[i] - '0');
        }

        row++;
    }

    vector<vector<int> > visited(grid.size(), vector<int>(grid[0].size(), 0));

    cout << grid.size() << "," << grid[0].size() << endl;
    cout << visited.size() << "," << visited[0].size() << endl;
    
    minVal = FindMinPath(grid, visited, 0, 0, 'E', 3) - grid[0][0];
    cout << "Min Path: " << minVal << endl;

}