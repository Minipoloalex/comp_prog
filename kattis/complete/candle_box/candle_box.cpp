#include <bits/stdc++.h>
using namespace std;

int get_sum_arithmetic_progression(int a1, int r, int n) {
    // an = a1 + (n - 1) * r
    return (a1 + a1 + (n-1)*r)*n / 2;
}

bool is_valid_age(int age, int sec_age, int R, int T) {
    // int r_should = (age + 4) * age / 2;
    // int t_should = (sec_age + 3) * sec_age / 2;
    int r_should = get_sum_arithmetic_progression(4, 1, age - 3);
    int t_should = get_sum_arithmetic_progression(3, 1, sec_age - 2);
    return r_should + t_should == R + T;
}

int main() {
    int d, r, t;
    cin >> d >> r >> t;

    int age = -1;
    for (int i = 4; i < 1000; i++) {
        if (is_valid_age(i, i - d, r, t)) {
            age = i;
            break;
        }
    }
    if (age == -1) throw invalid_argument("RTE");
    int r_should = get_sum_arithmetic_progression(4, 1, age - 3);
    cout << r - r_should << endl;
    return 0;
}
