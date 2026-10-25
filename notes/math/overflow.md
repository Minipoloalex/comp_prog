## Checking for Integer Overflow
`a * b` could cause overflow.

Check it without using 128 bits:

```cpp
if (a > MAX / b) {
    // Overflow would occur
}
a *= b;
```

>
> For positive integers:
>
>$$a \times b > MAX
>\iff
>a > \left\lfloor \frac{MAX}{b} \right\rfloor
>$$
>
>`a` is an int, so the fractional part doesn't matter (i.e, the remainer). Comparing it against `MAX / b` correctly detects whether the product would exceed `MAX`.
>
>
>>**Example:** If `MAX = 100` and `b = 3`, then `MAX / b = 33`.
>>
>>- `a = 33` → `33 × 3 = 99`
>>- `a = 34` → `34 × 3 = 102`
>
