n = int(2e5)
m = int(2e5)
r = 9973
with open("myin.txt", "w") as f:
    f.write(f"{r} {n} {m}\n")
    for _ in range(n):
        f.write(f"1 0\n")
        f.write(f"0 1\n")
        f.write("\n")
    for _ in range(m):
        f.write(f"1 1")


