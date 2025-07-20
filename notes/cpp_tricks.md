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