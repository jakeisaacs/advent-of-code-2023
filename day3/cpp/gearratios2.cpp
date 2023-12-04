#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int CheckGears(int r, int c, vector<string>& v, int N, int M) {
    int num, count=0, mult = 1;
    for(int i=(r > 0 ? r-1 : 0);i<=r+1 && i<M;i++) {
        for(int j=(c > 0 ? c-1 : 0);j<=c+1 && j<N;j++) {
            int tmp = v[i][j] - '0';
            if(tmp >= 0 && tmp < 10) {
                num = 0;
                while(j >= 0  && (tmp >= 0 && tmp < 10)) {
                    j--;
                    tmp = v[i][j >= 0 ? j : 0] - '0';
                }
                tmp = v[i][++j] - '0';
                while(j < N && (tmp >= 0 && tmp < 10)) {
                    num = num * 10 + tmp;
                    j++;
                    tmp = v[i][j < N ? j : N - 1] - '0';
                }
                mult *= num;
                count++;
            }
        }
    }

    return count == 2 ? mult : 0;
}

int main() {
    fstream f("../input.txt");
    string line;
    int sum = 0, tmp = 0, num = 0;
    bool isValid = false;

    vector<string> v;
    
    while(f.is_open() &&  getline(f, line)) {
        v.push_back(line);
    }

    const int N = v[0].size(), M = v.size();

    for (int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            if(v[i][j] == '*')
                sum += CheckGears(i, j, v, N, M);
        }
    } 

    f.close();

    cout << "Sum of all valid codes: " << sum << endl;

    return 0;
}