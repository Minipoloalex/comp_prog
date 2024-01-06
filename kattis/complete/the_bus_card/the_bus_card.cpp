#include <bits/stdc++.h>
using namespace std;

int main() {
    int K;
    cin >> K;
    int count = 0;
    while (K > 0) {
        if (K >= 401) {
            K -= 500;
        }
        else if (K >= 101 && K <= 400) {
            K -= 200;
        }
        else K -= 100;
        count++;
    }
    cout << count << endl;
    return 0;
}
/*
[1, 100] - 100
[101, 200] - 200
[201, 400] - 200 and subtract
[401, 500] - 500
[501, 600] - 500 and subtract
[601, 700] - 500 and subtract
[701, 800] - 500 and subtract
*/

