#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int CheckGame(string& l) {
    /* The code snippet is using regular expressions to search for matches in a string `l`. */
    smatch m, m2;
    regex e ("\\d+\\s\\w+"), e2("\\d+");
    int n, count, maxr, maxg, maxb;
    string str, color;

    maxr = maxg = maxb = 0;

    while(regex_search(l, m, e)) {
        str = m[0].str();
        n = str.size();

        if(regex_search(str, m2, e2)) {
            count = stoi(m2[0].str());
        }

        color = count > 9 ? str.substr(3,n-3) : str.substr(2,n-2);

        if (color == "red" && count > maxr) {
            maxr = count;
        } else if (color == "green" && count > maxg) {
            maxg = count;
        } else if (color == "blue" && count > maxb) {
            maxb = count;
        }

        l = m.suffix().str();
    }

    return maxr * maxg * maxb;
}


int main() {
    fstream f("../input.txt");
    string line;
    int sum = 0;

    //Reading each line and getting power for set of cubes (min of each color cube multiplied together)

    while(f.is_open() &&  getline(f, line)) {
        sum += CheckGame(line); 
    }

    cout << "Sum of plausible game #s: " << sum << endl;

    f.close();

    return 0;
}