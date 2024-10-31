#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        int ans = INT_MAX;
        if (n % 2 == 0) {   // cannot use delete
            vvi freq(2, vi(26, 0));
            for (int i = 0; i < n; i++) {
                freq[i % 2][s[i] - 'a']++;
            }
            ans = 0;
            for (int j = 0; j < 2; j++) {
                int mx = 0;
                for (int i = 0; i < 26; i++) {
                    mx = max(mx, freq[j][i]);
                }
                ans += (n / 2) - mx;
            }
        }
        else {  // must use delete
            vvi pref(n, vi(26, 0));
            vvi suf(n, vi(26, 0));
            for (int i = 0; i < n; i++) {
                if (i >= 2) pref[i] = pref[i - 2];  // even: i >= 2, odd: i >= 3
                pref[i][s[i] - 'a']++;
            }
            for (int i = n - 1; i >= 0; i--) {
                // since we delete one character and the original size is odd, then the last value "will have an odd index"

                if (i <= n - 3) {   // [1, 2, ..., n-4, n-3, n-2, n-1]. even: i <= n - 4, odd: n <= n - 3
                    suf[i] = suf[i + 2];
                }
                suf[i][s[i] - 'a']++;
            }

            int odds_after = n / 2, evens_after = n / 2;
            int odds_before = 0, evens_before = 0;
            for (int i = 0; i < n; i++) {   // delete i
                int min_odds = INT_MAX, min_evens = INT_MAX;
                for (int ch = 0; ch < 26; ch++) {
                    int total_odd_diff = 0, total_even_diff = 0;

                    if (i % 2 == 0) {
                        if (i - 1 >= 0) {
                            int correct_odds_before = pref.at(i - 1).at(ch);
                            total_odd_diff += odds_before - correct_odds_before;
                        }
                        if (i - 2 >= 0) {
                            int correct_evens_before = pref.at(i - 2).at(ch);
                            total_even_diff += evens_before - correct_evens_before;
                        }
                        if (i + 1 < n) {
                            int correct_evens_after = suf.at(i + 1).at(ch);
                            total_even_diff += evens_after - correct_evens_after;
                        }
                        if (i + 2 < n) {
                            int correct_odds_after = suf.at(i + 2).at(ch);
                            total_odd_diff += odds_after - correct_odds_after;
                        }
                    }
                    else {
                        if (i - 1 >= 0) {
                            int correct_evens_before = pref.at(i - 1).at(ch);
                            total_even_diff += evens_before - correct_evens_before;
                        }
                        if (i - 2 >= 0) {
                            int correct_odds_before = pref.at(i - 2).at(ch);
                            total_odd_diff += odds_before - correct_odds_before;   
                        }
                        if (i + 1 < n) {
                            int correct_odds_after = suf.at(i + 1).at(ch);
                            total_odd_diff += odds_after - correct_odds_after;
                        }
                        if (i + 2 < n) {
                            int correct_evens_after = suf.at(i + 2).at(ch);
                            total_even_diff += evens_after - correct_evens_after;
                        }
                    }
                    min_evens = min(min_evens, total_even_diff);
                    min_odds = min(min_odds, total_odd_diff);
                }

                if (i % 2 == 0) evens_after--, evens_before++;
                else odds_after--, odds_before++;
                ans = min(ans, min_odds + min_evens);
            }
            ans++;  // don't forget to count required delete operation
        }
        // if (n % 2 == 1) cout << "Odd: ";
        // else cout << "Even: ";
        cout << ans << '\n';
    }
    return 0;
}
