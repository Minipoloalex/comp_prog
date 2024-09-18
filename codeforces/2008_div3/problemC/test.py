t = int(1e4)
with open("myin.txt", "w") as f:
    f.write(f"{t}\n")
    for _ in range(t):
        l = 1
        r = int(1e9)
        f.write(f"{l} {r}\n")
