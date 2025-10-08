#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, INT_MAX);

struct Tag {
    bool rev = false;
    void apply(Tag upd) {
        rev ^= upd.rev;
    }
};

struct Node {
    Node *l = 0, *r = 0;
    int val, prio, c;

    int64_t sm; // additional info
    Tag lazy; // Update already done to the node (should push to children)
    Node(int v): val(v), prio(gen(rng)), c(1), sm(val) {}
    void apply(Tag upd) {
        if (upd.rev) { swap(l, r); }
    }
};
void apply(Node *t, Tag upd) {
    if (!t) return;
    t->apply(upd);      // update current node
    t->lazy.apply(upd); // compose lazy updates
}
void push(Node *t) {
    if (!t) return;
    apply(t->l, t->lazy);
    apply(t->r, t->lazy);
    t->lazy = Tag();
}
int getsz(Node *t) {
    return t ? t->c : 0;
}
int64_t getsum(Node *t) {
    return t ? t->sm : 0;
}
void recalc(Node *t) {
    if (t) {
        t->c = 1 + getsz(t->l) + getsz(t->r);
        t->sm = t->val + getsum(t->l) + getsum(t->r);
    }
}

// All nodes in L come before all nodes in R (by position)
Node* merge(Node *L, Node *R) {
    if (!L) return R;
    if (!R) return L;
    if (L->prio > R->prio) {    // L is the main root
        push(L);
        L->r = merge(L->r, R);
        recalc(L);
        return L;
    }
    else {  // R is the main root
        push(R);
        R->l = merge(L, R->l);
        recalc(R);
        return R;
    }
}

// Split by position: first k elements go to L, rest to R
pair<Node*, Node*> split(Node *t, int k) {
    if (!t) return {nullptr, nullptr};
    push(t);
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
    if (t) { push(t); each(t->l, f); f(t->val); each(t->r, f); }
}

void solve() {
    int n, m;
    cin >> n >> m;
    Node *treap = nullptr;
    for (int i = 0; i < n; i++) {
        int xi;
        cin >> xi;
        treap = merge(treap, new Node(xi));
    }
    while (m--) {
        int t, a, b;
        cin >> t >> a >> b;
        a--;b--;
        auto [L, rst] = split(treap, a); // L: [0, a), rst: [a, n)
        auto [mid, R] = split(rst, b-a+1); // mid: [a, b+1)
        if (t == 1) {
            apply(mid, Tag{true});
        }
        else {
            assert(t == 2);
            cout << getsum(mid) << '\n';
        }
        treap = merge(merge(L, mid), R);
    }
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
