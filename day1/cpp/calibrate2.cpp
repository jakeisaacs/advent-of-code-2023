#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//COULD BE FURTHER OPTIMIZED... SEARCHING FOR LITERAL AND STRING VERSION OF NUMBERS IN EACH LINE
void checkPositions(int& l, int& r, string line)
{
    int pos, n = line.size(), min = n, max = -1;
    vector<string> vals = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for(int i=0;i<vals.size();i++) {
        //SEARCHING FROM FRONT OF STRING FOR MIN
        pos = line.find(vals[i]);

        if (pos != string::npos && pos < min) {
            min = pos;
            l = i%9 + 1;
        }
        //SEARCHING FROM BACK OF STRING FOR MAX
        pos = line.rfind(vals[i]);
        if (pos != string::npos && pos > max) {
            max = pos;
            r = i%9 + 1;
        }
    }
}

int sumCalibrations()
{
    //OPENING FILE WHEN DECLARING IFSTREAM
    ifstream f("../input.txt");
    string line;
    int n, tmp, start, end, sum;

    sum = 0;

    //READING FILE INPUT LINE BY LINE

    while (f.is_open() && getline(f, line)) {

        start = end = -1;

        checkPositions(start, end, line);
        
        // ADD 2 DIGIT NUMBER FORMED BY START & END TO SUM
        sum += start * 10 + end;
    }

    f.close();

    return sum;
}

int main()
{
    int sum = sumCalibrations();
    cout << "SUM OF CALIBRATION CODES: " << sum << endl;
    return 0;
}

