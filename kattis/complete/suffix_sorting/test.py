n = 100000
s = "a" * n
q = ""
for i in range(n):
    q += " " + str(i)

with open("myin.txt", "w") as f:
    f.write(s + '\n')
    f.write(str(n) + q)
