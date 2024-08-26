from random import randint
n = int(1e5)
q = int(1e5)

with open("myin.txt", "w") as f:
    f.write(f"{n} {q}\n")
    s = ""
    for _ in range(n):
        s += str(randint(1, 40)) + " "
    f.write(s + '\n')
    for _ in range(q):
        xi = randint(1, n)
        yi = randint(xi, n)
        f.write(f"1 {xi} {yi}\n")
