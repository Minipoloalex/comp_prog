#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef set<int> si;
si s;
vi a;

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        s.clear();
        a.clear();
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            s.insert(ai);
        }
        int sz = (int) s.size();

        for (int v: s) {
            a.push_back(v);
        }

        int solution = 1;

        for (int currIndex = 0; currIndex < sz; currIndex++) {
            int curr = a[currIndex];

            int l = currIndex, u = sz - 1;
            while (l <= u) {
                if (u - currIndex + 1 <= solution) {
                    break;
                }
                int middle = (u + l) / 2;
                if (a[middle] - curr < n) {
                    int possible_sol = middle - currIndex + 1;
                    if (possible_sol > solution) {
                        solution = possible_sol;
                    }
                    l = middle + 1;
                }
                else {
                    u = middle - 1;
                }
            }
        }
        cout << solution << '\n';
    }
    
    return 0;
}
