n = int(2e5)
q = int(2e5)
print(n, q)
value = int(1e9)
print(f"{value} " * n)
for _ in range(q - 1):
    print(f"1 1 {value}", end=" ")
print(f"2 1 {n}")
