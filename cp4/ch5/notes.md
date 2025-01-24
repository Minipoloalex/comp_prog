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

$\log{(n)}$ blocks of 1



## Extended Euclidean Algorithm

### Modular inverse

#### Calculating combinations modulo $M$
Check https://cp-algorithms.com/combinatorics/binomial-coefficients.html#computing-binomial-coefficients-modulo-m on how to calculate combinations modulo $M$, based on factorial.
 
$$\binom n k = \frac {n!} {k!(n-k)!}$$ 
 
$$\binom n k \equiv n! \cdot (k!)^{-1} \cdot ((n-k)!)^{-1} \mod m.$$ 
```cpp
long long binomial_coefficient(int n, int k) {
    return factorial[n] * modInverse((factorial[k] * factorial[n - k]) % m, m) % m;
}
```


## GCC built-in functions
### Count number of set bits
- **Int** $$\_\_builtin\_popcount(x)$$
- **Long long** $$\_\_builtin\_popcountll(x)$$


## Sequences

### Logic behind simple sequences
Examples:
- 1, 2, 4, 7, 11, 16, 22, 29, 37, 46, 56
$$a(1) = 1$$
$$a(2) = a(1) + 1 = 2$$
$$a(3) = a(2) + 2 = 4$$
$$a(4) = a(3) + 3 = 7$$
$$...$$
$$a(n) = a(1) + (1 + 2 + 3 + ... + n - 1) = a(1) +\frac{n * (n-1)}{2}$$

## Complexity reasoning in non-classical examples:
## 
- $T(N) = T(N/2) + T(N/4) + O(1)$, from [MIUP 2022](https://dei.uc.pt/miup/wp-content/uploads/2022/10/caderno-MIUP-final-2022.pdf) problem E.

According to [Wolfram Alpha](https://www.wolframalpha.com/input?i=T%28N%29++%3D+T%28N%2F2%29+%2B+T%28N%2F4%29+%2B+1), approximately $T(N) \in \theta^{0.7n}$, whereas in [$T(N) = 3*T(N/4) + O(1)$](https://www.wolframalpha.com/input?i=T%28N%29+%3D+T%28N%2F4%29+%2B+T%28N%2F4%29+%2B+T%28N%2F4%29+%2B+1), approximately $T(N) \in \theta^{0.8n}$.

This shows why that is the case, as seen in [Wolfram Alpha](https://www.wolframalpha.com/input?i=log2%28n%29+%3C+log2%28n+%2F+2%29+%2B+log2%28n+%2F+2%29):
$$\log_2{(n)} < \log_2{\frac{n}{2}} + \log_2{\frac{n}{2}}, \forall n > 4$$
$$2 * \log_2{\frac{n}{2}} = \log_2{(\frac{n}{2})^2} = \log_2{\frac{n^2}{4}}$$

Note that the second version would lead to $TLE$ verdict, taking $30$ seconds to execute size $4e10$, while the first version only takes $0.3$ seconds.


## Built-in GCC functinos

- Built-in Function: `int __builtin_clz` (unsigned int x)
    - Returns the number of leading 0-bits in X, starting at the most significant bit position. If X is 0, the result is undefined.

- Built-in Function: `int __builtin_clzl` (unsigned long)
    - Similar to `__builtin_clz`, except the argument type is `unsigned long`.

- Built-in Function: `int __builtin_clzll` (unsigned long long)
    - Similar to `__builtin_clz`, except the argument type is `unsigned long long`.


## Greatest common divisor

### GCD calculation reasoning

Observation:
$$gcd(a, b) = gcd(a - b, b), a \ge b$$
*Proof by contradiction*:

First step:
$$d = gcd(a, b) > gcd(a - b, b)$$
$$ a = xd, b = yd, a - b = (x - y)*d$$
$$ d | (a - b), d | b \implies gcd(a - b, b) \ge d$$

Second step:

$$gcd(a, b) < gcd(a - b, b) = d$$
$$a - b = xd, b = yd, a = (a - b) + b = (x + y) * d$$
$$d | a; d | b \implies gcd(a, b) \ge d$$
Proof is complete.

```cpp
int gcd(int a, int b) {
    while (a >= b) a -= b;  // since gcd(a, b) = gcd(a - b, b)
    ...
}
```

Doing so is equivalent to doing $a \ \% \ b$.
$$gcd(a, b) = gcd(a - b, b) = gcd(a \% b, b) = gcd(b, a \% b)$$
With $b \ge a\ \%\ b$.
```cpp
// first call does not need a >= b
// from the second recursive call, a > b will always hold
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

#### Complexity reasoning
Proof that with $a \ge b$:
$$ a \ \% \ b < \frac{a}{2}$$
When calculating the GCD, this means that $a$ will be reduced at least by half, and the complexity should be $O(\log{N})$.

There are 2 cases for this proof:
1. $b > \frac{a}{2}$

$a \ge b > \frac{a}{2}$

$$a \ \%\  b = a - b < a - \frac{a}{2} = \frac{a}{2}$$
We can only take 1 $b$ from a, not any more.

2. $b \le \frac{a}{2}$
$$ a \ \% \ b \in [0, b - 1]$$
$$ a \ \% \ b < b \le \frac{a}{2}$$

Proof is complete.

Conclusions:
$$a \ \%\  b = a, a < b$$
$$a \ \%\ b < \frac{a}{2}, a \ge b$$

In each step, one of our numbers will be halved. A number $a$ can only be halved $\log{a}$ times before turning to $0$. So, the complexity of the algorithm is $O(\log{a} + \log{b})$.

Or, we can also say that the complexity is $O(\log{(min(a, b))})$. This can be important if $a$ and $b$ have different bounds. This is the case because the numbers alternate, so the first to get to $0$ will make the algorithm stop.

Even if $a, b \le 10^{18}$, we can still calculate their GCDs.
