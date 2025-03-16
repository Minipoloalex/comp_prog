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
