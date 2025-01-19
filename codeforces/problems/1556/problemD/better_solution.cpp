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

int sum(int a, int b) {
    int andab = ask("and", a, b);
    int orab = ask("or", a, b);
    int ans = 2 * andab + (~andab & orab);
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr;
    arr.reserve(n);
    int ab = sum(0, 1);
    int ac = sum(0, 2);
    int bc = sum(1, 2);
    int b = (ab - ac + bc) / 2;

    arr.push_back(ab - b);
    arr.push_back(b);
    arr.push_back(bc - b);

    for (int i = 3; i < n; i++) {
        arr.push_back(sum(0, i) - arr[0]);
    }
    sort(arr.begin(), arr.end());
    cout << "finish " << arr[k - 1] << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
