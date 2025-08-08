#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    map<string,int> mp;
    for(int i=0;i<n;++i)
    {
        string s;
        cin>>s;
        mp[s]++;
    }
    for(auto [s,f]:mp)
    {
        int m = n-f;
        if(f>m)
        {
            cout<<s<<endl;
            return;
        }
    }
    cout<<"NONE"<<endl;
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
