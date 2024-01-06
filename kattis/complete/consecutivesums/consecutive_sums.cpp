#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;


// The code here is not very good
// The prime factors function and sieve are basically useless for the solution used
// But it solves the problem

ll sieve_size = 0;
bitset<10000010> bs;
vll p;

void sieve(ll ub) {
    sieve_size = ub + 1;
    bs.set();
    bs[0] = bs[1] = 0;

    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

vll primeFactors(ll n) {
    vll odd_pf;
    for (int i = 0; i < (int) p.size() && p[i] * p[i] <= n; i++) {
        if (n % p[i] == 0 && p[i] % 2 == 1) {
            odd_pf.push_back(p[i]);
        }
        while (n % p[i] == 0) {
            n /= p[i];
        }
    }
    if (n != 1 && n % 2 == 1) odd_pf.push_back(n);
    return odd_pf;
}

void print_no_sol() {
    cout << "IMPOSSIBLE" << endl;
}
void print_solution(ll n, ll first, ll _count) {
    if (first < 0) return print_no_sol();

    if (first == 0) {
        first = 1;
        _count--;
    }

    cout << n << " = " << first;
    for (ll i = 1; i < _count; i++) {
        cout << " + " << first + i;
    }
    cout << endl;
}

void write_to_file() {
    ofstream of("input.txt");
    int count = 1e7;
    of << count << endl;
    for (int i = 1; i <= count; i++) {
        of << i << endl;
    }
}
bool check_file() {
    ifstream ifs("output.txt");
    string line;
    while (getline(ifs, line)) {
        if (line == "IMPOSSIBLE") continue;
        istringstream iss(line);
        ll n;
        ll curr, before;
        char c;

        iss >> n >> c >> before;    // 10 = 1 + 2 + 3 + 4
        ll total = before;
        while (iss >> c >> curr) {
            total += curr;
            if (curr != before + 1) {
                cout << "Error with " << n << endl;
                return false;
            }
            before = curr;
        }
        if (total != n) {
            cout << "Error with " << n << endl;
            return false;
        }
    }
    return true;
}

ll get_sum_ap(ll a1, ll an, ll n) {
    return (a1 + an) * n / 2;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;  // [1, 2000]
    sieve(1e6);
    ll n;
    // write_to_file();
    // bool worked = check_file();
    // if (!worked) exit(0);
    while (cin >> n) { // [1, 1e9]
        if (n == 1) print_no_sol();
        else if (n % 2 == 1) {   // if odd, then only 2 numbers to get n
            print_solution(n, n/2, 2);
        }
        else {
            vll pf = primeFactors(n);
            if (pf.empty()) print_no_sol();
            else {
                // ll first_odd_pf = pf.front(); // e.g. 10 = 2 * 5; 5 -> 10 / 5 = 2, 0 1 2 3 4 (count_sides = 2)
                
                // ll middle = n / first_odd_pf;
                // ll count_sides = first_odd_pf / 2;

                // ll first = middle - count_sides;
                // print_solution(n, first, first_odd_pf);
                // cout << n << endl;
                for (ll nums = 3; true; nums++) {
                    ll sub = nums / 2 - (nums % 2 == 0 ? 1: 0);
                    ll first = n / nums - sub;
                    // cout << nums << " " << first << " " << n / nums + nums/2 << endl;
                    if (first < 0) {
                        print_no_sol();
                        break;
                    }
                    else {
                        ll sum = get_sum_ap(first, first + nums - 1, nums);
                        if (sum == n) {
                            print_solution(n, first, nums);
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// case that does not work: 38 -> will say impossible but really is 8 + 9 + 10 + 11
// 38 / 4 = 9.5
// 34 / 4 = 8.5
