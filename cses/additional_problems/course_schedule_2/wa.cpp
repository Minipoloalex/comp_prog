#include <bits/stdc++.h>
using namespace std;

/*
This solution is wrong. Here's why:
We want 1 ASAP. So, we can't just select the smallest node possible at any instant.
We need to select the nodes that can lead to 1 the fastest.
*/
typedef vector<int> vi;

vi topoSort(const vector<vi>& gr) {
	vi indeg(gr.size()), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;

    set<int> q;
    for(int i = 0; i < int(gr.size()); i++) if (indeg[i] == 0) q.insert(i);
    while (!q.empty()) {
        int i = *q.begin();
        ret.push_back(i);
        q.erase(q.begin());

        for (int x : gr[i]) {
            if (--indeg[x] == 0) q.insert(x);
        }
	}
	return ret;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vi> gr(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
    }
    vi ans = topoSort(gr);
    for (auto x: ans) {
        cout << x + 1 << " ";
    }
    cout << '\n';

    return 0;
}
