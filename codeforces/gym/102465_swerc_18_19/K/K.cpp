#include <bits/stdc++.h>
using namespace std;

//  z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
// For S = "aabxaayaab", Z = [10, 1, 0, 0, 2, 1, 0, 3, 1, 0] (same size as S)
vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = (int) s.size();

	int l = 0, r = 0;
	for (int i = 1; i < (int) s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}
	return z;
}

int calc_period(string &s)
{
    vector<int> z = z_function(s);    
    int n = s.size();
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n) {
            if(n%i==0)  
                return i;
        }
    }
    return 0;
}
int go(int l,int r,vector<vector<int>> &dp, vector<vector<int>> &period)
{
    if(l==r)
        return 1;
    if(dp[l][r]!=-1)
        return dp[l][r];
    dp[l][r] = r-l+1;
    if(period[l][r]>0)
        dp[l][r] = go(l,l+period[l][r]-1,dp,period);
    for(int m=l;m<r;++m)
        dp[l][r] = min({dp[l][r],go(l,m,dp,period)+go(m+1,r,dp,period)});
    return dp[l][r];
}
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> period(n,vector<int>(n,0));
    vector<vector<int>> dp(n,vector<int>(n,-1));
    for(int i=0;i<n;++i)
    {
        string t = "";
        for(int j=i;j<n;++j)
        {
            t += s[j];
            period[i][j] = calc_period(t);
            //cout<<t<<": "<<period[i][j]<<endl;
        }
    }
    cout<<go(0,n-1,dp,period)<<endl;
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
