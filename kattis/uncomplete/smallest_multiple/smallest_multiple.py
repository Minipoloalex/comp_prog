import sys, math

inputs = sys.stdin.read().splitlines()

for line in inputs:
    numbers = line.split()
    lcm = 1
    for number in numbers:
        lcm = math.lcm(lcm, int(number))
    print(lcm)

# RTE
