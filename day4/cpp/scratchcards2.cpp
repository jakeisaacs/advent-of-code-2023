#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    fstream f("../input.txt");
    string line, word;
    stringstream ss_w, ss_g;
    smatch m;
    regex e_winners ("(\\d+\\s+){10}\\|"), e_guesses("(\\s+\\d+){25}");
    int sum = 0, indx;
    vector<string> v, fv;
    vector<int> vcopies;
    
    while(f.is_open() && getline(f, line)) {
        fv.push_back(line);
        vcopies.push_back(1);
    }
    
    for(int i=0;i<fv.size();i++)
    {
        sum += vcopies[i];
        if(regex_search(fv[i], m, e_winners)) {
            ss_w << m[0].str().substr(0,m[0].str().size()-1);
            line = m.suffix().str();
        }
        if(regex_search(fv[i], m, e_guesses)) {
            ss_g << m[0].str().substr(0,m[0].str().size());
            while(ss_g >> word) {
                v.push_back(word);
            }
        }

        indx = i;
        while (ss_w >> word) {
            if(find(v.begin(), v.end(), word) != v.end())
            {
                vcopies[++indx] += vcopies[i];
            }
        }
        v.clear();
        ss_g.clear();
        ss_w.clear();
    }

    f.close();

    cout << "Calculated sum of winners: " << sum << endl;

    return 0;
}