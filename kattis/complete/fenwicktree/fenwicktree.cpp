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

    FenwickTree ft(N);
    for (int i = 0; i < Q; i++) {
        char c;
        cin >> c;

        if (c == '+') {
            int n1; ll n2;
            cin >> n1 >> n2;

            ft.update(n1 + 1, n2);
        }
        else if (c == '?') {
            int v;
            cin >> v;
            cout << ft.query(v) << '\n';
        }
    }
    return 0;
}
