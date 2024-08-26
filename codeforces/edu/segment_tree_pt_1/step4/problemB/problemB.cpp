#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t ll;

struct item {
    ll a1, a2;
    ll b1, b2;
};

int64_t MOD;

void print_item(item &a) {
    cout << (a.a1 + MOD) % MOD << " " << (a.a2 + MOD) % MOD << '\n';
    cout << (a.b1 + MOD) % MOD << " " << (a.b2 + MOD) % MOD << '\n';
}

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 * 
 */
class SegmentTree {
private:
    item NEUTRAL_ELEMENT = {.a1=1, .a2=0, .b1=0, .b2=1};    // EMPTY SEGMENT (ID matrix)

    item combine(item &a, item &b) {
        return {
            .a1= ((a.a1 * b.a1) % MOD + (a.a2 * b.b1) % MOD) % MOD,
            .a2 = ((a.a1 * b.a2) % MOD + (a.a2 * b.b2) % MOD) % MOD,
            .b1 = ((a.b1 * b.a1) % MOD + (a.b2 * b.b1) % MOD) % MOD,
            .b2 = ((a.b1 * b.a2) % MOD + (a.b2 * b.b2) % MOD) % MOD
        };
    }
// private:
public:
    int64_t size;   // 2 * n (size of the segment tree array)
    int64_t n;      // size of the "original" array (counts additionally added)
    vector<item> st;
    /**
     * @brief All indices are inclusive
     * 
     * @param i 
     * @param j 
     * @param l 
     * @param r 
     * @return true 
     * @return false 
     */
    bool outside(int64_t l, int64_t r, int64_t i, int64_t j) {
        return j < l || r < i;
    }
    /**
     * @brief All indices are inclusive
     * 
     * @param i 
     * @param j 
     * @param l 
     * @param r 
     * @return true 
     * @return false 
     */
    bool inside(int64_t l, int64_t r, int64_t i, int64_t j) {
        return i <= l && r <= j;
    }
    void build(vector<item> &items, int64_t current, int64_t l, int64_t r) {
        if (l == r) {
            if (l < (int64_t) items.size()) st.at(current) = items.at(l);
            else st.at(current) = NEUTRAL_ELEMENT;
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        build(items, leftC, l, m);
        build(items, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
    }
    /**
     * @brief 
     * 
     * @param i Index of the starting array to set. Does not correspond to the node's index.
     * Instead corresponds to the node's limits.
     * @param value Value to set node with limits [i, i]
     * @param current Current node index
     * @param l Current node's left limit
     * @param r Current node's right limit
     */
    void update(int64_t i, item value, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) = value;
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
    }

    item get(int64_t i, int64_t j, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, j)) return NEUTRAL_ELEMENT;
        if (inside(l, r, i, j)) return st.at(current);

        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        auto rl = get(i, j, leftC, l, m);
        auto rr = get(i, j, rightC, m + 1, r);
        return combine(rl, rr);
    }

public:
    SegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        // do not need to set this here: we can just not assign anything
        // the get function will return the default value
        // st.assign(size, make_pair(INT_MAX, 0));
        st.resize(size);
    }
    /**
     * @brief
     * 
     * @param i 0-indexed
     * @param value 
     */
    void update(int64_t i, item &value) {
        update(i, value, 1, 0, n - 1);
    }
    /**
     * @brief 
     * 
     * @param i 
     * @param j 
     */
    item get(int64_t i, int64_t j) {
        return get(i, j, 1, 0, n - 1);
    }
    void build(vector<item> &items) {
        build(items, 1, 0, n - 1);
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(0);

    int n, m;
    cin >> MOD >> n >> m;

    SegmentTree st(n);
    vector<item> mtxs(n);
    for (int i = 0; i < n; i++) {
        int a1, a2, b1, b2;
        cin >> a1 >> a2 >> b1 >> b2;
        item mat = {.a1=a1,.a2=a2,.b1=b1,.b2=b2};
        mtxs[i] = mat;
    }
    st.build(mtxs);

    while (m--) {
        int64_t i, j;
        cin >> i >> j;
        i--;
        j--;
        item ans = st.get(i, j);
        print_item(ans);
        cout << '\n';
    }
    return 0;
}


// (2e5 + 2e5 * log(2e5)) * 4 = 8e5 + 2e7 = 2e7

// 2e5 * 4 + 2e5 * 2 + 2e5 * 4 = 2e6
