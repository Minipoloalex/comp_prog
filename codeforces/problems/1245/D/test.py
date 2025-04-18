import random

n = 2000
xi_min = 1
xi_max = int(1e6)
yi_min = 1
yi_max = int(1e6)

ci_min = 1
ci_max = int(1e9)
ki_min = 1
ki_max = int(1e4)

print(n)
for _ in range(n):
    print(f"{random.randint(xi_min, xi_max)} {random.randint(yi_min, yi_max)}")

for _ in range(n):
    print(random.randint(ci_min, ci_max), end=" ")
print()

for _ in range(n):
    print(random.randint(ki_min, ki_max), end=" ")
print()
