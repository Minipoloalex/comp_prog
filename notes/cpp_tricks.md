## Remove duplicates from a vector

https://cppreference.com/w/cpp/algorithm/unique.html

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```
