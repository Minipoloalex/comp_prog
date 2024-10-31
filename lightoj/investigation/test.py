def sum_digits(n):
    res = 0
    while n > 0:
        res += n % 10
        n //= 10
    return res

k = 7
for i in range(153, 363):
    if i % k == 0 and sum_digits(i) % k == 0:
        print(i)

