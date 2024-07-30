#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> days(m, vector<int>());

        for (int i = 0; i < m; i++) {
            int ki;
            cin >> ki;
            for (int j = 0; j < ki; j++) {
                int f;
                cin >> f;
                days[i].push_back(f);
            }
        }
        int limit = (m + 1) / 2;

        vector<int> friends_freq(n, 0);
        for (int i = 0; i < m; i++) {   // get the most repeated friend
            int v = days[i].back();
            friends_freq[v - 1]++;
        }

        int target = -1;
        int target_freq = -1;

        for (int i = 0; i < n; i++) {
            if (friends_freq[i] > limit) {
                target = i + 1;
                target_freq = friends_freq[i];
                break;
            }
        }

        auto print_solution = [&](vector<vector<int>> &sol) {
            cout << "YES" << '\n';
            for (int i = 0; i < m; i++) {
                cout << sol[i].back() << " ";
            }
            cout << '\n';
        };

        if (target == -1) {
            // cout << "NO TARGET" << '\n';
            print_solution(days);
            continue;
        }

        for (int i = 0; i < m && target_freq > limit; i++) {
            vector<int> &day = days[i];
            if (day.size() >= 2 && day.back() == target) {
                day.pop_back();
                target_freq--;
            }
        }

        if (target_freq > limit) cout << "NO" << '\n';
        else print_solution(days);
    }
    return 0;
}
