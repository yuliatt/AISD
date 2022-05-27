file = open("input.txt", "r")
n = int(file.readline())
adj = [0] * n
for line in range(n - 1):
    r, c = [int(item) - 1 for item in file.readline().split()]
    adj[c] = r + 1
file.close()
file = open("output.txt", "w")
for i in range(n):
    file.write(str(adj[i]) + " ")
file.close()
