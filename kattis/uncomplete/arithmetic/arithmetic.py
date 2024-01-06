integer = int(input(), 8)

hex_string = hex(integer).removeprefix("0x").upper()

print(hex_string)
