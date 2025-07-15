#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(int &x:a)cin>>x;
        vector<int> nxt(n,n);
        stack<int> stk;
        for(int i=n-1;i>=0;--i)
        {
            while(!stk.empty()&&a[stk.top()]<=a[i])
                stk.pop();
            if(!stk.empty())
                nxt[i] = stk.top();
            stk.push(i);
        }
        vector<long long> dp(n);
        for(int i=n-1;i>=0;--i)
        {
            int j = nxt[i];
            if(j==n||a[j]!=(a[i]+1))
                dp[i] = (a[i]+1)*1LL*(n-i);
            else 
                dp[i] = (a[i]+1)*1LL*(j-i)+dp[j];
        }
        long long ans = 0;
        for(int i=0;i<n;++i)
            if(a[i]==0)
                ans += dp[i];
        cout<<ans<<endl;
    }
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
