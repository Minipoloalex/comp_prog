#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = int(3e5); // max value of prime detected
bitset<MAX_VALUE + 1> bs;       // if bs[i] = 1: i is prime
vector<int64_t> p;              // primes list

void sieve(int64_t upper) {  // can be shown complexity is O(N log(log N))
    // sieve includes [0, upper]
    int64_t sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (int64_t i = 2; i < sieve_size; i++) if (bs[i]) {
        for (int64_t j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

int get_prime_idx(int64_t prime) {
    return int(lower_bound(p.begin(), p.end(), prime) - p.begin());
};

// requires having found primes: still is O(sqrt(n) / ln(n))
vector<int> prime_factors(int64_t N) {
    vector<int> factors;
    for (int i = 0; i < (int) p.size() && (p[i] * p[i]) <= N; i++) {
        if (N % p[i] == 0) {
            while (N % p[i] == 0) {
                N /= p[i];
            }
            factors.push_back(i);
        }
    }
    if (N != 1) factors.push_back(get_prime_idx(N));
    return factors;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int s, t;
    cin >> s >> t;
    s--;t--;
    vector<vector<int>> spiders_to_primes(n);
    vector<vector<int>> primes_to_spiders(p.size());
    for (int i = 0; i < n; i++) {
        spiders_to_primes[i] = prime_factors(a[i]);
        for (int primeidx: spiders_to_primes[i]) {
            primes_to_spiders[primeidx].push_back(i);
        }
    }
    using T = int;
    queue<T> q;
    vector<int> visited(p.size());
    vector<int> dist(n, -1), par(n, -1);
    q.emplace(s);
    dist[s] = 0;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int primeidx: spiders_to_primes[u]) {
            if (!visited[primeidx]) {
                visited[primeidx] = 1;
                for (int spideridx: primes_to_spiders[primeidx]) {
                    if (dist[spideridx] == -1) {    // not visited
                        q.emplace(spideridx);
                        par[spideridx] = u;
                        dist[spideridx] = dist[u] + 1;
                    }
                }
            }
        }
    }
    if (dist[t] == -1) {
        cout << "-1\n";
    }
    else {
        vector<int> path = {t};
        int cur = t;
        while (cur != s) {
            cur = par[cur];
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        cout << path.size() << '\n';
        for (int spideridx: path) {
            cout << spideridx + 1 << " ";
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    sieve(MAX_VALUE);
    while (t--) {
        solve();
    }
    return 0;
}
