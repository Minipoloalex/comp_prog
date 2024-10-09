t = int(1e4)
n = int(1e9)
k = int(1e9)

with open("myin.txt", "w") as f:
    f.write(f"{t}\n")
    for _ in range(t):
        f.write(f"{n} {k}\n")
