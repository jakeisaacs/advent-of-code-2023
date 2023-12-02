#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int CheckGame(string& l, int& gamenum) {
    /* The code snippet is using regular expressions to search for matches in a string `l`. */
    smatch m;
    regex e ("\\d\\d\\s\\w+");
    int n, count;
    string str, color;



    while(regex_search(l, m, e)) {
        str = m[0].str();
        n = str.size() - 3;

        count = stoi(str.substr(0,2));
        color = str.substr(3,n);

        if (count > 14 || (color == "red" && count > 12) || (color == "green" && count > 13) || (color == "blue" && count > 14)) {
            return 0;
        }
            

        l = m.suffix().str();
    }

    return gamenum;
}


int main() {
    fstream f("input.txt");
    string line;
    int sum = 0, gamenum = 0;

    while(f.is_open() &&  getline(f, line)) {
        cout << line << endl;
        sum += CheckGame(line, ++gamenum); 
    }

    cout << "Sum of plausible game #s: " << sum << endl;

    f.close();

    return 0;
}