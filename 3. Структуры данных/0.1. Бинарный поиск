n = int(input())
a = input().split()
for i in range(n):
    a[i] = int(a[i])

k = int(input())
v = input().split()
for i in range(k):
    v[i] = int(v[i])


def binary_search(a, v):
    l = 0
    r = len(a)
    while l < r:
        mid = (l + r) // 2
        if v == a[mid]:
            return 1
        if v < a[mid]:
            r = mid
        else:
            l = mid + 1
    return 0


def binary_search_lb(a, v):
    l = 0
    r = len(a)
    while l < r:
        mid = (l + r) // 2
        if v > a[mid]:
            l = mid + 1
        else:
            r = mid
    return l


def binary_search_ub(a, v):
    l = 0
    r = len(a)
    while l < r:
        mid = (l + r) // 2
        if v < a[mid]:
            r = mid
        else:
            l = mid + 1
    return r

for i in range(k):
    print(binary_search(a, v[i]), binary_search_lb(a, v[i]), binary_search_ub(a, v[i]))
