## Divisibility
1. Transitivity property: $\text{If } a \equiv b \pmod{m} \text{ and } b \equiv c \pmod{m}, \text{ then } a \equiv c \pmod{m}$.

$$a \equiv b \pmod{m} \;\land\; b \equiv c \pmod{m} \;\Rightarrow\; a \equiv c \pmod{m}$$

2.  Largest multiple of $s$ that does not exceed $d$: $\lfloor \frac{d}{s}\rfloor * s$

3. A number is of the form $x^k$ iff the exponents on its prime divisors are all divisible by $k$.
For example:
$$64=2^6=(2^6)^1=(2^3)^2=(2^2)^3=(2^1)^6$$
The prime factor exponent (6) is divisible by $[1, 2, 3, 6]$, so it can be expressed as $x^k$, with $k \in [1, 2, 3, 6]$.

4. A group of numbers is congruent to the same value w.r.t. a maximum mod $m$ given by $m = \texttt{gcd}(0, \texttt{gcd}(|a1 - a2|, \texttt{gcd}(|a2 - a3|, ...)))$. Basically, $m$ is the GCD of the differences (disregarding the order, because of $(1)$).

5. The approximate number of prime numbers up to $N$ is of the complexity of $\pi(N) \approx \mathcal{O}(\frac{N}{\ln N})$.

6. The number of divisors of an integer number is of the complexity of $\mathcal{O}\sqrt{N}$. It is easy to understand because of the way divisors pair up: $(d, \frac{N}{d})$.

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

7. With any positive integer $x$, there is at least one square number in $[x,2x]$

8. Geometric progression: $a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1} = a_0 * \frac{1 - q^n}{1 - q}$.

Proof:
$$S_n = a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1}$$
$$q * S_n = (a_0 + a_0 * q + a_0 * q^2 + ... + a_0 * q^{n - 1}) * q$$
$$ S_n - q * S_n = a_0 - a_0 * q^n $$
$$ S_n * (1 - q) = a_0 * (1 - q^n) $$
$$ S_n = a_0 * \frac{1 - q^n}{1 - q} = a_0 * \frac{q^n - 1}{q - 1}, q \neq 1$$

9. The sum of divisors can be calculated using a geometric progression for each prime factor.
$$ n = p_1^{a_1} * p_2^{a_2} * ... * p_n^{a_n} $$
$$ \text{Sum of divisors} = (1 + p_1 + p_1^2 + ... + p_1^{a_1}) * (1 + p_2 + p_2^2 + ... + p_2^{a_2}) * ... * (1 + p_n + p_n^2 + ... + p_n^{a_n}) $$

Each factor can be expressed as:
$$ S_i = \frac{p_i ^ {n + 1} - 1}{p_i - 1} $$



10. The product of the divisors of a number can be expressed as:
$$ n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}$$

$$ \text{Number of divisors} = \sigma(n) = (a_1 + 1)(a_2 + 1) \cdots (a_k + 1) $$

Mathematically:
$$ \text{Product of divisors} = P(n) = n^{\sigma(n)/2}$$
For perfect square numbers: $\sigma(n)$ is odd, so for that case we should do: $$P(n) = \sqrt{n} * n^\frac{\sigma(n) - 1}{2}$$

11. As seen in 9, the number of divisors of a perfect square is odd, while the number of divisors of other numbers is even.

12. $\mathcal{O}(sieve) = \mathcal{O}(N * \log{\log{N}})$. This can be shown using the Harmonic Series of primes. $\sum_{p}^{N} \frac{1}{p} = \ln{\ln{N}} + \texttt{constant}$
