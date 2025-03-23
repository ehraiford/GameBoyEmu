used = []
available = []

with open("jump_table_py_output.txt", "r") as generated:
    for line in generated.readlines():
        if '&' in line:
            line = line.split('&')[1]
            line = line.split(',')[0]
            if line not in used:
                used.append(line)

with open("Opcodes.cpp", "r") as written:
    for line in written.readlines():
        if "static" in line:
            line = line.removeprefix("static OpCode ")
            line = line.split(' ')[0]
            available.append(line)

total = 0
for func in available:
    if func not in used:
        print(func)
        total += 1

print(f"Missing: {total}")