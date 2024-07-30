### Geometric series:
```
a,  a * r,  a * r^2,  ...
```

- Sum of infinite geometric series: $\frac{a}{1 - r}$
- Sum of finite geometric series (n terms): $\frac{a}{1 - r} * (1 - r^{n})$


### Harmonic series

$ H(n) = 1 + \frac{1}{2} + \frac{1}{3} + \frac{1}{4} + \frac{1}{5} + \frac{1}{6} + ... = ln(n) $

$n + \frac{n}{2} + \frac{n}{3} + \frac{n}{4} + \frac{n}{5} + \frac{n}{6} + ... = n (1 + \frac{1}{2} + \frac{1}{3} + \frac{1}{4} + \frac{1}{5} + \frac{1}{6} + ...) = n * ln(n)$


Harmonic series usage example (https://codeforces.com/contest/1996/problem/D) to achieve $O(N logN)$ (jiangly): 

```cpp
int n, x;
std::cin >> n >> x;

i64 ans = 0;
for (int a = 1; a <= n; a++) {
    for (int b = 1; a * b <= n && a + b <= x; b++) {
        ans += std::min((n - a * b) / (a + b), x - a - b);
    }
}
std::cout << ans << "\n";
```

#### Explanation

$1 + (\frac{1}{2} + \frac{1}{3}) + (\frac{1}{4} + \frac{1}{5} + \frac{1}{6} + \frac{1}{7}) + (\frac{1}{8} + \frac{1}{9} + \frac{1}{10} + \frac{1}{11} + \frac{1}{12} + \frac{1}{13}+ \frac{1}{14} + \frac{1}{15}) + ...$

E.g. $\frac{1}{2} + \frac{1}{3} \leq 2 * \frac{1}{2} = 1$

Log(n) blocks of 1