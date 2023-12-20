#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <numeric>
#include <sstream>

using namespace std;

bool CheckPart( map<string, string>& workflows, vector<int>& part) {
    string workflow, rule, result, key = "in";
    const string XMAS = "xmas";
    int pos, val, end, semipos;
    bool lt;

    workflow = workflows[key];
    pos = 0;

    while (true) {
        workflow = workflow.substr(pos, workflow.length());
        pos = workflow.find(',');
        if (pos == string::npos) {
            workflow = workflow.substr(0,workflow.length());
            if(workflow[0] == 'A')
                return true;
            else if (workflow[0] == 'R')
                return false;
            else {
                key = workflow;
                workflow = workflows[key];
                pos = 0;
            }
        } else {
            rule = workflow.substr(0,pos);
            end = rule.length();
            semipos =  rule.find(':');
            result = rule.substr(semipos+1,end-semipos-1);

            val = stoi(rule.substr(2,semipos-2));
            lt = rule[1] == '<';

            if ((part[XMAS.find(rule[0])] < val && lt) || (part[XMAS.find(rule[0])] > val && !lt)) {
                if(result[0] == 'A')
                    return true;
                else if (result[0] == 'R')
                    return false;
                else {
                    key = result;
                    workflow = workflows[key];
                    pos = 0;
                }
            } else {
                pos++;
            }
        }
    }

    return false;
}

int main () {
    ifstream f("../input.txt");
    string line, key;
    smatch m;
    regex e_parts("\\d+");
    int pos1, pos2, val, sum, total;
    vector<int> v;
    map<string, string> workflows;

    while(f.is_open() && getline(f, line)) {
        //break on empty line (len might be over 0 for newline char)
        if(line.length() < 2) break;

        pos1 = line.find('{');
        pos2 = line.find('}') - pos1 - 1;

        key = line.substr(0,pos1);
        line = line.substr(pos1+1, pos2);

        workflows[key] = line;

        // cout << key << " " << workflows[key] << endl;
    }

    while(f.is_open() && getline(f, line)) {
        sum = 0;
        while(regex_search(line, m, e_parts)) {
            val = stoi(m[0].str());
            sum += val;
            v.push_back(val);
            line = m.suffix().str();
        }
        
        if (CheckPart(workflows, v)) total += sum;

        v.clear();
    }

    cout << "Total of valid parts: " << total << endl;

}