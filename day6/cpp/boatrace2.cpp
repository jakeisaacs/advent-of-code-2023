#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    long r_time = 40817772, r_dist = 219101213651089, dist, comb;

    comb = 0;

    for (int i=0;i<(r_time/2)+1;i++) {
        dist = (r_time - i) * i;

        if (dist > r_dist) comb++;
    }

    cout << "Total win combinations: " << (comb*2-1) << endl;

    return 0;
}