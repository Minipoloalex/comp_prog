input_list = eval(input())

def stringify(lst):
    if type(lst) is not list:
        return str(lst)
    ans = "{"
    for elem in lst:
        ans += stringify(elem) + ","
    return ans + "}"

ans = stringify(input_list)
print(ans)
