def find_key(a, n, key):
    for i in range(n):
        if a[i] == key:
            return True
    return False


file = open("input.txt", "r")
lines = file.readlines()
line = lines[0].split()
m = int(line[0])
c = int(line[1])
n = int(line[2])
lines.pop(0)

hash_table = [0] * m
for i in range(m):
    hash_table[i] = -1
for i in range(n):
    line = lines[0].strip()
    lines.pop(0)
    key = int(line)
    if not find_key(hash_table, m, key):
        k = 0
        h = ((key % m) + c * k) % m
        while hash_table[h] != -1:
            k += 1
            h = ((key % m) + c * k) % m
        hash_table[h] = key
        
file.close()

file = open("output.txt", "w")
hash = [str(i) for i in hash_table]
file.write(' '.join(hash))
file.close()
