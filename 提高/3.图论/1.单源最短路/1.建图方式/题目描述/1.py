import sys
from collections import deque

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    INF = 10**9
    n, m, S, T = ri(), ri(), ri(), ri()
    g = [[] for _ in range(n + 1)]
    st = [False] * (n + 1)
    dist = [INF] * (n + 1)

    def spfa():
        dist[S] = 0
        q = deque([S])
        st[S] = True

        while q:
            u = q.popleft()
            st[u] = False

            for v, w in g[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    if not st[v]:
                        q.append(v)
                        st[v] = True

    for _ in range(m):
        u, v, w = ri(), ri(), ri()
        g[u].append((v, w))
        g[v].append((u, w))

    spfa()

    sys.stdout.write(f"{dist[T]}\n")


if __name__ == "__main__":
    solve()
