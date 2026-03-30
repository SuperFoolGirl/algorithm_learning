import sys


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)

    def ri():
        return int(next(it))

    n = ri()
    m = ri()
    add = []
    query = []
    alls = []

    for _ in range(n):
        x = ri()
        c = ri()
        add.append((x, c))
        alls.appen(x)

    for _ in range(m):
        l = ri()
        r = ri()
        query.append((l, r))
        alls.append(l)
        alls.append(r)

    alls = sorted(list(set(alls)))

    sz = len(alls)
    a = [0] * (sz + 1)
    s = [0] * (sz + 1)

    def find(x):
        l = 0
        r = sz - 1
        while l < r:
            mid = (l + r) >> 1
            if alls[mid] >= x:
                r = mid
            else:
                l = mid + 1
        return l
    
    for x, c in add:
        idx = find(x)
        a[idx] += c

    for i in range(1, sz + 1):
        s[i] = s[i - 1] + a[i]

    res = []
    for l, r in query:
        l_idx = find(l)
        r_idx = find(r)
        res.append(str(s[r_idx] - s[l_idx - 1]))
    
    sys.stdout.write("\n".join(res) + "\n")


if __name__ == "__main__":
    solve()
