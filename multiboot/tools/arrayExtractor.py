def sign(value):
    if value > 0x7FFF:
        value = -(0x10000 - value)

    return value

file = open("../mzm_us_baserom.gba", "rb")

def Func():
    inputValue = input("Address : ")
    size = int(input("Size : "))

    addr = int(inputValue, 16)

    file.seek(addr)

    result = ""

    for x in range(1, size + 1):
        # result += str(int.from_bytes(file.read(2), "little"))
        result += hex(int.from_bytes(file.read(2), "little"))

        if x % 16 == 0 and x != 0:
            result += ",\n"
        else:
            result += ", "

    print(result)
    Func()

Func()