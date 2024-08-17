#include <bits/stdc++.h>
using namespace std;

#define LSO(n) ((n) & (-(n)))

class FenwickTree {
private:
    int size;
    vector<int> ft;
public:
    FenwickTree(int n) {
        size = n + 1;
        ft.assign(size, 0);
    }
    int get(int i) {
        int sum = 0;
        for (; i; i -= LSO(i)) sum += ft[i];
        return sum;
    }
    void update(int i, int value) {
        for (; i < size; i += LSO(i)) ft[i] += value;
    }
    int get(int i, int j) {
        return get(j) - get(i - 1);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1, -1);
    vector<int> ans(n + 1);

    int nn = n << 1;
    FenwickTree ft(nn);

    for (int i = 1; i <= nn; i++) {
        int v; cin >> v;
        if (a[v] != -1) {
            int idx = a[v];
            int res = ft.get(idx, i);
            ans[v] = res;
            ft.update(idx, 1);
        }
        else {
            a[v] = i;
        }
    }
    for (int i = 1; i < (int) ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
