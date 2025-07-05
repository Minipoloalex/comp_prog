#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    vector<int> v(n);
    for(int &x:v)cin>>x;
    map<int,int> mp;
    vector<int> dp(n+1,0);
    for(int i=n-1;i>=0;--i)
    {
        auto it = mp.find(v[i]);
        if(it!=mp.end())
        {
            dp[i] = 1+min(dp[i+1],it->second);
            mp[v[i]] = min(mp[v[i]],dp[i+1]);
        }
        else
        {
            dp[i] = 1+dp[i+1];
            mp[v[i]] = dp[i+1];
        }
    }
    cout<<dp[0]<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
