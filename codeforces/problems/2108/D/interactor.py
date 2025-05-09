def test(n, k, c):
    print(1)
    print(n, k)
    try:
        while True:
            l = input()

            if l[0] == "?":
                x = int(l.split()[-1])
                print(c[x - 1])
            elif l[1] == "!":
                a = int(l.split()[-2])
                b = int(l.split()[-1])
                print("Answer:", a, b)
                break
            else:
                continue
    except:
        return

def myin():
    a = [0, 1, 2, 3, 4]
    b = [0, 1, 3, 4, 2]

    assert(len(a) == len(b))

    rst = [0, 1, 2, 3, 4]
    c = a + rst + b

    n = len(c)
    k = len(a)
    test(n, k, c)

def myin2():
    c = [0, 1, 3, 4, 2, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
    test(15, 5, c)

def myin3():
    c = [0, 1, 2, 0, 2, 1]
    test(6, 3, c)

def myin4():
    c = [2, 1, 0, 2, 0, 1, 2]
    test(7, 3, c)

def in1():
    c = [1, 2, 2, 1, 2]
    test(5, 2, c)

def in2():
    c = [2,4,3,1,2,4,3,1,2,1,3,2,4,1,3,2,4,1]
    test(len(c), 4, c)

def in3():
    c = [1, 1, 1]
    test(3, 1, c)

def in4():
    c = [1, 2, 3, 4, 5] * 2
    test(10, 5, c)

def in5():
    c = [1,2,3,1,2,3,1,3,2]
    test(len(c),3,c)

def in6():
    c = [1,3,2,4,1,3,4,2,1,3,4,2]
    test(12, 4, c)

# myin()
# myin2()
# myin3()
myin4()
# in1()
# in2()
# in3()
# in4()
# in5()
# in6()
