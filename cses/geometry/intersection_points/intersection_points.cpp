#include <bits/stdc++.h>
using namespace std;


// Usage:
// FenwickTree ft(n);
// 1-indexed on n:
// e.g. Sum[0:n-1] = ft.rsq(1, n);

#define LSOne(S) ((S) & -(S)) // the key operation

typedef long long ll; // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

// 1-indexed
class FenwickTree
{ // index 0 is not used
private:
    vll ft; // internal FT is an array
public:
    FenwickTree(int m) { ft.assign(m + 1, 0); } // create an empty FT

    void build(const vll &f)
    {
        int m = (int)f.size() - 1; // note f[0] is always 0
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i)
        {                                  // O(m)
            ft[i] += f[i];                 // add this value
            if (i + LSOne(i) <= m)         // i has parent
                ft[i + LSOne(i)] += ft[i]; // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); } // create FT based on f

    FenwickTree(int m, const vi &s)
    { // create FT based on s
        vll f(m + 1, 0);
        for (int i = 0; i < (int)s.size(); ++i) // do the conversion first
            ++f[s[i]];                          // in O(n)
        build(f);                               // in O(m)
    }

    ll rsq(int j)
    { // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }
};

const int MAX_VALUE = int(1e6);
const int MAX_SIZE = int(2e6) + 1;

int ft_index(int value) {
    return value + MAX_VALUE + 1;
}

void solve() {
    int n;
    cin >> n;
    vector<array<int,4>> events;
    for (int i = 0; i < n; i++) {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;    // assumption: x1 <= x2 and y1 <= y2
        if (x1 == x2) {
            // vertical line
            events.push_back({x1, 2, y1, y2});
        }
        else {
            assert(y1 == y2);   // horizontal line
            events.push_back({x1, 1, y1, -1});
            events.push_back({x2, 3, y1, -1});
        }
    }
    sort(events.begin(), events.end());
    int64_t ans = 0;
    FenwickTree ft(MAX_SIZE);
    for (auto &[x, type, y1, y2]: events) {
        if (type == 1 || type == 3) {
            int to_add = type == 1 ? 1 : -1;
            ft.update(ft_index(y1), to_add);
        }
        else if (type == 2) {
            int64_t inters = ft.rsq(ft_index(y1), ft_index(y2));
            ans += inters;
        }
    }
    cout << ans << '\n';
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
