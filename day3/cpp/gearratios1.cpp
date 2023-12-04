#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool CheckSides(int r, int c, vector<string>& v, int N, int M) {
    for(int i=(r > 0 ? r-1 : 0);i<=r+1 && i<M;i++) {
        for(int j=(c > 0 ? c-1 : 0);j<=c+1 && j<N;j++) {
            int tmp = v[i][j] - '0';
            if(v[i][j] != '.' && v[i][j] != '\r' && !(tmp >= 0 && tmp < 10)) {
                cout << i << "," << j << " " << v[i][j] << " ";
                return true;
            }
        }
    }

    return false;
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
            tmp = v[i][j] - '0';
            while(tmp >=0 && tmp <= 9 && j < N) {
                isValid = isValid || CheckSides(i, j, v, N, M);
                num = num * 10 + tmp;
                tmp = v[i][++j < N ? j : N-1] - '0';
            }
            sum += isValid ? num : 0;
            if(isValid) cout << (i+1) << "," << (j+1) << ": " << num << " | " << sum << endl;
            num = 0;
            isValid = false;
        }
    } 

    f.close();

    cout << "Sum of all valid codes: " << sum << endl;

    return 0;
}