#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;
typedef uint64_t ul;
typedef vector<ll> vll;
class FenwickTree {
    vll ft;
    int sz;

    int lso(int x) { return x & -x; }
public:
    FenwickTree(int N) {
        sz = N + 1;
        ft.assign(N + 1, 0);
    }

    void update(int i, ll v) {
        for (; i < sz; i += lso(i)) ft[i] += v;
    }

    ll query(int i) {
        ll sum = 0;
        for (; i; i -= lso(i)) sum += ft[i];
        return sum;
    }
};

int main() {
    cin.tie(NULL); ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    int values[7];
    for (int i = 1; i <= 6; i++) {
        cin >> values[i];
    }
    string l;
    cin >> l;
    vector<FenwickTree> vt(7, FenwickTree(N));
    for (int i = 0; i < (int) l.size(); i++) {
        int v = l[i] - '0';
        vt[v].update(i + 1, 1);
    }
    
    ll sum;
    char ch;
    for (int i = 0; i < Q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        switch (a) {
            case 1:
                // replace Ki gem with gem of type Pi (Ki = b, Pi = c)
                ch = l[b - 1];
                l[b - 1] = (char) c + '0';
                vt[ch - '0'].update(b, -1);
                vt[c].update(b, 1);
                break;
            case 2:
                // revalue gem
                values[b] = c;
                break;
            case 3:
                // get gem values between L and R (b and c)
                sum = 0;
                for (int j = 1; j < (int) vt.size(); j++) {
                    auto &ft = vt[j];
                    sum += (ft.query(c) - ft.query(b - 1)) * values[j];
                }
                cout << sum << '\n';
                break;
        }
    }
    return 0;
}
