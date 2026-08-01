## Remove duplicates from a vector

https://cppreference.com/w/cpp/algorithm/unique.html

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

## Partial Sorting
https://en.cppreference.com/cpp/algorithm/nth_element

`nth_element` rearranges elements in `[first, last)` such that after the rearrangement the section `[first, nth]` is sorted, making the index `nth` contain the `nth`-element of the array if it was sorted.

```cpp
vector<int> d(m);

// `nth_id` must represent a valid index:
// Here:  // 0 <= nth_id <= m-1
nth_element(d.begin(), d.begin() + nth_id, d.end());

// this version can take O(NlogN)
// but if always called like this,
// then it's obviously O(N) on average as well
nth_element(d.begin(), d.begin() + nth_id, d.end(), greater());
```

## Accumulate

It uses the initial accumulator type passed, not the vector's type:
```cpp
vector<int> a(n, INT_MAX);
int64_t sm = accumulate(a.begin(), a.end(), 0);   // overflows
int64_t sm = accumulate(a.begin(), a.end(), 0LL); // does not overflow

vector<int64_t> a(n, INT_MAX);
int64_t sm = accumulate(a.begin(), a.end(), 0);   // overflows
int64_t sm = accumulate(a.begin(), a.end(), 0LL); // does not overflow
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

