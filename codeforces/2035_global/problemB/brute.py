res = []
for n in range(0, 2**30, 66):
    yes = True
    aux = n
    while aux and yes:
        digit = aux % 10
        aux //= 10
        if (digit != 3 and digit != 6):
            yes = False
    if yes:
        res.append(n)


for nr in res:
    print(nr)
