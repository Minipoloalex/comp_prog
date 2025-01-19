#include <bits/stdc++.h>
using namespace std;

#define BIT(i) 1 << (i)

int ask(string s, int i, int j) {
    cout << s << " " << i + 1 << " " << j + 1 << endl;
    int ans;
    cin >> ans;
    if (ans == -1) assert(0 == 1);
    return ans;
}

tuple<int,int,int> get_values(int a, int b, int c) {
    int avb = ask("or", a, b);
    int avc = ask("or", a, c);
    int bvc = ask("or", b, c);
    int anb = ask("and", a, b);
    int anc = ask("and", a, c);
    int bnc = ask("and", b, c);

    int ansa = 0, ansb = 0, ansc = 0;
    for (int i = 0; i < 32; i++) {
        int avbb = avb & BIT(i);
        int avcb = avc & BIT(i);
        int bvcb = bvc & BIT(i);
        int anbb = anb & BIT(i);
        int ancb = anc & BIT(i);
        int bncb = bnc & BIT(i);
        int aa = 0, bb = 0, cc = 0;
        // ORs
        if (avbb && avcb && !bvcb) {
            aa = BIT(i);
        }
        else if (avbb && !avcb && bvcb) {
            bb = BIT(i);
        }
        else if (!avbb && avcb && bvcb) {
            cc = BIT(i);
        }
        else if (!avbb && !avcb && !bvcb) {
            // bits are 0
        }
        // ANDs
        else if (anbb && ancb && bncb) {
            aa = BIT(i);
            bb = BIT(i);
            cc = BIT(i);
        }
        else if (anbb && !ancb && !bncb) {
            aa = BIT(i);
            bb = BIT(i);
        }
        else if (!anbb && ancb && !bncb) {
            aa = BIT(i);
            cc = BIT(i);
        }
        else if (!anbb && !ancb && bncb) {
            bb = BIT(i);
            cc = BIT(i);
        }
        else assert(0 == 1);
        ansa |= aa;
        ansb |= bb;
        ansc |= cc;
    }
    return {ansa, ansb, ansc};
}

int get_value(int i, int aidx, int a) {
    int avi = ask("or", i, aidx);
    int ani = ask("and", i, aidx);
    int ans = 0;
    for (int j = 0; j < 32; j++) {
        int avib = avi & BIT(j);
        int anib = ani & BIT(j);
        int ab = a & BIT(j);
        int ansb = 0;
        if (ab) {
            ansb = anib;
        }
        else {
            ansb = avib;
        }
        ans |= ansb;
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    auto [a, b, c] = get_values(0, 1, 2);
    arr = {a, b, c};
    arr.reserve(n);
    for (int i = 3; i < n; i++) {
        arr.push_back(get_value(i, 0, a));
    }
    sort(arr.begin(), arr.end());
    cout << "finish " << arr[k - 1] << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
