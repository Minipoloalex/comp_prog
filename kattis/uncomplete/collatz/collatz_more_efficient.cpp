#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> first;  // < number, steps >
int a, b;
int steps1;
int steps2;

int resA;
int resB;
int numberRes;

void collatz1(int x) {
    first.emplace(x, steps1);
    if (x == 1) return;
    
    if ((x & 1) == 0) x /= 2;
    else x = 3 * x + 1;
    
    steps1++;
    return collatz1(x);
}

void collatz2(int x) {
    auto itr = first.find(x);
    if (itr != first.end()) {
        if (a < b) {    // first is a
            resA = first[x];
            resB = steps2;
        }
        else {  // first is b
            resB = steps1;
            resA = steps2;

        }
        resA = first[x];    // the steps
        resB = steps2;
        numberRes = x;
        return;
    }
    if (x == 1) return;
    
    if ((x & 1) == 0) x /= 2;
    else x = 3 * x + 1;

    steps2++;
    return collatz2(x);
}

int main() {
    while (true) {
        scanf("%d %d", &a, &b); // [1, 1e6]
        if (a == 0 && b == 0) break;
        first.clear();
        first.reserve(293);
        steps1 = 0;
        steps2 = 0;
        
        int _first = a < b  ? a : b;
        int _second = a < b ? b : a;
        collatz1(_first);
        collatz2(_second);

        cout << a << " needs " << resA << " steps, " << b << " needs " 
        << resB << " steps, they meet at " << numberRes << endl;
    }
}
