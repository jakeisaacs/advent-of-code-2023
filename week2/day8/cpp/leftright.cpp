#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>

using namespace std;

// Recursive function to return gcd of a and b  
long long gcd(long long a, long long b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  
// Function to return LCM of two numbers  
long long lcm(long a, long b) 
{ 
    return (a / gcd(a, b)) * b; 
} 

int main () {
    ifstream f("../input.txt");
    string line;
    smatch m;
    regex e ("([A-Z])\\w+");
    vector<int> lr;
    vector<string> coords, positions;
    vector<int> found;
    map<string, vector<string> > mp;
    string key, val1, val2;

    if(f.is_open() && getline(f, line)) {
        for (int i=0;i<line.length();i++) {
            lr.push_back(line[i] == 'L' ? 0 : 1);
        }
        getline(f, line);
    }

    while(f.is_open() && getline(f, line)) {

        while(regex_search(line, m, e)) {
            coords.push_back(m[0].str());
            line = m.suffix().str();
        }
        if(coords[0][2] == 'A') positions.push_back(coords[0]);
        mp[coords[0]] = {coords[1], coords[2]};
        coords.clear();
    }

    long steps = 0;
    const int N = lr.size(), M = positions.size();
    // map<string, vector<string> >::iterator it;
    bool foundZ, foundAll = false;
    vector<bool> matches(M, false);
    int matchCount;
    long long total = 1;

    for (int i=0; i<M;i++) {
        cout << "Starting at: " << positions[i] << endl;
    }

    for (int i=0; i<M;i++) {
        steps = 0;
        while (positions[i][2] != 'Z') {
            positions[i] = mp[positions[i]][lr[steps%N]];
            steps++;
        }
        found.push_back(steps);
        cout << steps << endl;
    }

    long long lcmval = lcm(found[0], found[1]);

    for (int i=2; i<M;i++) {
        lcmval = lcm(lcmval, found[i]);
        cout << lcmval << endl;
    }


    cout << "Total steps to Zs: " << lcmval << endl;

}