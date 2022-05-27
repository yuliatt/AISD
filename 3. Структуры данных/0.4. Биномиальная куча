file = open("input.txt", "r")
n = int(''.join(file.read().split()))
file.close()


file = open("output.txt", "w")
if n <= 0:
    file.write('-1\n')
else:
    heap = []
    while n > 0:
        i = 0
        while pow(2, i) <= n:
            i += 1
        heap.insert(0, i - 1)
        n -= pow(2, i - 1)
    for i in heap:
        file.write(str(i) + '\n')
file.close()
