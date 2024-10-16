#include <bits/stdc++.h>
using namespace std;

int n;
string s;

pair<int64_t, int> process(int idx, bool ignore_mult) {
    int open = 0;
    int64_t curr = 0;

    int i = idx;

    while (i < n) {
        if (!ignore_mult && i - 1 >= 0 && s[i - 1] == ')' && s[i] == '(') {
            open++;
            auto p = process(i, true);
            curr *= p.first;
            i = p.second;
        }
        else if (i + 1 < n && s[i] == '(' && s[i + 1] == '(') {
            open++;
            auto p = process(i + 1, ignore_mult);
            curr += p.first; i = p.second;
        }
        else if (s[i] == '(') {
            open++;
            i++;
        }
        else if (open > 0 && s[i] == ')') {
            return {curr + 1, i + 1};
        }
        ignore_mult = false;
    }

    return {curr, i};
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin >> n;
    cin >> s;

    int i = 0;
    int64_t ans = 1;
    while (i < n) {
        auto [curr, idx] = process(i, true);
        // cout << i << " " << idx << " " << curr << endl;
        ans *= curr;
        i = idx;
    }
    cout << ans << '\n';
    // cout << idx << '\n';
    return 0;
}
