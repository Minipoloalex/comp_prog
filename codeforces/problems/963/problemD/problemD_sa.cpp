#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

// Suffix Array data structure, allows long strings with 350K ASCII chars = 3.5e5
// Assumes the existence of a terminal character (smaller in ascii value than all of the others)
class SuffixArray
{
private:
    vi RA; // rank array

    void countingSort(int k)
    {                                       // O(n)
        int maxi = max(300, n);             // up to 255 ASCII chars
        vi c(maxi, 0);                      // clear frequency table
        for (int i = 0; i < n; ++i)         // count the frequency
            ++c[i + k < n ? RA[i + k] : 0]; // of each integer rank
        for (int i = 0, sum = 0; i < maxi; ++i)
        {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        vi tempSA(n);
        for (int i = 0; i < n; ++i) // sort SA
            tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        swap(SA, tempSA); // update SA
    }

    void constructSA()
    { // can go up to 400K chars
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0); // the initial SA
        RA.resize(n);
        for (int i = 0; i < n; ++i)
            RA[i] = T[i]; // initial rankings
        for (int k = 1; k < n; k <<= 1)
        { // repeat log_2 n times
            // this is actually radix sort
            countingSort(k); // sort by 2nd item
            countingSort(0); // stable-sort by 1st item
            vi tempRA(n);
            int r = 0;
            tempRA[SA[0]] = r;          // re-ranking process
            for (int i = 1; i < n; ++i) // compare adj suffixes
                tempRA[SA[i]] =         // same pair => same rank r; otherwise, increase r
                    ((RA[SA[i]] == RA[SA[i - 1]]) && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r : ++r;
            swap(RA, tempRA); // update RA
            if (RA[SA[n - 1]] == n - 1)
                break; // nice optimization
        }
    }

    void computeLCP()
    {
        vi Phi(n);
        vi PLCP(n);
        PLCP.resize(n);
        Phi[SA[0]] = -1;            // default value
        for (int i = 1; i < n; ++i) // compute Phi in O(n)
            Phi[SA[i]] = SA[i - 1]; // remember prev suffix
        for (int i = 0, L = 0; i < n; ++i)
        { // compute PLCP in O(n)
            if (Phi[i] == -1)
            {
                PLCP[i] = 0;
                continue;
            } // special case
            while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
                ++L; // L incr max n times
            PLCP[i] = L;
            L = max(L - 1, 0); // L dec max n times
        }
        LCP.resize(n);
        for (int i = 0; i < n; ++i) // compute LCP in O(n)
            LCP[i] = PLCP[SA[i]];   // restore PLCP
    }

public:
    const char *T; // the input string
    // must have end special char (delimter) smaller than all of its chars
    const int n; // the length of T (including the last special char)
    vi SA;       // Suffix Array (size n, includes special char)
    vi LCP;      // LCP of adj sorted suffixes (size n, includes special char)
    // SA[0]: suffix of special (end) char
    // LCP = [N/A, 0 or N/A, ...]

    // Usage: s += '\1'; SuffixArray sa(s.c_str(), (int) s.size());
    SuffixArray(const char *initialT, const int _n) : T(initialT), n(_n)
    {
        constructSA(); // O(n log n)
        computeLCP();  // O(n)
    }

    // returns [lb, ub] of sorted suffixes indices
    // otherwise (-1, -1) if not found
    ii stringMatching(const char *P)
    {                           // in O(m log n)
        int m = (int)strlen(P); // usually, m < n
        int lo = 0, hi = n - 1; // range = [0..n-1]
        while (lo < hi)
        {                                         // find lower bound
            int mid = (lo + hi) / 2;              // this is round down
            int res = strncmp(T + SA[mid], P, m); // P in suffix SA[mid]?
            (res >= 0) ? hi = mid : lo = mid + 1; // notice the >= sign
        }
        if (strncmp(T + SA[lo], P, m) != 0)
            return {-1, -1}; // if not found
        ii ans;
        ans.first = lo;
        hi = n - 1; // range = [lo..n-1]
        while (lo < hi)
        { // now find upper bound
            int mid = (lo + hi) / 2;
            int res = strncmp(T + SA[mid], P, m);
            (res > 0) ? hi = mid : lo = mid + 1; // notice the > sign
        }
        if (strncmp(T + SA[hi], P, m) != 0)
            --hi; // special case
        ans.second = hi;
        return ans; // returns (lb, ub)
    } // where P is found
};

void solve() {
    string s;
    cin >> s;
    s += '\1';
    SuffixArray sa(s.c_str(), (int) s.size());
    int k;
    cin >> k;
    while (k--) {
        int x;
        string m;
        cin >> x >> m;
        auto [lb, ub] = sa.stringMatching(m.c_str());
        if (lb == -1 && ub == -1) {
            cout << "-1\n";
            continue;
        }
        vector<int> sfxs(ub - lb + 1);
        for (int i = 0; i < (int) sfxs.size(); i++) {
            sfxs[i] = sa.SA[lb + i];
        }
        sort(sfxs.begin(), sfxs.end());

        int ans = INT_MAX;
        int msz = int(m.size());
        int l = 0, r = x - 1;
        int n = int(sfxs.size());
        while (r < n) {
            ans = min(ans, sfxs[r] - sfxs[l] + msz);
            l++; r++;
        }
        if (ans == INT_MAX) ans = -1;
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
