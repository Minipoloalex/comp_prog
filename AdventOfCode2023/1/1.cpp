#include <bits/stdc++.h>
using namespace std;

void solveFirst() {
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        bool is_first = true;
        int first, last = 0;
        for (char c : line) {
            if (isdigit(c)) {
                if (is_first) {
                    first = c - '0';
                    is_first = false;
                }
                last = c - '0';
            }
        }
        sum += first * 10 + last;
    }
    cout << sum << endl;
}

string nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void solveSecond() {
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        bool is_first = true;
        int first, last = 0;
        for (int i = 0; i  < (int) line.size(); i++) {
            char c = line[i];
            string rest_line = line.substr(i);

            for (int n = 0; n < 9; n++) {
                string number = nums[n];
                if (rest_line.starts_with(number)) {
                    if (is_first) {
                        is_first = false;
                        first = n + 1;
                    }
                    last = n + 1;
                }
            }
            if (isdigit(c)) {
                if (is_first) {
                    first = c - '0';
                    is_first = false;
                }
                last = c - '0';
            }
        }
        sum += first * 10 + last;
    }
    cout << sum << endl;
}

int main() {
    solveSecond();
    return 0;
}
