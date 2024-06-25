#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> ind;
        string s, c;
        cin >> s;

        unordered_set<int> myset;
        int count_repeated = 0;
        for (int i = 0; i < m; i++) {
            int index;
            cin >> index;
            index--;

            if (myset.find(index) == myset.end()) {
                myset.insert(index);
                ind.push_back(index);
            } else count_repeated++;
        }
        cin >> c;
        m = (int) myset.size();

        sort(ind.rbegin(), ind.rend());
        sort(c.rbegin(), c.rend());
        // for (int i = 0; i < m; i++) {
        //     cout << ind[i] << " ";
        // }
        // cout << endl;
        for (int i = 0; i < m; i++) {
            int index = ind[i];

            char value = c[i + count_repeated];
            s[index] = value;
        }
        cout << s << '\n';
    }
    return 0;
}
