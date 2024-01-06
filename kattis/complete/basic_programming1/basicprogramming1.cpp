#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef vector<unsigned int> vi;

int main() {
    int N, t;
    cin >> N; cin >> t;
    vi v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    ll sum = 0;
    int i = 0;
    string r;
    switch(t) {
        case 1:
            cout << 7 << endl;
            break;
        case 2:
            if (v[0] > v[1]) cout << "Bigger" << endl;
            else if (v[0] == v[1]) cout << "Equal" << endl;
            else cout << "Smaller" << endl;
            break;
        case 3:            
            sort(v.begin(), v.begin() + 3);
            cout << v[1] << endl;
            break;
        case 4:
            for (unsigned int val: v) {
                sum += val;
            }
            cout << sum << endl;
            break;
        case 5:
            for (unsigned int val: v) {
                if (val % 2 == 0) sum += val;
            }
            cout << sum << endl;
            break;
        case 6:
            for (unsigned int val: v) {
                r += ((char) (val % 26 + 'a'));
            }
            cout << r << endl;
            break;
        case 7:
            int max_count = N;
            i = 0;
            bool done = false;
            while (max_count--) {
                i = v[i];
                if (i >= N) {
                    cout << "Out" << endl;
                    done = true;
                    break;
                }
                else if (i == N - 1) {
                    cout << "Done" << endl;
                    done = true;
                    break;
                }
            }
            if (!done) cout << "Cyclic" << endl;
            break;
    }
    return 0;
}
