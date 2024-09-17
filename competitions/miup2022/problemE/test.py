n = int(2e5)
m = int(2e5)

with open("myin2.txt", "w") as f:
    f.write("1\n")
    f.write(f"{n} {m}\n")
    s = ""
    for i in range(n):
        s += str(i + 1) + " "  
    f.write(s + '\n')
    f.write(s + '\n')
