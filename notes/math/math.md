## Divisibility
1. Transitivity property: $\text{If } a \equiv b \pmod{m} \text{ and } b \equiv c \pmod{m}, \text{ then } a \equiv c \pmod{m}$.

$$a \equiv b \pmod{m} \;\land\; b \equiv c \pmod{m} \;\Rightarrow\; a \equiv c \pmod{m}$$

2.  Largest multiple of $s$ that does not exceed $d$: $\lfloor \frac{d}{s}\rfloor * s$

3. A number is of the form $x^k$ iff the exponents on its prime divisors are all divisible by $k$.
For example:
$$64=2^6=(2^6)^1=(2^3)^2=(2^2)^3=(2^1)^6$$
The exponent $6$ from the prime factor $2$ is divisible by $[1, 2, 3, 6]$, so it can be expressed as $x^k$, with $k \in [1, 2, 3, 6]$.

4. A group of numbers is congruent to the same value w.r.t. a maximum mod $m$ given by $m = \texttt{gcd}(0, \texttt{gcd}(|a1 - a2|, \texttt{gcd}(|a2 - a3|, ...)))$. Basically, $m$ is the GCD of the differences (disregarding the order, because of $(1)$).

5. The **approximate number of prime numbers up to $N$** is of the complexity of $\pi(N) \approx \mathcal{O}(\frac{N}{\ln N})$.

    5.1 **Prime gaps**: The average gap between two primes is about $\ln{A}$, but there can be pretty big gaps, more than 1000. Check https://en.wikipedia.org/w/index.php?title=Prime_gap&oldid=1295208192 (second table).

6. The number of divisors $d(n)$ of an integer number is of the complexity of $\mathcal{O}\sqrt{N}$. It is easy to understand because of the way divisors pair up: $(d, \frac{N}{d})$.

```cpp
// Count divisors of a number
const int up = (int)sqrt(a);
for (int div = 1; div <= up; div++) {
    if (a % div == 0) {
        // the divisor and quotient are both divisors of a
        divisors[div]++;
        // make sure not to double count
        if (div != a / div) { divisors[a / div]++; }
    }
}
```

Actually, $d(n) = \mathcal{O}(n^\epsilon)$, with any $\epsilon > 0$ and $n$ tending to $\infty$. More precisely, it is:
$$ d(n) \le 2 ^ {\frac{\ln n}{\ln \ln n} (1 + o(1))} $$

Here, o(1) means a term that approaches 0 as n approaches $\infty$.

It can be simplified to:
$$ d(n) = \mathcal{O}(n ^ {\frac{\ln 2}{\ln \ln n}}) $$

Since $\ln \ln n \to \infty$ as $n \to \infty$, the exponent $\frac{\ln 2}{\ln \ln n}$ goes to $0$, reinforcing that $d(n)$ grows slower than $n^\epsilon$ for any fixed $\epsilon > 0$.

For a value of $10^6$, the exponent is approximately $0.26$.


7. With any positive integer $x$, there is at least one square number in $[x,2x]$

8. Geometric progression: $a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1} = a_0 * \frac{1 - q^n}{1 - q}$.

Proof:
$$S_n = a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1}$$
$$q * S_n = (a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1}) * q$$
$$ S_n - q * S_n = a_0 - a_0 * q^n $$
$$ S_n * (1 - q) = a_0 * (1 - q^n) $$
$$ S_n = a_0 * \frac{1 - q^n}{1 - q} = a_0 * \frac{q^n - 1}{q - 1}, q \neq 1$$

9. The sum of divisors can be calculated using a geometric progression for each prime factor.
$$ n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k} $$
$$ \text{Sum of divisors} = \sigma{(n)}$$
$$ \sigma{(n)}=  (1 + p_1 + p_1^2 + ... + p_1^{a_1}) * (1 + p_2 + p_2^2 + ... + p_2^{a_2}) * ... * (1 + p_k + p_k^2 + ... + p_k^{a_k}) $$

Each factor can be expressed as:
$$ S_i = \frac{p_i ^ {a_i + 1} - 1}{p_i - 1} $$


10. The product of the divisors of a number can be expressed as a simple formula (see $\text{Product of divisors} = \dots$ ):
$$ n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}$$

$$ \text{Number of divisors} = d(n) = \tau(n) = (a_1 + 1)(a_2 + 1) \cdots (a_k + 1) $$

Mathematically:
$$ \text{Product of divisors} = P(n) = n^{d(n)/2}$$
For perfect square numbers: $d(n)$ is odd, so for that case we should do: $$P(n) = \sqrt{n} * n^\frac{d(n) - 1}{2}$$
Or instead just use: $$P(n) = (\sqrt{n})^{d(n)}$$

