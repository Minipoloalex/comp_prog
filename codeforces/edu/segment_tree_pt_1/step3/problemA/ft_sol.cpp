#include <bits/stdc++.h>
using namespace std;

#define LSO(n) ((n) & (-(n)))

class FenwickTree {
private:
    vector<int> ft;
    int size;
public:
    FenwickTree(int n) {
       size = n + 1;
       ft.assign(size, 0); 
    }
    void update(int i, int value) {
        for (; i < size; i += LSO(i)) ft[i] += value;
    }
    int get(int i) {
        int sum = 0;
        for (; i; i -= LSO(i)) sum += ft[i];
        return sum;
    }

    int get(int i, int j) {
        return get(j) - get(i - 1);
    }
};

int main() {
    int n;
    cin >> n;
    FenwickTree ft(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        int cnt = ft.get(ai + 1, n);
        cout << cnt << " ";
        ft.update(ai, 1);
    }
    cout << '\n';

    return 0;
}
