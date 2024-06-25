#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;
        // cout << "'" << s << "'" << endl;
        if (n >= 4 || (n == 3 && s[1] != '0')) {
            bool result_found = false;
            for (int i = 0; i < n; i++) {
                if (s[i] == '0') {
                    cout << 0 << '\n';
                    result_found = true;
                    break;
                }
            }
            if (result_found) continue;
        }

        int smallest_nr = INT_MAX;
        int smallest_nr_idx = -1;

        int second_smallest_nr = INT_MAX;
        int second_smallest_idx = -1;
        for (int i = 0; i < n - 1; i++) {
            int n1 = s[i] - '0', n2 = s[i + 1] - '0';
            int candidate = n1 * 10 + n2;
            if (candidate < smallest_nr) {
                second_smallest_nr = smallest_nr;
                second_smallest_idx = smallest_nr_idx;

                smallest_nr = candidate;
                smallest_nr_idx = i;                
            }
            else if (candidate < second_smallest_nr && candidate != smallest_nr) {
                second_smallest_idx = i;
                second_smallest_nr = candidate;
            }
        }
        // if (smallest_nr % 10 == 1 && second_smallest_nr - smallest_nr == 1) {
        //     smallest_nr = second_smallest_nr;
        //     smallest_nr_idx = second_smallest_idx;
        // }

        // cout << "Smallest: " << smallest_nr << endl;
        auto get_total = [&](int nr_idx, int nr) {
            int total = 0;
            for (int i = 0; i < n; ) {
                if (i == nr_idx) {
                    if (nr == 1) { // will only happen if n = 3 or n = 2, because 01
                        if (total == 0) {
                            total = 1;
                        }
                    }
                    else {
                        total += nr;
                    }
                    i += 2;
                }
                else {
                    if (s[i] == '1') {

                    }
                    else {
                        total += s[i] - '0';
                    }
                    i++;
                }
            }
            return total;
        };
        int total = get_total(smallest_nr_idx, smallest_nr);
        // cout << smallest_nr << " " << smallest_nr_idx << endl;
        if (second_smallest_idx != -1) {
            total = min(total, get_total(second_smallest_idx, second_smallest_nr));
        }
        cout << total << endl;

        // int total = 0;
        // for (int i = 0; i < n; ) {
        //     if (i == smallest_nr_idx) {
        //         if (smallest_nr == 1) { // will only happen if n = 3 or n = 2, because 01
        //             if (total == 0) {
        //                 total = 1;
        //             }
        //         }
        //         else {
        //             total += smallest_nr;
        //         }
        //         i += 2;
        //     }
        //     else {
        //         if (s[i] == '1') {

        //         }
        //         else {
        //             total += s[i] - '0';
        //         }
        //         i++;
        //     }
        // }
        // cout << total << endl;
    }
    return 0;
}
