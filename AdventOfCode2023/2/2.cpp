#include <bits/stdc++.h>
using namespace std;


void solveFirst() {
    unordered_map<string, int> m = {{"red", 12}, {"green", 13}, {"blue", 14}};
    string line;
    int sumIds = 0;
    while (getline(cin, line)) {
        string trash;
        char ctrash;
        int id;
        bool possible = true;

        istringstream iss_set(line);
        iss_set >> trash >> id >> ctrash;
        
        string game_set;
        while (getline(iss_set, game_set, ';')) {
            string taken;
            istringstream iss_taken(game_set);
            while (getline(iss_taken, taken, ',')) {
                istringstream iss(taken);
                int number;
                string name;
                iss >> number >> name;
                if (number > m[name]) { // not possible
                    possible = false;
                }
            }
        }
        if (possible) {
            sumIds += id;
        }
    }
    cout << sumIds << endl;
}
void solveSecond() {
    string line;
    int total = 0;
    while (getline(cin, line)) {
        unordered_map<string, int> m = {{"red", 0}, {"blue", 0}, {"green", 0}};
        string trash;
        char ctrash;
        int id;

        istringstream iss_set(line);
        iss_set >> trash >> id >> ctrash;
        
        string game_set;
        while (getline(iss_set, game_set, ';')) {
            string taken;
            istringstream iss_taken(game_set);
            while (getline(iss_taken, taken, ',')) {
                istringstream iss(taken);
                int number;
                string name;
                iss >> number >> name;
                m[name] = max(m[name], number);
            }
        }
        int game_total = 1;
        for (auto &[type, count]: m) {
            // cout << type << "-" << count << endl;
            game_total *= count;
        }
        // cout << game_total << endl;
        total += game_total;
    }
    cout << total << endl;
}
int main() {
    solveSecond();
    return 0;
}
