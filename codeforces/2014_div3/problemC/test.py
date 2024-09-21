# n = int(2e5)
# t = 1
# with open("myin.txt", "w") as f:
#     f.write(f"1\n")
#     f.write(f"{n}\n")
#     s = ""
#     for i in range(1, n // 2 + 1):
#         s += str(1) + " "
#     print(len(range(1, n // 2 + 1)))
#     for i in range(n // 2 + 1, n + 1):
#         s += str(int(1e6)) + " "
#     print(len(range(n // 2 + 1, n + 1)))
#     f.write(s + "\n")

t = int(1e4)
n = 20
with open("myin.txt", "w") as f:
    f.write(f"{t}\n")
    for _ in range(t):
        f.write(f"{n}\n")
        s = ""
        for i in range(1, n // 2 + 1):
            s += str(1) + " "
        print(len(range(1, n // 2 + 1)))
        for i in range(n // 2 + 1, n + 1):
            s += str(int(1e6)) + " "
        print(len(range(n // 2 + 1, n + 1)))
        f.write(s + "\n")

