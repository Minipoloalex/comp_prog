#include <bits/stdc++.h>
using namespace std;


map<string, int> mmap = {
    {"Jan", 0},
    {"Feb", 1},
    {"Mar", 2},
    {"Apr", 3},
    {"May", 4},
    {"Jun", 5},
    {"Jul", 6},
    {"Aug", 7},
    {"Sep", 8},
    {"Oct", 9},
    {"Nov", 10},
    {"Dec", 11}
};
string weekdays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int m_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool leap_year(int y) {
    return y % 400 == 0 || (y % 100 != 0 && y % 4 == 0);
}

/**
 * @brief 
 * 
 * @param d 
 * @param m [0, 11]
 * @param y 
 * @return string 
 */
string solve(int d, int m, int y) {
    int64_t days = 0;
    int ydiff = (y - 1900);
    int yrst = ydiff % 400;
    int yd400 = ydiff / 400;
    days = yd400 * (4 * (25 * 366 + 75 * 365) - 3);
    // cout << yd400 << " " << days << " ";

    int curry = 1900 + yd400 * 400;
    // cout << curry << " ";
    for (int r = 0; r < yrst; r++, curry++) {
        if (leap_year(curry)) {
            days += 366;
        }
        else {
            days += 365;
        }
    }
    // cout << curry << " " << days << " ";
    for (int i = 0; i < m; i++) {
        int md = m_days[i];
        if (md == 28 && leap_year(curry)) {
            md = 29;
        }
        days += md;
    }
    // cout << days << " ";
    days += d - 1;
    // cout << days << " ";
    // cout << endl;

    return weekdays[days % 7];
}

int main() {
    int day;
    string month;
    int year;
    while (cin >> day >> month >> year) {
        int m = mmap[month];
        cout << solve(day, m, year) << endl;
    }
    return 0;
}
