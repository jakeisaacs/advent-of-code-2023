#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<int> v_time{40, 81, 77, 72}, v_dist{219, 1012, 1365, 1089};
    int curTime, curDist, dist, count, comb;
    const int N = v_time.size();

    comb = 1;

    for (int i=0;i<N;i++) {
        curTime = v_time[i];
        curDist = v_dist[i];
        count = 0;
        for(int j=0;j<curTime;j++){
            dist = (curTime - j) * j;

            if (dist > curDist) count++;
        }
        comb *= count;
    }

    cout << "Total win combinations: " << comb << endl;

    return 0;
}