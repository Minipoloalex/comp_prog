#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    vector<int> x(n),y(n);
    for(int i=0;i<n;++i)
        cin>>x[i]>>y[i];
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    if(n&1)
        cout<<x[n/2]<<" "<<y[n/2]<<endl;
    else 
        cout<<x[n/2-1]<<" "<<y[n/2-1]<<endl;
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
