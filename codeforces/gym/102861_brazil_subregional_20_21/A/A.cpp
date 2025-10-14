#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n,a,b;
    cin>>n>>a>>b;
    if(a==0)
    {
        double E = 0;

        vector<double> ps(n+1);

        for(int i=1;i<=n;++i)
        {
            double sum = 0;

            if(i-(a+1)>=0)
                sum += ps[i-(a+1)];
            if(i-b>0)
                sum -= ps[i-b-1];

            E = ((b-a+1)+sum)/(b-a);

            ps[i] = (E+ps[i-1]);
        }
        
        cout<<fixed<<setprecision(10)<<E<<endl;
    }
    else
    {
        double E = 0;

        vector<double> ps(n+1);

        for(int i=1;i<=n;++i)
        {
            double sum = 0;

            if(i-a>=0)
                sum += ps[i-a];
            if(i-b>0)
                sum -= ps[i-b-1];

            E = 1+sum/(b-a+1);

            ps[i] = (E+ps[i-1]);
        }

        cout<<fixed<<setprecision(10)<<E<<endl;
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
