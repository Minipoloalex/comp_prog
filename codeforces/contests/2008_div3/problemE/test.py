ns = [int(2e5), int(2e5 - 1)]

with open("myin.txt", "w") as f:
    f.write("2\n")
    for n in ns:
        f.write(f"{n}\n")
        f.write("a"*n + "\n")