Note that $\sqrt{n} \mod M \neq \sqrt{n \mod M} \mod M$. If we want the product of divisors $P(n) \mod M$ and $n$ doesn't fit in 64 bits, we should divide each of the prime exponents by 2 (https://cses.fi/problemset/task/1082). Obviously they can be divided, because we're handling the **perfect square** case.

$$\sqrt{n} = \sqrt{p_1^{a_1}} \cdot \sqrt{p_2^{a_2}} \cdot \dots \cdot \sqrt{p_k^{a_k}} $$

11. As seen in 9, the **number of divisors of a perfect square is odd**, while the **number of divisors of other numbers is even**.

12. $\mathcal{O}(sieve) = \mathcal{O}(N * \log{\log{N}})$. This can be shown using the Harmonic Series of primes. $\sum_{p}^{N} \frac{1}{p} = \ln{\ln{N}} + \texttt{constant}$


13. The sum of the first $x$ odd numbers is a perfect square. $ 1 + 3 + \dots + 2n - 1 = n * \frac{(1 + 2n - 1)}{2} = \frac{n * 2n}{2} = n^2$, a perfect square.
On the other hand, the sum of the first $x$ even numbers ($x > 1$) is never a perfect square: $ 2 + 4 + \dots + 2n = n*(n + 1) $. $n^2$ is a perfect square and the next perfect square is $(n + 1)^2$, which is obviously not the sum of the first $x > 1$ even numbers.

14. **The digit sum (in base 10) preserves the remainder modulo 9**. This is easy to prove: all powers of 10 give the remainder 1 when divided by 9, therefore $\sum a_i * 10^i$, the value of the number, gives the same remained as $\sum a_i$, the digit sum of the number. Basically, this means that if we add 9 to a number $n$, its digit sum modulo 9 will remain unchanged.

    14.1. If 2 numbers have the same digit sum, that implies that they are $9k$ apart, but not the other way around. E.g. $91$ and $100$.

15. From **Fermat's Little Theorem**:

If $p$ is a prime number, then for any integer $a$ not divisible by $p$, the congruence relation below holds.

$$a^{p-1} \equiv 1 \pmod{p}$$

**Conditions:**
- $p$ is a prime
- $gcd(a, p) = 1$

16. The number of distinct $GCD$'s of a number $M$ to other numbers (can be lots of other numbers) is obviously limited by the number of divisors of $M$.

17. Doing "$(a_i + k)\mod{m}$" keeps "$a_i \mod{gcd(k, m)}$" invariant.

$$(a_i + k) \mod{gcd(k, m)} = a_i \mod{gcd(k, m)}$$


This is simple to prove:
- Given $g = gcd(k, m)$, we have $g \mid k$ and $g \mid m$.
- This means that $k \mod g = 0$, so adding $k$ has no effect modulo $g$.

Simple problem example for this: https://codeforces.com/problemset/problem/2050/F. Doing the GCD of the 
differences gives the largest MOD that makes numbers equal (see editorial).

18. If we apply matrix $R$ after matrix $L$, then the product is: $R * L$.

19. We can modulo matrix elements to do the product of matrices (since matrix multiplication is just repeated additions and multiplications).
$$
    (R L)_{ij}
    \;=\;\sum_{k} R_{ik}\,L_{kj}.
$$
So:
$$
    (A \bmod M)\,(B \bmod M)\;\bmod M
    \;=\;(A\,B)\bmod M.
$$

20. $gcd(a, b) = c \implies gcd(\frac{a}{c}, \frac{b}{c}) = 1$

21. Given a list of integer numbers $a_1,a_2,\dots,a_n$, we can tell if a linear combination of them (with negative and/or positive coefficients) can form a (large) number $K$ by, given $g = gcd(a_1,a_2,\dots,a_n)$:

$$ c_1 a_1 + c_2 a_2 + \cdots + c_n a_n = K \texttt{, integer coefficients }c_i\in [-\infty, \infty], \texttt{ iff}$$
$$g \mid K \quad\Longleftrightarrow\quad K \bmod g = 0$$

22. An interesting fact is that the prefix sum of the differences between consecutive perfect squares is almost a perfect square itself. In fact, $S + 1$ is a perfect square. E.g. in the sequence of perfect squares: $1, 4, 9, 16, 25$, we have the difference: $3 + 5 + 7 + 9 = 8 + 7 + 9 = 15 + 9 = 24$.

23. **Euclidean Algorithm**

The base for the algorithm is: $gcd(a, b) = gcd(b, a - b)$. Or more general:
$$gcd(a, b) = gcd(b, a + k \cdot b)$$

