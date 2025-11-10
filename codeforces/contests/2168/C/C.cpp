#include <bits/stdc++.h>
using namespace std;

// there's a better solution than mine (check editorial)

bool get(int l, int r, int x) { // [l, r)
    bool par = 0;
    for (int i = l; i < r; i++) {
        par ^= bool(x & (1 << i));
    }
    return par;
}
bool get2(int start, int sz, int x) {
    bool par = 0;
    for (int i = 0; i < 3; i++) {
        par ^= get(start+i*5,start+i*5+sz,x);
    }
    return par;
}

void A() {
    int x;
    cin >> x;
    x--;
    vector<int> st;
    for (int i = 0; i < 15; i++) {
        if (x & (1 << i)) {
            st.push_back(i+1);
        }
    }
    vector<bool> cand;
    cand.push_back(get(0,10,x));
    cand.push_back(get(5,15,x));
    cand.push_back(get2(0,3,x));
    cand.push_back(get2(2,3,x));
    cand.push_back(get2(0,1,x)^get2(3,1,x));
    for (int i = 0; i < 5; i++) {
        if (cand[i]) {
            st.push_back(i+16);
        }
    }
    cout << st.size() << '\n';
    for (int val: st) {
        cout << val << " ";
    }
    cout << '\n';
}

void B() {
    bitset<20> b;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ai--;
        b.set(ai);
    }

    int x = 0;
    for (int i = 0; i < 15; i++) {
        if (b[i]) {
            x |= (1 << i);
        }
    }
    vector<bool> code;
    for (int i = 15; i < 20; i++) {
        if (b[i]) {
            code.push_back(1);
        }
        else code.push_back(0);
    }
    vector<bool> bits;
    bits.push_back(get(0,10,x));
    bits.push_back(get(5,15,x));
    bits.push_back(get2(0,3,x));
    bits.push_back(get2(2,3,x));
    bits.push_back(get2(0,1,x)^get2(3,1,x));
    auto eq = [&](int i) {
        return bits[i] == code[i];
    };
    int wrong = -1;
    if (!eq(0) && !eq(1)) {
        // incorrect in the middle
        wrong = 5;
    }
    else if (!eq(0) && eq(1)) {
        // left
        wrong = 0;
    }
    else if (eq(0) && !eq(1)) {
        // right
        wrong = 10;
    }
    if (wrong != -1) {
        if (eq(2) && eq(3)) {   // needs this check! because maybe the error code was itself wrong (the first part)
            wrong = -1;
        }
        else if (!eq(2) && eq(3)) {
            
        }
        else if (eq(2) && !eq(3)) {
            wrong += 3;
        }
        else if (!eq(2) && !eq(3)) {
            // both wrong: wrong bit is in the middle
            wrong += 2;
            goto finish;
        }
    }
    if (wrong != -1) {
        if (eq(4)) {
            wrong += 1;
        }
        else {

        }
    }

    finish:
    if (wrong != -1) {
        x ^= (1 << wrong);
    }
    cout << x+1 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string type;
    cin >> type;
    assert(type == "first" || type == "second");
    int t = 1;
    cin >> t;
    while (t--) {
        if (type == "first") {
            A();
        }
        else {
            B();
        }
    }
    return 0;
}
