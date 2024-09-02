
n = 100
with open("myin.txt", "w") as f:
    f.write("1\n")
    f.write(f"{n}\n")
    s = ""
    for i in range(n):
        s += str(i + 1) + " "
    f.write(s + "\n")
