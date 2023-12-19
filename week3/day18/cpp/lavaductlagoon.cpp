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
    int x1, x2, y1, y2, sum, points, span, perimeter;
    string color;

    x1 = x2 = y1 = y2 = 0;
    points = sum = perimeter = 0;

    while(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        ss >> dir;
        ss >> span;
        ss >> color;
        // color = color.substr(1,color.length()-2);

        x1 = x2;
        y1 = y2;

        if (dir == 'R') { x2 = x1 + span; } 
        else if (dir == 'L') { x2 = x1 - span; } 
        else if (dir == 'U') { y2 = y2 + span; } 
        else { y2 = y2 - span; }

        sum += x1*y2 - x2*y1;
        perimeter += abs(x2-x1) + abs(y2-y1);
        points += span;

        cout << x1 << "," << y1 << " | " << x2 << "," << y2 << endl;
    }

    //Using Pick's Theorem & Shoelace Theorem from Day 10
    int total = abs(sum)/2 + points/2 + 1;

    cout << "Calculated area (including perimeter): " << total << endl;

}