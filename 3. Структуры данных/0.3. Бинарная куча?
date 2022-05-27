def is_heap(line):
    if line == 0:
        return False
    else:
        for i in range(len(line)):
           if (2 * i + 1) < len(line) and \
                   int(line[i]) > int(line[2*i + 1]) or \
                   (2 * i + 2) < len(line) and \
                   int(line[i]) > int(line[2 * i + 2]):
            return False
    return True


file = open("input.txt", "r")
line = []
for i in file:
    i = i.split()
    line.append(i)
file.close()

line.remove(line[0])
line = line[0]

out = open("output.txt", "w")
out.write('Yes') if is_heap(line) is True else out.write('No')
out.close()
