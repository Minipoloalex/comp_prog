n = int(2e5)
k = n // 2

with open("myin.txt", "w") as f:
    f.write("1\n")
    f.write(f"{n} {k}\n")
    f.write("1 " * n + "\n")
