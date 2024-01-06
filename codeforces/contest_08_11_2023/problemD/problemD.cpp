#include <bits/stdc++.h>
using namespace std;

typedef set<int> vi;

vi v;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            v.insert(ai);
        }
        sort(v.begin(), v.end());
        bool is_balanced = true;
        for (int i = 1; i < n; i++) {

        }
    }    
    return 0;
}
