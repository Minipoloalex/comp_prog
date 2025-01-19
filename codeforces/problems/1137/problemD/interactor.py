t = 2
c = 2

players = [i for i in range(10)]
players_pos = [0 for _ in range(10)]

suc = [i + 1 for i in range(t)] + [(i + t + 1) for i in range(c)]
suc[-1] = t

def move(pl):
    players_pos[pl] = suc[players_pos[pl]]
def players_str(pls):
    s = ""
    for pl in pls:
        s += str(pl)
    return s

done = False
while not done:
    line = input()
    l = line.split()
    if l[0] == "done":
        done = True
    elif l[0] == "next":
        for pl in l[1:]:
            move(int(pl))
        pos = {}
        for pl, plpos in enumerate(players_pos):
            pos[plpos] = pos.get(plpos, [])
            pos[plpos].append(pl)
        s = str(len(pos))
        for pls in pos.values():
            s += " " + players_str(pls)
        print(s)
