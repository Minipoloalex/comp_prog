#include <bits/stdc++.h>
using namespace std;

struct STR;

vector<STR> strings;
string s0;

enum TYPE { NONE, CUT, JOIN };
struct STR {
    TYPE type = NONE;
    int id = -1;
    uint64_t lb = 0, ub = 0;
    uint64_t szl = 0, szr = 0;
    uint64_t SZ = 0;
    uint64_t l = 0, r = 0;
    STR() {}
    STR(int _id, STR const& a, STR const& b) {
        type = JOIN;
        id = _id;
        szl = a.SZ;
        szr = b.SZ;
        SZ = szl + szr;
        l = a.id;
        r = b.id;
    }
    STR(int _id, STR const& s, uint64_t low, uint64_t up) {
        id = _id;
        type = CUT;
        lb = low;
        ub = up;
        szl = ub - lb;
        SZ = szl;
        l = s.id;
    }
    string get(uint64_t a, uint64_t b) {
        if (id == 0) {
            return s0.substr(a, b - a); // [a, b)
        }
        if (type == JOIN) {
            string fst, snd;
            if (a < szl) {
                fst = strings[l].get(a, min(szl, b));
                if (b > szl) {
                    snd = strings[r].get(0, b-szl);
                }
            }
            else {
                assert(a >= szl);
                fst = strings[r].get(a-szl, b-szl);
            }
            return fst + snd;
        }
        else {
            return strings[l].get(lb+a, lb+b);
        }
    }
};

void solve() {
    int n;
    cin >> n;
    cin >> s0;
    strings.reserve(n + 1);
    strings.emplace_back(0, STR(), 0, int(s0.size()));

    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;
        if (op == "JOIN") {
            uint64_t k, m;
            cin >> k >> m;
            strings.emplace_back(i+1, strings[k], strings[m]);
        }
        else {
            assert(op == "CUT");
            uint64_t k, l, u;
            cin >> k >> l >> u;
            strings.emplace_back(i+1, strings[k], l, u);
        }
    }
    cout << strings.back().get(0, strings.back().SZ) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
