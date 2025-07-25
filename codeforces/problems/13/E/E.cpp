#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (auto &ai: arr) cin >> ai;
    int block_size = int(sqrt(n));

    // lst[i]: index of last node in this block (before going to next): helps in determining last
    // nxt[i]: index of next node in the blocks after
    // cnt[i]: number of moves to get to nxt[i] index
    vector<int> lst(n), nxt(n), cnt(n);
    auto pull = [&](int i) {
        int j = i + arr[i];
        if (j >= n) {
            nxt[i] = n;
            lst[i] = i;
            cnt[i] = 1;
        }
        else {
            int bi = i / block_size;
            int bj = j / block_size;
            if (bi != bj) { // bi < bj
                cnt[i] = 1;
                lst[i] = i;
                nxt[i] = j;
            }
            else {
                cnt[i] = cnt[j] + 1;
                lst[i] = lst[j];
                // careful with edge case nxt[j] = n (last is not i, possibly it's j)
                nxt[i] = nxt[j];
            }
        }
    };
    for (int i = n - 1; i >= 0; i--) {
        pull(i);
    }
    auto trav = [&](int i) {
        int total = 0, last;
        while (i < n) {
            last = lst[i];
            total += cnt[i];
            i = nxt[i];
        }
        return pair<int,int>{total, last};
    };
    while (m--) {
        int type;
        cin >> type;
        if (type == 0) {
            int a, b;
            cin >> a >> b;
            a--;
            arr[a] = b;
            int block = a / block_size;
            int base_idx = block * block_size;
            for (int i = a; i >= base_idx; i--) {
                pull(i);
            }
        }
        else {
            assert(type == 1);
            int a;
            cin >> a;
            a--;
            auto [cost, last] = trav(a);
            cout << last + 1 << " " << cost << '\n';
        }
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
