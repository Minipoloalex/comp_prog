#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> calc(string s)
{
    int n = s.size();
    vector<vector<int>> ans(26);
    int c = 1;
    for(int i=1;i<n;++i)
    {
        if(s[i]==s[i-1])
            c++;
        else 
        {
            ans[s[i-1]-'a'].push_back(c);
            c = 1;
        }
    }
    ans[s.back()-'a'].push_back(c);
    return ans;
}

void solve() {
    string s;
    cin>>s;
    auto v = calc(s);
    long long ans = 1;
    for(int i=0;i<v.size();++i)
    {
        long long sum = 0; 
        for(int x:v[i])
        {
            ans += sum*x;
            ans += x;
            sum += x;
        }
    }
    cout<<ans<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
