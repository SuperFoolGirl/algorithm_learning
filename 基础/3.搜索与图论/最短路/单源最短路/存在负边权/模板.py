import sys
from collections import deque


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    g = [[] for _ in range(n + 1)]
    INF = 10**9
    dist = [INF] * (n + 1)
    st = [False] * (n + 1)

    def spfa(start):
        dist[start] = 0
        queue = deque([1])
        st[start] = True

        while queue:
            u = queue.popleft()
            st[u] = False

            for v, w in g[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                if not st[v]:
                    queue.qppend(v)
                    st[v] = True

    for _ in range(m):
        u, v, w = ri(), ri(), ri()
        g[u].append((v, w))

    spfa(1)
    if dist[n] > INF // 2:
        print("impossible")
    else:
        print(dist[n])


if __name__ == "__main__":
    solve()
