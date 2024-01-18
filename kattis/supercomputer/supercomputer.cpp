#include <bits/stdc++.h>
using namespace std;

typedef uint64_t ul;
typedef int64_t ll;
typedef vector<ll> vll;

class FenwickTree {
    int sz;
    vll ft;
    int lso(int x) {
        return x & -x;
    }
public:
    FenwickTree(int N) {
        sz = N + 1;
        ft.assign(N, 0);
    }
    void update(int i, int v) {
        for (; i < sz; i += lso(i)) ft[i] += v;
    }
    ll query(int i) {
        ll sum = 0;
        for (; i; i -= lso(i)) sum += ft[i];
        return sum;
    }
};

bitset<1000010> mem;


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    
    FenwickTree ft(n);
    mem.reset();

    char c;
    int l, r, bit;
    for (int i = 0; i < k; i++) {
        cin >> c;
        if (c == 'F') {
            cin >> bit;
            mem[bit].flip();
            if (mem[bit]) {
                ft.update(bit, 1);
            }
            else {
                ft.update(bit, -1);
            }
        }
        else {
            assert(c == 'C');
            cin >> l >> r;
            cout << ft.query(r) - ft.query(l - 1) << '\n';
        }
    }
    return 0;
}
