#include <bits/stdc++.h>
using namespace std;


int cnt(int x, int divi) {    // how many are divisable
    return x / divi;
}

void solve() {
    int a,b,m;
    cin>>a>>b>>m;

    int p = 0;
    for(int i=0;i<=30;++i)
        if(m&(1<<i))
            p = i;

    int ans = cnt(b+1, 1 << p) - cnt(a, 1 << p);
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
