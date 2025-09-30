#include <bits/stdc++.h>
using namespace std;
const int INF = int(1e9)+7;
#define sz(v) int((v).size())

typedef vector<int> vi;

/**
 * Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in O(1).
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V|log|V| + Q)
 */
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
    RMQ() {}
	RMQ(const vector<T> &V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			for (int j = 0; j < sz(jmp[k]); j++)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) { // end-exclusive: [a, b)
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};


void solve() {
    int n,k;
    cin>>n>>k;

    vector<int> a(n);
    for(int &x:a)
        cin>>x;

    vector<int> pref_min(n,INF), suf_min(n,INF);

    pref_min[0] = a[0];
    for(int i=1;i<n;++i)
        pref_min[i] = min(pref_min[i-1],a[i]);

    suf_min[n-1] = a[n-1];
    for(int i=n-2;i>=0;--i)
        suf_min[i] = min(suf_min[i+1],a[i]);
    
    for(int i=0;i<n;++i)
        a[i] += i;

    RMQ<int> s(a);
    
    int ans = -INF;

    for(int i=0;i<n;++i)
    {
        int tmp = INF;

        int l = max(0,i-k+1), r = i;

        if(l>0)
            tmp = min(tmp,pref_min[l-1]);
        if(r+1<n)
            tmp = min(tmp,suf_min[r+1]);
        
        int inc = k-i;

        tmp = min(tmp,s.query(l,r+1)+inc);

        ans = max(ans,tmp);
        //cout<<"MIN: "<<s.query(l,r+1)<<"_"<<tmp<<"--\n";
    }

    cout<<ans<<'\n';
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
