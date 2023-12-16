#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

void PrintPlatform(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cout << platform[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int GetSum(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();
    int sum = 0;

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(platform[i][j] == 'O')
                sum += N-i;
        }
    }
    return sum;
}

void MoveNorth(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();
    vector<int> tracker(M, 0);

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(platform[i][j] == 'O') {
                if(tracker[j] != i) {
                    platform[tracker[j]][j] = platform[i][j];
                    platform[i][j] = '.';
                }
                tracker[j]++;
            } else if (platform[i][j] == '#') {
                tracker[j] = i + 1;
            }
        }
    }
}

void MoveSouth(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();
    vector<int> tracker(M, N-1);

    for(int i=N-1;i>=0;i--) {
        for(int j=0;j<M;j++) {
            if(platform[i][j] == 'O') {
                if(tracker[j] != i) {
                    platform[tracker[j]][j] = platform[i][j];
                    platform[i][j] = '.';
                }
                tracker[j]--;
            } else if (platform[i][j] == '#') {
                tracker[j] = i - 1;
            }
        }
    }
}

void MoveWest(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();
    vector<int> tracker(N, 0);

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(platform[i][j] == 'O') {
                if(tracker[i] != j) {
                    platform[i][tracker[i]] = platform[i][j];
                    platform[i][j] = '.';
                }
                tracker[i]++;
            } else if (platform[i][j] == '#') {
                tracker[i] = j + 1;
            }
        }
    }
}

void MoveEast(vector<string>& platform) {
    const int N = platform.size(), M = platform[0].length();
    vector<int> tracker(N, M-1);

    for(int i=0;i<N;i++) {
        for(int j=M-1;j>=0;j--) {
            if(platform[i][j] == 'O') {
                if(tracker[i] != j) {
                    platform[i][tracker[i]] = platform[i][j];
                    platform[i][j] = '.';
                }
                tracker[i]--;
            } else if (platform[i][j] == '#') {
                tracker[i] = j - 1;
            }
        }
    }
}

void PerformCycle(vector<string>& platform) {
    MoveNorth(platform);
    MoveWest(platform);
    MoveSouth(platform);
    MoveEast(platform);
    // PrintPlatform(platform);
}

bool VerifySteps(int indx, int steps, int prevsum, vector<string> platform) {
        int sum;

        for(int i=indx+1;i<=indx+steps;i++) {
            PerformCycle(platform);
            sum = GetSum(platform);
        }

        if (sum == prevsum) {
            cout << "WINNING SUM: " << sum << " INDEX: " << indx << " STEPS: " << steps << endl;
            return true;
        }

        return false;
}

int main () {
    ifstream f("../input.txt");
    string line;
    vector<string> platform, prevplatform;

    while(f.is_open() && getline(f, line)) {
        platform.push_back(line);
    }

    map<int, int> m;
    int previ, sum, prevsum, steps, cycles;

    cycles = 1000000000; 

    for(long i=0;i<1000000000;i++){
        PerformCycle(platform);
        sum = GetSum(platform);
        if (m.find(sum) != m.end()) {
            steps = i - m[sum];
            // cout << "index: " << i << " steps: " << steps << " cycles: " << (cycles - i - 1)%steps << endl;
            cout << "index: " << i << " Total sum: " << GetSum(platform) << endl;
            PrintPlatform(platform);
            if (steps > 1 && (cycles - i - 1)%steps == 0 && VerifySteps(i, steps, sum, platform)) {
                break;
            }
        }
        m[sum] = i;
        // PrintPlatform(platform);
    }

    // cout << "Total sum: " << GetSum(platform) << endl;
}