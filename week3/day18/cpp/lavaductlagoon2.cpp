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
    char dir;
    long x1, x2, y1, y2, span, points, sum, perimeter;
    string color, directions;

    x1 = x2 = y1 = y2 = 0;
    points = sum = perimeter = 0;

    directions = "RDLU";

    while(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        ss >> dir;
        ss >> span;
        ss >> color;

        //Overwriting span and dir based off part 2 encoding
        span = stoi(color.substr(2,color.length()-4), 0, 16);
        dir = directions[stoi(color.substr(color.length()-2,1))];

        x1 = x2;
        y1 = y2;

        if (dir == 'R') { x2 = x1 + span; } 
        else if (dir == 'L') { x2 = x1 - span; } 
        else if (dir == 'U') { y2 = y2 + span; } 
        else { y2 = y2 - span; }

        sum += x1*y2 - x2*y1;
        perimeter += abs(x2-x1) + abs(y2-y1);
        points += span;

        // cout << x1 << "," << y1 << " | " << x2 << "," << y2 << endl;
    }

    //Using Pick's Theorem & Shoelace Theorem from Day 10
    long total = abs(sum)/2 + points/2 + 1;

    cout << "Calculated area (including perimeter): " << total << endl;

}