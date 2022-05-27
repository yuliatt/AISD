file = open("input.txt", "r")
n = int(file.readline())
adj = [0] * n
for i in range(n):
    j = 0
    for k in file.readline().split():
        if k == '1':
            adj[j] = i + 1
        j += 1
file.close()
file = open("output.txt", "w")
for i in range(n):
    file.write(str(adj[i]) + " ")
file.close()
