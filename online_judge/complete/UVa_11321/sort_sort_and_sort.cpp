#include <bits/stdc++.h>
using namespace std;

int arr[10000];
int N, M;

bool cmp(int a, int b) {
    bool aIsEven = a % 2 == 0;
    bool bIsEven = b % 2 == 0;

    return a % M < b % M || (a % M == b % M && 
    (
        (!aIsEven && bIsEven) || 
        (!aIsEven && !bIsEven && a > b) ||
        (aIsEven && bIsEven && a < b)
        ));
}

int main() {
    while (true) {
        memset(arr, 0, sizeof arr);
        cin >> N; cin >> M;
        if (N == 0 && M == 0) break;

        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        sort(arr, arr + N, cmp);
        cout << N << " " << M << endl;
        for (int i = 0; i < N; i++) {
            cout << arr[i] << endl;
        }
    }
    cout << "0 0" << endl;
    return 0;
}
