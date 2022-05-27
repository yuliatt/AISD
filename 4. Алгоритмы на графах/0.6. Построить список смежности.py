file = open("input.txt", "r")
n, m = [int(i) for i in file.readline().split()]
adj = [[] * n for _ in range(n)]
for line in range(m):
    i, j = [int(item) - 1 for item in file.readline().split()]
    adj[i].append(j + 1)
    adj[j].append(i + 1)
file.close()
file = open("output.txt", "w")
for i in range(n):
    file.write(str(len(adj[i])) + " ")
    for j in adj[i]:
        file.write(str(j) + " ")
    file.write('\n')
file.close()
