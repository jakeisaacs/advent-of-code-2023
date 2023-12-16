#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>

using namespace std;

int GetHashVal(string code) {
    int hashval = 0;


    for (char c : code) {
        hashval += c;
        hashval *= 17;
        hashval %= 256;
    }

    return hashval;

}

void InsertLens(map<int, map<string, pair<int, int> > >& m, string code, int flen) {
    int val = GetHashVal(code);

        if(m.find(val) != m.end() && m[val].find(code) != m[val].end())
            m[val][code].second = flen;
        else {
            m[val][code] = make_pair(m[val].size()+1, flen);
        }
}

void RemoveLens(map<int, map<string, pair<int, int> > >& m, string code) {
    int val = GetHashVal(code);

    if (m.find(val) != m.end() && m[val].find(code) != m[val].end()) {
        map<string, pair<int, int> >::iterator it;
        int num = m[val][code].first;
        m[val].erase(code);
        for(it = m[val].begin();it!=m[val].end();++it) {
            if(it->second.first > num) {
                it->second.first--;
            }
        } 
        
    }
}

void IterateMap(map<int, map<string, pair<int, int> > >& m) {
    map<int, map<string, pair<int, int> > >::iterator it1;
    map<string, pair<int, int> >::iterator it2;
    int sum = 0;

    for(it1 = m.begin();it1!=m.end();++it1) {
        for(it2 = it1->second.begin();it2!=it1->second.end();++it2) {
            sum += (it1->first+1) * it2->second.first * it2->second.second;
        }
    }

    cout << "Total sum: " << sum << endl;
}

int main () {
    ifstream f("../input.txt");
    string line, str, code;
    long sum = 0;
    map<int, map<string, pair<int, int> > > m;

    int flen, pos;

    if(f.is_open() && getline(f, line)) {
        stringstream ss(line);
        while(ss.good()) {
            getline(ss, str, ',');

            pos = str.find('=');
            if (pos != string::npos) {
                code = str.substr(0, pos);
                flen = str[pos+1] - '0';
                InsertLens(m, code, flen);
            } else {
                pos = str.find('-');
                code = str.substr(0, pos);
                RemoveLens(m, code);
            }
        }

        IterateMap(m);
    }

}