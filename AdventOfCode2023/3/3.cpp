#include <bits/stdc++.h>
using namespace std;


typedef pair<int, int> ii;
vector<string> v;

int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy[8] = {1, -1, -1, 0, 1, -1, 0, 1};

vector<ii> symbols;

// for the first problem, it is the sum of the numbers
// for the second problem, it is the sum of the gear ratios
int total = 0;

int is_inside(int x, int y) {
    return y >= 0 && y < (int) v.size() && x >= 0 && x < (int) v[0].size();
}

int get_horiz_number(ii pos) {
    int y = pos.second;
    int x_begin = pos.first;
    while (is_inside(x_begin - 1, y) && isdigit(v[y][x_begin - 1])) {
        x_begin--;
    }
    int x_end = pos.first;
    while (is_inside(x_end + 1, y) && isdigit(v[y][x_end + 1])) {
        x_end++;
    }
    string num = v[y].substr(x_begin, x_end - x_begin + 1);
    istringstream iss(num);
    int number;
    iss >> number;
    cout << number << endl;
    
    for (int x = x_begin; x <= x_end; x++) {
        v[y][x] = '.';
    }
    return number;
}

void dfs(ii pos) {
    v[pos.second][pos.first] = '.';
    for (int i = 0; i < 8; i++) {
        int x = pos.first + dx[i];
        int y = pos.second + dy[i];
        if (is_inside(x, y) && isdigit(v[y][x])) {
            int number = get_horiz_number(make_pair(x, y));
            total += number;
        }
    }
}

void solveFirst() {
    string line;
    while (getline(cin, line)) {
        v.push_back(line);
    }
    for (int y = 0; y < (int) v.size(); y++) {
        for (int x = 0; x < (int) v[0].size(); x++) {
            char c = v[y][x];
            if (!isdigit(c) && c != '.') {
                symbols.emplace_back(x, y);
            }
        }
    }
    for (auto &p: symbols) {
        dfs(p);
    }
}

void dfsGears(ii pos) {
    v[pos.second][pos.first] = '.';
    int count = 0;
    int gear_ratio = 1;
    for (int i = 0; i < 8; i++) {
        int x = pos.first + dx[i];
        int y = pos.second + dy[i];
        if (is_inside(x, y) && isdigit(v[y][x])) {
            int number = get_horiz_number(make_pair(x, y));
            gear_ratio *= number;
            count++;
        }
    }
    if (count == 2) {
        total += gear_ratio;
    }
}
void solveSecond() {
    string line;
    while (getline(cin, line)) {
        v.push_back(line);
    }
    for (int y = 0; y < (int) v.size(); y++) {
        for (int x = 0; x < (int) v[0].size(); x++) {
            char c = v[y][x];
            if (c == '*') {
                symbols.emplace_back(x, y);
            }
        }
    }
    for (auto &p: symbols) {
        dfsGears(p);
    }
}

int main() {
    solveSecond();
    cout << total << endl;
    return 0;
}
