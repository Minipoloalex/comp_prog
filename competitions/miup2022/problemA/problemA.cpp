#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;

vector<string> strs;
vi score, fol;
int64_t c, n;

vi best;    // could be integer (bitmask)
int64_t best_fol = 0, mx_score = 0;

void solve(int64_t i, int64_t curr_fol, int64_t curr_score, vi &curr) {
    if (curr_fol > c) return;   // invalid
    if (i == n) {
        if (curr.size() > best.size() || (curr.size() == best.size() && curr_score > mx_score)) {
            // no need to check the latest condition (we can just do it greedily with the order in which we recurse)
            #ifdef DEBUG
            for (int64_t v: curr) {
                cout << v << " ";
            }
            cout << endl;
            #endif

            best = curr;
            best_fol = curr_fol;
            mx_score = curr_score;
        }
        return;
    }
    curr.push_back(i);
    solve(i + 1, curr_fol + fol[i], curr_score + score[i], curr);
    curr.pop_back();
    solve(i + 1, curr_fol, curr_score, curr);
}

int main() {
    cin >> c >> n;
    strs.resize(n);
    score.resize(n);
    fol.resize(n);
    for (int64_t i = 0; i < n; i++) {
        cin >> strs[i] >> fol[i] >> score[i];
    }
    vi curr;
    solve(0, 0, 0, curr);

    cout << best.size() << " " << best_fol << " " << mx_score << '\n';
    for (int64_t i: best) {
        cout << strs[i] << '\n';
    }
    return 0;
}
