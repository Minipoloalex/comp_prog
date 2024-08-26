#include <bits/stdc++.h>
using namespace std;

#define lc(i) (2 * (i))
#define rc(i) (2 * (i) + 1)

class SegmentTree {
public:
    int n;  // not size of st array, n is number of leaves
    vector<int> st;
    int NEUTRAL_ELEMENT = INT_MAX;

    SegmentTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        st.assign(2 * n, NEUTRAL_ELEMENT);
    }
    bool outside(int l, int r, int i, int j) {
        return r < i || l > j;
    }
    int combine(int a, int b) {
        return min(a, b);
    }
    void update(int i, int value, int current, int l, int r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) = value;
            return;
        }

        int left = lc(current);
        int right = rc(current);
        int m = (l + r) / 2;

        update(i, value, left, l, m);
        update(i, value, right, m + 1, r);

        st.at(current) = combine(st.at(left), st.at(right));
    }
    int get(int i, int j, int p, int current, int l, int r) {
        if (outside(l, r, i, j)) return 0;
        if (st.at(current) > p) return 0;

        if (l == r) {
            if (st.at(current) <= p) {
                st.at(current) = NEUTRAL_ELEMENT;
                return 1;
            }
            return 0;
        }
        int left = lc(current);
        int right = rc(current);
        int m = (l + r) / 2;

        int rl = get(i, j, p, left, l, m);
        int rr = get(i, j, p, right, m + 1, r);
        st.at(current) = combine(st.at(left), st.at(right));

        return rl + rr;
    }
    int get(int i, int j, int p) {
        return get(i, j, p, 1, 0, n - 1);
    }
    void update(int i, int value) {
        update(i, value, 1, 0, n - 1);
    }
};

int main()  {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    SegmentTree st(n);
    while (m--) {
        // for (int v: st.st) {
        //     cout << v << " ";
        // }
        // cout << endl;
        int op;
        cin >> op;
        if (op == 1) {
            int i, h;
            cin >> i >> h;
            st.update(i, h);
        }
        else {
            assert(op == 2);
            int l, r, p;
            cin >> l >> r >> p;
            int cnt = st.get(l, r - 1, p);
            cout << cnt << '\n';
        }
    }
    return 0;
}
