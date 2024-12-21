#include <bits/stdc++.h>
using namespace std;


#define LSB(i) ((i) & -(i))

class FT {
public:
    int n;
    vector<int64_t> ft;
public:
    FT(int _n) {
        n = _n;
        ft.assign(n + 1, 0);
    }
    int64_t get(int i) {
        int64_t ans = 0;
        for (; i; i -= LSB(i)) {
            ans += ft[i];
        }
        return ans;
    }
    int64_t get(int l, int r) {
        return get(r) - get(l - 1);
    }
    void add(int i, int64_t value) {
        for (; i <= n; i += LSB(i)) {
            ft[i] += value;
        }
    }
    void build(vector<int64_t> &v) {
        for (int i = 0; i < n; i++) {
            add(i + 1, v[i]);
        }
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int64_t> v(n);
    for (auto &x: v) cin >> x;

    FT ft(n);
    ft.build(v);

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            int64_t diff = b - v[a - 1];
            v[a - 1] = b;

            ft.add(a, diff);
        }
        else {
            assert(type == 2);
            cout << ft.get(a, b) << '\n';
        }
    }
    return 0;
}