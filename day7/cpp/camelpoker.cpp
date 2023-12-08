#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int GetScore(string card) {
    int score = 0, max = 0, pmax = 0;
    map<char, int> m;
    const int N = card.length();

    for (int i=0;i<N;i++) {
        m[card[i]]++;
    }

    for (auto val : m) {
        if(val.second >= max) {
            pmax = max;
            max = val.second;
        } else if (val.second > pmax) {
            pmax = val.second;
        }
    }

    if(max > 3) {
        score = max + 1;
    } else if (max == 3) {
        score = pmax == 2 ? 4 : 3;
    } else if (max == 2) {
        score = pmax == 2 ? 2 : 1;
    }

    return score;
}

int ConvertCard(char c) {
    int n;

    switch (c) {
        case 'A':
            n = 14;
            break;
        case 'K':
            n = 13;
            break;
        case 'Q':
            n = 12;
            break;
        case 'J':
            n = 11;
            break;
        case 'T':
            n =  10;
            break;
        default:
            n = c - '0';
            break;
    }

    return n;
}

bool BreakTie(string c1, string c2) {
    int n1, n2;

    cout << "Breaking tie: " << c1 << " | " << c2 << endl;
    for (int i=0;i<c1.size();i++) {
        n1 = ConvertCard(c1[i]);
        n2 = ConvertCard(c2[i]);

        cout << "Comparing: " << c1[i] << " : " <<c2[i] << endl;
        if (n1 == n2)
            continue;

        return n1 > n2;
    }
    return c1.length() > c2.length();
}

void CompareCards(int index, vector<int>& scores, vector<int>& indexes, vector<string>& cards) {
    int i = index - 1, score = GetScore(cards[index]);

    while (score >= scores[i] && i >= 0) {
        if (score == scores[i]) {
            // cout << "Card: " << cards[index] << " Score: " << score << "vs Card: " << cards[indexes[i]] << " Score: " << scores[i] << endl;
            if(!BreakTie(cards[index], cards[indexes[i]]))
                break;
        }
        i--;
    }
    i++;

    scores.insert(scores.begin() + i, score);
    indexes.insert(indexes.begin() + i, index);
}

int main() {
    fstream f("../input.txt");
    string line, card, val;
    vector<string> cards;
    vector<int> vals, scores, indexes;
    long total = 0;
    int score = 0;

    while(f.is_open() && getline(f, line) && !line.empty()) {
        stringstream ss(line);
        ss >> card >> val;

        cards.push_back(card);
        vals.push_back(stoi(val));

    }

    score = GetScore(cards[0]);
    // score = 0;
    scores.push_back(score);
    indexes.push_back(0);

    // CompareCards(cards[1], 1, scores, indexes, cards);
    // CompareCards(cards[2], 2, scores, indexes, cards);
    // CompareCards(cards[3], 3, scores, indexes, cards);

    // for(int i=0;i<4;i++) {
    //     cout << "Card: " << cards[indexes[i]] << " Score: " << scores[i] << endl;
    // }

    const int N = cards.size();

    for (int i=1;i<N;i++) {
        CompareCards(i, scores, indexes, cards);
    }

    fstream of("output.txt");

    for(int i=0;i<N;i++) {
        total += (N-i) * vals[indexes[i]];
        of << "Card: " << cards[indexes[i]] << " Vals: " << vals[indexes[i]] << " Score: " << scores[i] << " Added: " << ((N-i) * vals[indexes[i]]) << " Total: " << total << endl;
        // cout << "Card: " << cards[indexes[i]] << " Vals: " << vals[indexes[i]] << " Score: " << scores[i] << " Added: " << ((N-i) * vals[indexes[i]]) << " Total: " << total << endl;
    }

    of.close();

    cout << "Total: " << total << endl;

    return 0;
}