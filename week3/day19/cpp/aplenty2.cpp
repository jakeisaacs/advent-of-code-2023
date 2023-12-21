#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

int MultiplyRanges(vector<pair<int, int> >& ranges) {
    int total = 1;

    for(int i=0;i<ranges.size();i++) {
        total *= ranges[i].second - ranges[i].first;
    }

    return total;
}

int CheckRange( map<string, string>& workflows, vector<pair<int, int> > ranges, string key) {
    string workflow, rule, result;
    const string XMAS = "xmas";
    int pos, val, sum, end, tmp, semipos, rngindx;
    bool lt;

    workflow = workflows[key];
    pos = -1;
    sum = 0;

    while (true) {
        cout << workflow << endl;
        workflow = workflow.substr(pos+1, workflow.length());
        pos = workflow.find(',');
        if (pos == string::npos) {
            workflow = workflow.substr(0,workflow.length());
            if(workflow[0] == 'A')
                sum += MultiplyRanges(ranges);
            else if (workflow[0] == 'R')
                sum += 0;
            else {
                sum += CheckRange(workflows, ranges, result);
            }
            break;
        } else {
            rule = workflow.substr(0,pos);
            end = rule.length();
            semipos =  rule.find(':');
            result = rule.substr(semipos+1,end-semipos-1);

            rngindx = XMAS.find(rule[0]);
            val = stoi(rule.substr(2,semipos-2));
            lt = rule[1] == '<';

            if(lt) {
                tmp = ranges[rngindx].second;
                ranges[rngindx].second = min(tmp, val);
                if(result[0] == 'A')
                    sum += MultiplyRanges(ranges);
                else if (result[0] == 'R')
                    sum += 0;
                else {
                    sum += CheckRange(workflows, ranges, result);
                }
                ranges[rngindx].first = max(ranges[rngindx].first, ranges[rngindx].second);
                ranges[rngindx].second = tmp;
            } else {
                tmp = ranges[rngindx].first;
                ranges[rngindx].first = max(tmp, val);
                if(result[0] == 'A')
                    sum += MultiplyRanges(ranges);
                else if (result[0] == 'R')
                    sum += 0;
                else {
                    sum += CheckRange(workflows, ranges, result);
                }
                ranges[rngindx].second = min(ranges[rngindx].first, ranges[rngindx].second);
                ranges[rngindx].first = tmp;
            }

        }
    }

    return sum;
}

int main () {
    ifstream f("../input.txt");
    string line, key;
    int pos1, pos2, val, sum, total;
    map<string, string> workflows;
    vector<pair<int, int> > ranges;

    while(f.is_open() && getline(f, line)) {
        //break on empty line (len might be over 0 for newline char)
        if(line.length() < 2) break;

        pos1 = line.find('{');
        pos2 = line.find('}') - pos1 - 1;

        key = line.substr(0,pos1);
        line = line.substr(pos1+1, pos2);

        workflows[key] = line;
    }

    for(int i=0;i<4;i++)
        ranges.push_back(make_pair(0,4000));

    total = CheckRange(workflows, ranges, "in");

    // CheckRange();

    cout << "Total of valid parts: " << total << endl;

}