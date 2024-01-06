#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    while (cin >> a >> b >> c) {
        if (a == 0 && b == 0 && c == 0) break;
        int arr[] = {a, b, c};
        sort(arr, arr + 3);
        if (arr[0] * arr[0] + arr[1] * arr[1] == arr[2] * arr[2]) {
            cout << "right" << endl;
        }
        else cout << "wrong" << endl;
    }
    return 0;
}
