## Remove duplicates from a vector

https://cppreference.com/w/cpp/algorithm/unique.html

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

## GCD
Note that:

```
gcd(0, 0) = 0;
gcd(0, n) = n;
```

## Integers, bases and strings
### From `int` to `string`:
```cpp
int val = ...;
string s = to_string(val);  // base 10 only
```

There isn't any library function for arbitrary bases here.


### From `string` to `int`:

Basic `string` to `int`:
```cpp
int val = stoi(s);  // base 10
```

From **a string representation of any base** to `int`:
```cpp
int val = stoi(s, nullptr, base);  // e.g. base = 2
```

Specific to binary representation.
From a **binary representation string** to `int`:
```cpp
string s = "00110010";      // binary representation
int val = int(bitset<32>(s).to_ulong());   // integer
```

