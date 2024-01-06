#include <bits/stdc++.h>
using namespace std;

int main() {
    int M; cin >> M;
    string line;
    getline(cin, line); // rest of the line (empty)
    
    unordered_map<string, int> um;
    unordered_map<string, set<string>> used;
    
    set<string> people;
    vector<string> res;
    for (int i = 0; i < M; i++) {
        getline(cin, line);
        istringstream iss(line);
        string name;
        iss >> name;
        people.insert(name);
        string word;
        
        while (iss >> word) {
            um[word]++;
            used[word].insert(name);
        }
    }
    for (auto &[s, p]: used) {
        if (p.size() == people.size()) {
            res.push_back(s);
        }
    }
    sort(res.begin(), res.end(), [&um](string a, string b) {
        return um[a] > um[b];
    });
    for (const string &s: res) {
        cout << s << endl;
    }
    if (res.empty()) {
        cout << "ALL CLEAR" << endl;
    }
    return 0;
}