```cpp
int gcd(int a, int b) { // inefficient (just the idea)
    while (a >= b) a -= b;  // since gcd(a, b) = gcd(a - b, b)
    ...
}
```
```cpp
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```
```cpp
int64_t euclid(int64_t a, int64_t b) {
	while (b > 0) { // iterative, euclid-like implementation
        // a = k * b + r
        // r = a % b
		int64_t k = a / b;
		a -= k * b;
		swap(a, b);
	}
	return a;
}
```

## Factorials and Combinations
1. Inverse modulo property
$$(a*x) \mod P \equiv 1$$
$$((a \mod{P})*x \mod{P}) \equiv 1$$
This means that: $\texttt{modinv}(A, P) = \texttt{modinv}(A \mod{P}, P)$

2. Inverse modulo of factorials

$$\texttt{fact}[i] = \texttt{fact}[i - 1] * i$$

For calculating modular inverse (and by precomputing), we can get the value for the last factorial we may need, then propagate it backwards. This prevents us from having to run inverse modulo for every factorial value, which would be $\mathcal{O}(N \log N)$, instead of $O(N)$.

$$\frac{1}{i!} * i = \frac{i}{i!} = \frac{1}{(i-1)!}$$
$$\texttt{invfact}[i] = \texttt{invfact}[i + 1] * (i+1)$$

3. If we know $\binom nk$ does not overflow, we can simplify the factorials (simplify the fraction):
```cpp
if (n - k < k) k = n - k;
int64_t ans = 1;
for (int i = 0; i < k; i++) {
    ans = ans * (n - i) / (i + 1);
}
```
It's ensured that $i + 1$ will divide $ans$, because $ans$ has "seen" $i + 1$ numbers up until the moment (which means it has seen a multiple of $i + 1$).

4. More details about Binomial coefficients

Sum of binomial coefficients (sum of a row in Pascal's Triangle):
$$
\binom{n}{0} + \binom{n}{1} + \binom{n}{2} + \cdots + \binom{n}{n} = 2^n
$$

Binomial expansion of $(a+b)^n$:
$$
(a + b)^n = \binom{n}{0} a^n b^0 + \binom{n}{1} a^{n-1} b^1 + \cdots + \binom{n}{n-1} a^1 b^{n-1} + \binom{n}{n} a^0 b^n
$$

5. Placing $X$ items in $N$ boxes (different scenarios): https://usaco.guide/CPH.pdf#page=219.

- For scenario 2, can think of it in a $\textit{DP }$ way. For this scenario, we can also think of separating the balls with $n$ bars: "|", and choosing the positions of these bars.
- Scenario 3 simplifies to scenario 2 if we think of placing the "basic setup" first.

6. **Derangements**: The number of derangements of $n$ numbers, expressed as $!n$, is the number of permutations such that no element appears in its original position. Informally, it is the number of ways $n$ hats can be returned to $n$ people such that no person receives their own hat. Check https://usaco.guide/gold/combo#derangements for proofs:

By the Principle of Inclusion-Exclusion, we can show that:
$$!n = n! \sum_{k=0}^{n} \frac{(-1)^k}{k!}$$

This leads to the following recursive definition:
$$ !(n + 1) =\ !n \cdot (n + 1) + (n+1)! \cdot \frac{(-1)^{n+1}}{(n+1)!} =\ !n \cdot (n+1) + (-1)^{n+1}$$

Where $!0 = 1$, since there is one way to organize a 0-sized permutations (that respects any conditions).

There is also a proof using $DP$ and the results are:
$$!n = (n - 1) \cdot (\ !(n - 2)\ +\ !(n - 1)\ ), with \ !0 = 1, \ !1 = 0$$


## Expected Values

1. Basic definition (Expected value of a discrete random variable)
$$\mathbb{E}[X] = \sum_x x \cdot P(X = x)$$

2. Linearity of expectation (holds even if $X$ and $Y$ are not independent):  
$$\mathbb{E}[X + Y] = \mathbb{E}[X] + \mathbb{E}[Y]$$

Example use: https://atcoder.jp/contests/agc049/tasks/agc049_a

3. Product of expectations (only if $X$ and $Y$ are independent):  
$$\mathbb{E}[X \cdot Y] = \mathbb{E}[X] \cdot \mathbb{E}[Y] \quad \text{if } X \perp Y$$

For example:
$$\mathbb{E}[X^2] \ne (\mathbb{E}[X])^2$$


## Simple formulas
1. **Change logarithm base**
$$ \log_b(X) = \frac{\log(X)}{\log(b)}$$

2. **Max** and **Min**:
$$\max(a,b)=\frac{a+b+\lvert a-b\rvert}{2}$$
$$\min(a,b)=\frac{a+b-\lvert a-b\rvert}{2}$$
