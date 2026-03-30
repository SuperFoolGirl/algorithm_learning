import sys
from collections import deque


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    INF = 10**9
    n = ri()
    root = 0
    g = [[] for _ in range(n + 1)]
    fa = [[0] * 16 for _ in range(n + 1)]
    depth = [INF] * (n + 1)

    def bfs(root):
        depth[0], depth[root] = 0, 1
        q = deque([root])

        while q:
            u = q.popleft()
            for v in g[u]:
                if depth[v] > depth[u] + 1:
                    depth[v] = depth[u] + 1
                    q.append(v)
                    fa[v][0] = u
                    for k in range(1, 16):
                        anc = fa[v][k - 1]
                        fa[v][k] = fa[anc][k - 1]

    def lca(a, b):
        if depth[a] < depth[b]:
            a, b = b, a

        for k in range(15, -1, -1):
            if depth[fa[a][k]] >= depth[b]:
                a = fa[a][k]

        if a == b:
            return a

        for k in range(15, -1, -1):
            if fa[a][k] != fa[b][k]:
                a = fa[a][k]
                b = fa[b][k]

        return fa[a][0]

    for _ in range(n - 1):
        u, v = ri(), ri()
        if v == -1:
            root = u
        else:
            g[u].append(v)
            g[v].append(u)

    bfs(root)

    m = ri()
    while m:
        m -= 1
        a, b = ri(), ri()

        p = lca(a, b)

        if p == a:
            sys.stdout.write(f"1\n")
        elif p == b:
            sys.stdout.write(f"2\n")
        else:
            sys.stdout.write(f"0\n")


if __name__ == "__main__":
    solve()
