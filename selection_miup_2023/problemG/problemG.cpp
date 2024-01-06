#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n, c;
    cin >> n >> c;
    c = min(c, n);   // each customer wants at least on baguette
    
    vvi dp(n, vi(n, 0));    // [left, right]
    vi bag(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> bag[i];
    }
    for (int left = 0; left < n; left++) {
        for (int right = 0; right < n; right++) {
            // choose left
            
        }
    }
    return 0;
}
