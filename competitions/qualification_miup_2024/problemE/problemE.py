# Marco VB solution
n = int(input())
s = input()

for _ in range(1000):
    s = s.replace("()", "(1)")
for _ in range(1000):
    s = s.replace(")(", ")*(", 110)
for _ in range(1000):
    s = s.replace("))", ")+1)", 110)

print(eval(s))
