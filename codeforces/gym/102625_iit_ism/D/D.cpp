#include <bits/stdc++.h>
using namespace std;
#define MAX 1000000
int dp[MAX+10];

int go(int n)
{
    if(n==1)
        return 1;
    if(dp[n]!=-1)
        return dp[n];
    dp[n] = 1+go(n-1);
    if(n%2==0)
        dp[n] = min(dp[n],1+go(n/2));
    if(n%3==0)
        dp[n] = min(dp[n],1+go(n/3));
    return dp[n];
}
void restore(int n,vector<int>&ans)
{
    ans.push_back(n);
    if(n==1)
        return;
    int x = go(n);
    if(x==1+go(n-1))
    {
        restore(n-1,ans);
        return;
    }
    if(n%2==0&&x==1+go(n/2))
    {
        restore(n/2,ans);
        return;
    }
    assert(n%3==0&&x==1+go(n/3));
    restore(n/3,ans);
}
void solve() {
    int n;
    cin>>n;
    cout<<go(n)<<endl;
    vector<int> ans;
    restore(n,ans);
    reverse(ans.begin(),ans.end());
    for(int x:ans)
        cout<<x<<" ";
    cout<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    for(int i=0;i<=MAX;++i)
        dp[i] = -1;
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
