#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin>>s;
    int n = s.size();
    int ans = n;
    int c[] = {0,0,0};
    c[s[0]-'a']++;
    int l = 0, r = 1;
    while(r<=n)
    {
        if(min({c[0],c[1],c[2]})>0)
        {
            c[s[l]-'a']--;
            l++;
        }
        else 
        {
            if(r==n)
                break;
            c[s[r]-'a']++;
            r++;
        }
        if(min({c[0],c[1],c[2]})>0)
            ans = min(ans,r-l);
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
