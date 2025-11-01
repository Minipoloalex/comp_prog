#include <bits/stdc++.h>
using namespace std;

int go(int b, int i,int bellow, int p, vector<vector<int>> &dp)
{

    if(i==p)
    {
        if(bellow)
            return 2;

        int ans  = 0;

        int x = b&((1LL<<(i+1))-1);
        long long f1 = (1LL<<(i+1))-1;
        auto f2 = f1>>1;

        ans += f1<=x;
        ans += f2<=x;

        return ans;
    }

    if(dp[i][bellow]!=-1)
        return dp[i][bellow];
    
    dp[i][bellow] = 0;

    for(int bit=0;bit<=1;++bit)
    {
        if(bellow)
            dp[i][bellow] += go(b,i-1,bellow,p,dp);
        else if(bit<bool(b&(1<<i)))
            dp[i][bellow] += go(b,i-1,1,p,dp);
        else if(bit==bool(b&(1<<i)))
            dp[i][bellow] += go(b,i-1,0,p,dp);
    }

    return  dp[i][bellow];
}

void solve() {
    int a,b,m;
    cin>>a>>b>>m;

    int p = 0;
    for(int i=0;i<=30;++i)
        if(m&(1<<i))
            p = i;
    
    vector<vector<int>> dp(31,vector<int>(2,-1));
    int ans = go(b,30,0,p,dp);
    //cout<<b<<": "<<ans<<endl;

    vector<vector<int>> dp2(31,vector<int>(2,-1));
    ans -= go(a-1,30,0,p,dp2);
    //cout<<a-1<<": "<<go(a-1,30,0,p,dp2)<<endl;

    cout<<ans<<endl;
    
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
