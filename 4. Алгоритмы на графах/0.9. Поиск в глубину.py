def dfs(node):
    global index
    is_passed[node] = True
    mark[node] = index
    index += 1
    for v in range(n):
        if adj[node][v] == 1 and not is_passed[v]:
            dfs(v)


file = open("input.txt", "r")
n = int(file.readline())
index = 1
is_passed = [False] * n
mark = [0] * n
adj = [[0] * n for _ in range(n)]
for j in range(n):
    adj[j] = [int(item) for item in file.readline().split()]
for j in range(n):
    if not is_passed[j]:
        dfs(j)
file.close()

file = open("output.txt", "w")
for j in range(n):
    file.write(str(mark[j]) + " ")
file.close()
