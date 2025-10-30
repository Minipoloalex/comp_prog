#include <bits/stdc++.h>
using namespace std;

vector<int> qry(vector<int> &ind) {
    cout << "? " << ind.size();
    for (int i: ind) {
        cout << " " << i+1;
    }
    cout << endl;
    int c;
    cin >> c;
    vector<int> ans(c);
    for (auto &i: ans) cin >> i, i--;
    return ans;
}
void finish(vector<int> &ans) {
    cout << "!";
    for (int i: ans) cout << " " << i+1;
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    int N = n*n+1;
    vector<int> used(N,0);
    vector<int> inc(N,0), dec(N,0), parInc(N,-1), parDec(N,-1);
    vector<int> cur(N);
    iota(cur.begin(), cur.end(), 0);
    for (int i = 0; i < n; i++) {
        vector<int> resp = qry(cur);
        int curidx = 0;
        int mxdec = 0;
        int par = -1;
        for (int j = 0; j < N; j++) {
            if (used[j]) {
                if (dec[j] >= mxdec) {
                    mxdec = dec[j];
                    par = j;
                }
            }
            else {
                if (curidx < int(resp.size()) && j == resp[curidx]) {
                    dec[j] = mxdec + 1;
                    parDec[j] = par;
                    curidx++;
                }
            }
        }
        int mxinc = 0;
        par = -1;
        curidx = int(resp.size()) - 1;
        for (int j = N-1; j >= 0; j--) {
            if (used[j]) {
                if (inc[j] >= mxinc) {
                    par = j;
                    mxinc = inc[j];
                }
            }
            else {
                if (curidx >= 0 && j == resp[curidx]) {
                    parInc[j] = par;
                    inc[j] = mxinc + 1;
                    curidx--;

                    par = j;
                    mxinc = inc[j];
                }
            }
        }
        for (int ind: resp) used[ind] = 1;
        cur.clear();
        bool end = false;
        for (int j = 0; j < N; j++) {
            if (!used[j]) {
                cur.push_back(j);
            }
            if (inc[j] >= n + 1 || dec[j] >= n + 1) {
                end = true;
            }
        }
        if (end) break;
    }
    int mxdec = 0;
    int par = -1;
    for (int j = 0; j < N; j++) {
        if (used[j]) {
            if (dec[j] >= mxdec) {
                mxdec = dec[j];
                par = j;
            }
        }
        else {
            dec[j] = mxdec + 1;
            parDec[j] = par;
        }
    }
    par = -1;
    int mxinc = 0;
    for (int j = N-1; j >= 0; j--) {
        if (used[j]) {
            if (inc[j] >= mxinc) {
                mxinc = inc[j];
                par = j;
            }
        }
        else {
            inc[j] = mxinc + 1;
            parInc[j] = par;
        }
    }
    // for (int j = 0; j < N; j++) {
    //     cout << j + 1 << ": " << inc[j] << " " << dec[j] << endl;
    // }
    int idx = -1;
    for (int j = 0; j < N; j++) {
        if (inc[j] >= n + 1 || dec[j] >= n + 1) {
            idx = j;
            break;
        }
    }

    assert(idx != -1);
    vector<int> ans;
    int val = n + 1;
    bool from_dec = dec[idx] >= n + 1;
    while (int(ans.size()) < n + 1) {
        assert(idx >= 0 && idx < N);
        if ((from_dec && dec[idx] >= val) || (!from_dec && inc[idx] >= val)) {
            ans.push_back(idx);
            val--;    
        }
        if (from_dec) {
            idx = parDec[idx];
        }
        else {
            idx = parInc[idx];
        }
    }
    sort(ans.begin(), ans.end());
    finish(ans);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
