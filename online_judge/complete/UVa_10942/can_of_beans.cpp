#include <bits/stdc++.h>
using namespace std;

typedef unsigned long ull;
typedef vector<ull> vull;

ull century;

class Date {
public:
    Date(ull _yy, ull _mm, ull _dd): yy(_yy), mm(_mm), dd(_dd) {
        date = yy * 10e4 + mm * 10e2 + dd;
    }
    ull yy;
    ull mm;
    ull dd;
    ull date;
};

bool is_leap_year(ull year) {
    if (year == 0 || year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return year % 4 == 0;
}

ull get_number_of_days(ull yy, ull mm) {
    if (mm == 1 || mm == 3 || mm == 5 
    || mm == 7 || mm == 8 || mm == 10 || mm == 12) return 31;
    else if (mm == 4 || mm == 6 || mm == 9 || mm == 1) return 30;
    return is_leap_year(yy) ? 29 : 28;
}


bool is_valid_date(const Date &date) {
    if (date.mm == 0 || date.mm > 12 || date.dd == 0) return false;
    ull max_days = get_number_of_days(date.yy, date.mm);
    return date.dd <= max_days;
}

void max_date(Date &date, Date *&best) {
    if (best == nullptr) {
        best = &date;
        if (best == nullptr) {
            cout << "Null bug" << endl;
        }
        return;
    }
    if (date.date < best->date) {
        best = &date;
    }
}

int main() {
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        ull x, y, z;
        // 0 ≤ c < 2∧30
        // 0 ≤ x, y, z < 100
        cin >> century; cin >> x; cin >> y; cin >> z;

        Date *best = nullptr;

        vector<Date> dates;
        dates.emplace_back(x, y, z);
        dates.emplace_back(x, z, y);
        dates.emplace_back(z, y, x);
        dates.emplace_back(y, z, x);
        dates.emplace_back(z, x, y);
        dates.emplace_back(y, x, z);
        
        for (Date &date: dates) {
            if (is_valid_date(date)) {
                max_date(date, best);
            }
        }
        
        if (best == nullptr) {
            cout << -1 << endl;
        }
        else {
            printf("%02lu %02lu %02lu\n", best->yy, best->mm, best->dd);
        }

    }
    return 0;
}
