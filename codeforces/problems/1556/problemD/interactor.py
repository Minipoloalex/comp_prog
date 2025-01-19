n = 7
k = 6
arr = [1, 6, 4, 2, 3, 5, 4]
print(n, k)
while True:
    line = input()
    line = line.split()
    if line[0] == "finish":
        if int(line[1]) == arr[k - 1]:
            print("YES")
        else:
            print("NO")
        exit(0)
    a = arr[int(line[1]) - 1]
    b = arr[int(line[2]) - 1]
    if line[0] == "and":
        print(a & b)
    elif line[0] == "or":
        print(a | b)
    else:
        print("Invalid")
