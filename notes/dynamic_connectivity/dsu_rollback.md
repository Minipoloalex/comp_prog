# DSU with Rollback
Check https://usaco.guide/adv/offline-del.

**Uses**: It allows reverting operations in a LIFO (stack) way.

- Useful for Dynamic Connectivity to go through the segment tree and be able to "go back" in the tree's nodes, popping the changes made to the DSU.

## Complexity
The rollbacks don't allow path compression, so the complexity of the DSU is $\mathcal{O}(\log{N})$, since we only have union by size (or rank).

## Code
From USACO:

```cpp
class DSU {
  private:
	vector<int> p, sz;
	// stores previous unites
	vector<pair<int &, int>> history;

  public:
	DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

	int get(int x) { return x == p[x] ? x : get(p[x]); }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

        // a cool way to save (cur, prev): note the int&
        // cur is the updated version, prev is the saved ("before") version
		// save this unite operation
		history.push_back({sz[a], sz[a]});
		history.push_back({p[b], p[b]});

		p[b] = a;
		sz[a] += sz[b];
	}

	int snapshot() { return history.size(); }

	void rollback(int until) {
		while (snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};
```
