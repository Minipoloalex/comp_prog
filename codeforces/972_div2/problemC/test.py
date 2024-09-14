n = int(1e3)
m = int(1e3)

with open("myin2.txt", "w") as f:
    f.write("1\n")
    s = "n" * m
    f.write(f"{n} {m}\n")
    for _ in range(n):
        f.write(f"{s}\n")


