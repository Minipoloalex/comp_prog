#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int get_int(int base, string s) {
    int integer = 0;
    for (int xi = 0; xi < (int) s.size(); xi++) {
        char c = s[xi];
        if (c >= '0' && c <= '9') {
            integer *= base;
            integer += c - '0';
        }
        else if (c >= 'a' && c <= 'z') {
            integer *= base;
            integer += c - 'a' + 10;
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string x, y, z;
        char c;
        cin >> x >> y >> c >> z;

        vector<string> res;
        vi bases;
        int lower_base = 1;
        int upper_base = 36;
        for (char xi: x) {
            if (lower_base == 1 && xi == '0') {
                lower_base = 2;
            }
            if (lower_base < 10 && xi >= '0' && xi <= '9') {
                lower_base = xi - '0' + 1;
            }
        }
        for (int base = lower_base; base <= upper_base; base++) {
            int x_int = get_int(base, x);
            int y_int = get_int(base, y);
            int z_int = get_int(base, z);
            switch (c) {
                case '+':
                    if (x_int + y_int == z_int) cout << base;
                    break;
            }
        }
    }
    return 0;
}
