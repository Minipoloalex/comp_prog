from random import randint
c = int(2**31)
n = 20
length = 10
fol = int(2**20)

with open("myin.txt", "w") as f:
    f.write(f"{c} {n}\n")
    for _ in range(n):
        s = ""
        for _ in range(length):
            s+= chr(ord('a') + randint(0, 25))
        # score = randint(1, 1000)
        # follow = randint(1, fol)
        score = 1000
        follow = fol
        f.write(f"{s} {follow} {score}\n")
