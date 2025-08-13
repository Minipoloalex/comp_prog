#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    int ans = INT_MAX;
    while(n--)
    {
        int x,y;
        cin>>x>>y;
        y /= x;
        ans = min(ans,y);
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
