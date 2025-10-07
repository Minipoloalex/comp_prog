#include <bits/stdc++.h>
using namespace std;
const int MAX = 2000;
const long long INF = 1e18;
int n,k,x;
int a[MAX+10],b[MAX+10],c[MAX+10], d[MAX+10];
long long dp[MAX+10][5];
long long go(int i,long long rating)
{
    if(i==n)    
        return rating;

    if(abs(rating-x)<=k)
    {
        auto j = rating-x+k;
        if(dp[i][j]!=-1)
            return dp[i][j];
        dp[i][j] = -INF;
        if(min(c[i],d[i])==0)
            dp[i][j] = max(dp[i][j],go(i+1,rating-b[i]));
        if(max(c[i],d[i])==1)
            dp[i][j] = max(dp[i][j],go(i+1,rating+a[i]));
        return dp[i][j];
    }

    //Simulation
    
    if(rating<x-k)
    {
        if(c[i]==0)
            return go(i+1,rating-b[i]);
        return go(i+1,rating+a[i]);
    }

    //if(rating<x+k)
    if(d[i]==0)
        return go(i+1,rating-b[i]);
    return go(i+1,rating+a[i]);
}
void solve() {
    cin>>n>>k>>x;
    for(int i=0;i<n;++i)
        cin>>a[i]>>b[i]>>c[i]>>d[i];
    for(int i=0;i<n;++i)
        for(int j=0;j<5;++j)
            dp[i][j] = -1;
    cout<<go(0,x)<<endl;
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
