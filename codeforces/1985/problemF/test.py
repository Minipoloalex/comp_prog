n = int(2e5)
with open("myin.txt", "w") as f:
    f.write("1\n")
    f.write(f"{n} {n}\n")
    f.write(f"{n} " * n + "\n")
    f.write(f"{n} " * n + "\n")
