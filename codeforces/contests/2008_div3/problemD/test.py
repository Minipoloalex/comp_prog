n = int(2e5)

with open("myin.txt", "w") as f:
    f.write("2\n")
    f.write(str(n) + '\n')
    s = ""
    for i in range(1, n + 1):
        s += str(i) + " "
    f.write(s + '\n')
    s = ""
    for i in range(1, n + 1):
        s += "0 "
    f.write(s + '\n')

    f.write(str(n) + '\n')
    s = ""
    for i in range(1, n + 1):
        s += str(i % n + 1) + " "
    f.write(s + '\n')
    s = ""
    for i in range(1, n + 1):
        s += "0 "
    f.write(s + '\n')
