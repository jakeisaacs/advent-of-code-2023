#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>

using namespace std;

int GetHashVal(string code) {
    int hashval = 0;


    for (char c : code) {
        hashval += c;
        hashval *= 17;
        hashval %= 256;
    }

    return hashval;

}

int main () {
    ifstream f("../input.txt");
    string line, code;
    long sum = 0;

    int val;

    if(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        while(ss.good()) {
            getline(ss, code, ',');
            val = GetHashVal(code);
            sum += val;
            // cout << code << " " << val << " " << sum << endl;
        }
    }

    cout << "Final sum: " << sum << endl;

}