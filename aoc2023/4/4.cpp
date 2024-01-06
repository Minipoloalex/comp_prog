#include <bits/stdc++.h>
using namespace std;

void solveFirst() {
    int points = 0;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string trash;
        iss >> trash >> trash;
        int num = 0;
        set<int> win;
        while (iss >> num) {
            win.insert(num);
        }

        iss.clear();

        char divider;
        iss >> divider;

        set<int> mine;

        while (iss >> num) {
            mine.insert(num);
        }
        win.merge(mine);    // win = union; mine = intersection;

        points += (1 << mine.size()) >> 1;
    }
    cout << points << endl;
}

void solveSecond() {
    int cards = 0;
    vector<int> count;
    vector<string> lines;
    
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    count.assign(lines.size(), 1);
    for (int i = 0; i < (int) lines.size(); i++) {
        line = lines[i];
        cards += count[i];
        
        istringstream iss(line);
        string trash;
        iss >> trash >> trash;
        int num = 0;
        set<int> win;
        while (iss >> num) {
            win.insert(num);
        }

        iss.clear();

        char divider;
        iss >> divider;

        set<int> mine;

        while (iss >> num) {
            mine.insert(num);
        }
        win.merge(mine);    // win = union; mine = intersection;

        int points = (int) mine.size();
        cout << i << ": " << count[i] << ", points: " << points << endl;
        for (int j = i + 1; j <= i + points && j < (int) lines.size(); j++) {
            count[j] += count[i];
        }
    }
    cout << cards << endl;
}

int main() {
    solveSecond();
    return 0;
}
