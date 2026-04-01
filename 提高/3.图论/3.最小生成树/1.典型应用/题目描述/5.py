import sys


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    p = list(range(n * m + 1))
    ids = [[0] * (m + 1) for _ in range(n + 1)]
    e = []

    def find(x):
        if p[x] != x:
            p[x] = find(p[x])
        return p[x]

    def get_edges():
        dx = [-1, 0, 1, 0]
        dy = [0, 1, 0, -1]
        dw = [1, 2, 1, 2]

        for z in range(0, 2):
            for i in range(1, n + 1):
                for j in range(1, m + 1):
                    for u in range(0, 4):
                        if u % 2 == z:
                            x, y = i + dx[u], j + dy[u]
                            if x < 1 or x > n or y < 1 or y > m:
                                continue
                            a, b, w = ids[i][j], ids[x][y], dw[u]
                            if a < b:
                                e.append((a, b, w))

    def kruskal():
        res = 0
        for a, b, w in e:
            pa, pb = find(a), find(b)
            if pa != pb:
                p[pa] = pb
                res += w
        return res

    t = 1
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            ids[i][j] = t
            t += 1

    try:
        while True:
            x1, y1, x2, y2 = ri(), ri(), ri(), ri()
            a, b = ids[x1][y1], ids[x2][y2]
            p[find(a)] = find(b)
    except StopIteration:
        pass

    get_edges()

    sys.stdout.write(f"{kruskal()}\n")


if __name__ == "__main__":
    solve()
