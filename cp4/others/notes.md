
## XOR Hashing
Problem to serve as an example https://codeforces.com/blog/entry/134093.

Assign to each value $a_i$ in the array a random value $rnd_i$. When the same value appears again, we reuse the previously used random value for that value $a_i$. Be sure not to use the same random values by keeping, for example, an hashset of random values used.

Example code for the problem:

```cpp
void solve() {
    int n,q;
    cin >> n >> q;
    vector<unsigned long long> v(n);
    for (auto &c : v) cin >> c;
 
    random_device rd;
    mt19937_64 gen(rd());
    map<unsigned long long, unsigned long long> mapping;
    set<unsigned long long> used = {0};
 
    for (auto &c : v){
        unsigned long long random;
        if (!mapping.contains(c)){
            do{
                random = gen();
            }while (used.contains(random));
            used.insert(random);
            mapping[c] = random;
        }else{
            random = mapping[c];
        }
        c = random;
    }
 
    vector<unsigned long long> xor_pref(n+1);
 
    for (int i=0;i<n;i++) xor_pref[i+1] = xor_pref[i] ^ v[i];
    
    for (int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        cout << ((xor_pref[r]^xor_pref[l-1])?"NO\n":"YES\n");
    }
}
```

In this example, the random generator is created by doing:
```cpp
random_device rd;       // standard interface to a platform-specific non-deterministic generator random number generator
mt19937_64 gen(rd());   // Mersenne twister engine (64 bits)
```

Another way to instantiate a random function:
```cpp
auto random = mt19937_64(time(0));
```
