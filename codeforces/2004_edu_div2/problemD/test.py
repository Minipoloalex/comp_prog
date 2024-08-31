n = int(2e5)
q = int(2e5)

with open("myin2.txt", "w") as f:
    f.write("2\n")

    f.write(f"{n} {q}\n")
    middle = int(n / 2)
    s = ""
    for _ in range(middle):
        s += "GR "
    s += "BR GY "
    for _ in range(n - middle - 2):
        s += "GR "
    f.write(s + "\n")
    
    for _ in range(q):
        f.write(f"{middle + 1} {middle + 2}\n")
    
    f.write(f"{n} {q}\n")
    middle = int(n / 2)
    s = ""
    for i in range(middle):
        s += "GR " if i % 2 else "BY "
    s += "BR GY "
    for i in range(n - middle - 2):
        s += "GR " if i % 2 else "BY "
    f.write(s + "\n")
    
    for _ in range(q):
        f.write(f"{middle + 1} {middle + 2}\n")
