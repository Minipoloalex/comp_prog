#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    int cur = 100;
    int ans = cur;
    while(n--)
    {
        int x;
        cin>>x;
        cur += x;
        ans = max(ans,cur);
    }
    cout<<ans<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
