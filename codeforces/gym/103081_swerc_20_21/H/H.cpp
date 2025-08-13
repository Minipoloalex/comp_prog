#include <bits/stdc++.h>
using namespace std;


struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *_l, Vertex *_r) : l(_l), r(_r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(v->sum+new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}

void solve() {
    int n;
    cin>>n; cin.ignore();
    vector<int> st(n), end(n);
    
    for (int i = 1; i <= n; i++) {
        string s; getline(cin, s);

        istringstream iss(s);

        string x;
        while (iss >> x) {
            if (x[0] == '+') {
                int fig = stoi(x.substr(1));
                st[fig] = i;
            }

            if (x[0] == '-') {
                int fig = stoi(x.substr(1));
                end[fig] = i;
            }
        }
    }


    vector<int> days(n);
    for (auto &di: days) cin >> di;


    int a[n+1];
    for(int i=0;i<=n;++i)
        a[i] = 0;

    vector<Vertex*> roots = {build(a,0,n)};
    for(int i=n-1;i>=0;--i)
    {
        //a[st[i]]++;
        auto root = update(roots.back(),0,n,st[i],+1);

        //a[end[i]]--;
        root = update(root,0,n,end[i],-1);

        roots.push_back(root);
    }

    reverse(roots.begin(),roots.end());

    int x = 0;

    for(int i=0;i<n;++i)
    {
        //cout<<x<<"!"<<endl;
        auto root = roots[x];
        x = (x+get_sum(root,0,n,0,days[i]))%n;
        
    }
    cout<<x<<endl;

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
