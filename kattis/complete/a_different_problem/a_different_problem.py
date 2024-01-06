import sys
inputs = sys.stdin.read().splitlines()

for case in inputs:
    numbers = case.split()
    print(abs(int(numbers[0]) - int(numbers[1])))
