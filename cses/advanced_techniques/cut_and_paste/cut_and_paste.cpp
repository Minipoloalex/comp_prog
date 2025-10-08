#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, INT_MAX);

struct Node {
    Node *l = 0, *r = 0;
    int val, prio, c;
    Node(int v): val(v), prio(gen(rng)), c(1) {}
};

int getsz(Node *t) {
    return t ? t->c : 0;
}
void recalc(Node *t) {
    if (t) t->c = 1 + getsz(t->l) + getsz(t->r);
}

// Precondition: all keys in L < all keys in R
Node* merge(Node *L, Node *R) {
    if (!L) return R;
    if (!R) return L;
    if (L->prio > R->prio) {    // L is the main root
        L->r = merge(L->r, R);
        recalc(L);
        return L;
    }
    else {  // R is the main root
        R->l = merge(L, R->l);
        recalc(R);
        return R;
    }
}

// Split by position: first k elements go to L, rest to R
pair<Node*, Node*> split(Node *t, int k) {
    if (!t) return {nullptr, nullptr};
    if (getsz(t->l) < k) {
        auto [L, R] = split(t->r, k - getsz(t->l) - 1);
        t->r = L;
        recalc(t);
        return {t, R};
    }
    else {
        auto [L, R] = split(t->l, k);
        t->l = R;
        recalc(t);
        return {L, t};
    }
}

template<class F> void each(Node *t, F f) {
    if (t) { each(t->l, f); f(t->val); each(t->r, f); }
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    Node *root = nullptr;
    for (char c: s) {
        Node *node = new Node(c);
        root = merge(root, node);
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        // L:   [0, a)
        // mid: [a, n)
        // cut: [a, b + 1)
        auto [L, mid] = split(root, a);
        auto [cut, R] = split(mid, b - a + 1);
        root = merge(merge(L, R), cut);
    }
    each(root, [](int val) {
        cout << char(val);
    });
    cout << '\n';
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
