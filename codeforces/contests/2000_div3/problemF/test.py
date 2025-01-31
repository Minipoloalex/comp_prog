from random import randint
n = int(1e3)
k = 100
with open("myin.txt", "w") as f:
    f.write(f"2\n")
    f.write(f"{n} {k}\n")
    for _ in range(n):
        ai = randint(1, 100)
        bi = randint(1, 100)
        f.write(f"{ai} {bi}\n")
    
    f.write(f"{n} {k}\n")
    for _ in range(n):
        ai = 1
        bi = 1
        f.write(f"{ai} {bi}\n")
