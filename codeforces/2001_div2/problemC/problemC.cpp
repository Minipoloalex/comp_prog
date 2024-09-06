#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int ask(int a, int b) {
    cout << "? " << a << " " << b << endl;
    cout.flush();
    int x;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> seen(n + 1, 0);
        seen[1] = 1;
        set<int> s;
        for (int i = 2; i <= n; i++) s.insert(i);

        vector<ii> edges;
        while (int(edges.size()) < n - 1) {
            int a = 1, b = *s.begin();
            if (seen[b]) {  // only remove once confirmed as "seen" (in the tree)
                s.erase(s.begin());
                continue;
            }

            while (true) {
                int x = ask(a, b);

                if (x == a) {
                    seen[b] = 1;
                    edges.emplace_back(a, b);
                    break;
                }
                else if (seen[x]) {  // look in [x, b]
                    a = x;
                }
                else {  // look in [1, x]
                    b = x;
                }
            }
        }
        cout << "!";
        for (auto &[a, b]: edges) {
            cout << " " << a << " " << b;
        }
        cout << endl;
    }
    return 0;
}
