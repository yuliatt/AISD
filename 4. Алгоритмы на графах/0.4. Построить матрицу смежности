file = open("input.txt", "r")
lines = file.read().splitlines()
file.close()

file = open("output.txt", "w")
n, m = map(int, lines[0].split())
lines.pop(0)
adj = [[0] * n for _ in range(n)]

for it in range(m):
    r, c = map(int, lines[0].split())
    adj[r - 1][c - 1] = adj[c - 1][r - 1] = 1
    lines.pop(0)

for i in range(n):
    for j in range(n):
        file.write(str(adj[i][j]) + " ")
    file.write("\n")
file.close()
