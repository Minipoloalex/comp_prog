#include <bits/stdc++.h>
using namespace std;

#define LSO(n) ((n) & (-(n)))

class FenwickTreePURQ {
private:
    int64_t size;
    vector<int64_t> ft;

    int64_t get(int64_t i) {
        int64_t sum = 0;
        for (; i; i -= LSO(i)) sum += ft[i];
        return sum;
    }
    void update(int64_t i, int64_t value) {
        for (; i < size; i += LSO(i)) ft[i] += value;
    }
    int64_t get(int64_t i, int64_t j) {
        return get(j) - get(i - 1);
    }
public:
    FenwickTreePURQ(int64_t n) {
        size = n + 1;
        ft.assign(size, 0);
    }
    int64_t point_query(int64_t i) {
        return get(i);
    }
    void range_update(int64_t i, int64_t j, int64_t v) {
        update(i, v);
        update(j + 1, -v);
    }
    void print_ft() {
        for (int64_t v: ft) {
            cout << v << " ";
        }
        cout << endl;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    FenwickTreePURQ ft(n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int64_t l, r, v;
            cin >> l >> r >> v;
            ft.range_update(l + 1, r, v);   // range_update uses 1-indexing (and inclusive indices)
            // ft.print_ft();
        }
        else {
            assert(op == 2);
            int64_t i;
            cin >> i;
            cout << ft.point_query(i + 1) << '\n';
        }
    }
    return 0;
}
