
#include <bits/stdc++.h>
#define MAX 60
#define P 10000
using namespace std;
int v[MAX+10], target;
long long dp[MAX+10][P*MAX+10];
int n;
long long go(int i, int sm)
{
    if(sm>=target)
        return 1;
    if(i==n)
        return 0;
    if(dp[i][sm]!=-1)
        return dp[i][sm];
    return dp[i][sm] = go(i+1, sm)+go(i+1,sm+v[i]);
}
void solve() {
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>v[i], target += v[i];
    sort(v,v+n,greater<int>());
    for(int i=0;i<n;++i)    
        for(int j=0;j<=target;++j)
            dp[i][j] = -1;
    target /= 2;
    target++;
    cout<<go(0,0)<<endl;
    /*for(int i=0;i<n;++i)
        for(int j=0;j<=target;++j)
            cout<<"DP["<<i<<"]["<<j<<']'<<" = "<<dp[i][j]<<endl;*/
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