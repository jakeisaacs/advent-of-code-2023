#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int sumCalibrations()
{
    //OPENING FILE WHEN DECLARING IFSTREAM
    ifstream f("calibration.txt");
    string line;
    int n, tmp, start, end, sum;

    sum = 0;

    //READING FILE INPUT LINE BY LINE

    while (f.is_open() && getline(f, line)) {

        start = end = -1;
        n = line.size();

        //IF YOU WANT TO WATCH EACH LINE...
        // cout << line << endl;

        //LOOK FROM FRONT FOR START
        for(int i=0;i<n && start<0;i++)
        {
            tmp = line[i] - '0';
            if (tmp >= 0 && tmp < 10)
                start = tmp;
        }
        //LOOK FROM BACK FOR END
        for(int i=n-1;i>=0 && end<0;i--)
        {
            tmp = line[i] - '0';
            if(tmp >= 0 && tmp < 10)
                end = tmp;
        }
        
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

