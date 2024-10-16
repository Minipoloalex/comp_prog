// https://www.hackerrank.com/challenges/one-week-preparation-kit-queue-using-two-stacks/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=preparation-kits&playlist_slugs%5B%5D=one-week-preparation-kit&playlist_slugs%5B%5D=one-week-day-five
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    int q;
    cin >> q;
    stack<int> s1, s2;
    while (q--) {
        int type;
        int x;
        cin >> type;
        switch (type) {
            case 1:
                cin >> x;
                s1.push(x);
                break;
            case 2:
                if (s2.empty()) {
                    while (!s1.empty()) {
                        int a = s1.top();
                        s1.pop();
                        s2.push(a);
                    }
                }
                if (!s2.empty()) s2.pop();
                break;
            case 3:
                if (s2.empty()) {
                    while (!s1.empty()) {
                        int a = s1.top();
                        s1.pop();
                        s2.push(a);
                    }
                }
                if (!s2.empty()) {
                    int a = s2.top();
                    cout << a << '\n';
                    // s2.pop();
                }
                break;
        }
    }
    return 0;
}
