import sys

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n, m, k = ri(), ri(), ri()
    d = [[float("inf")] * (n + 1) for _ in range(n + 1)]

    def floyd():
        for k in range(1, n + 1):
            for i in range(1, n + 1):
                for j in range(1, n + 1):
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j])

    for i in range(1, n + 1):
        d[i][i] = 0

    for _ in range(m):
        u, v, w = ri(), ri(), ri()
        d[u][v] = min(d[u][v], w)

    floyd()
    res = []
    for _ in range(k):
        u, v = ri(), ri()
        if d[u][v] == float("inf"):
            res.append("-1")
        else:
            res.append(str(d[u][v]))
    sys.stdout.write("\n".join(res) + "\n")


if __name__ == "__main__":
    solve()
