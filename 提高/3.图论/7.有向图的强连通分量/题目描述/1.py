import sys

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))
    rs = lambda: next(it)

    INF = 10 ** 9
    n, m = ri(), ri()
    g = [[] for _ in range(n + 1)]
    dfn, low, timestamp = [0] * (n + 1), [0] * (n + 1), 0
    stk = []
    id, scc_cnt, sz = [0] * (n + 1), 0, [0] * (n + 1)
    dout = [0] * (n + 1)

    def tarjan(u):
        nonlocal timestamp, scc_cnt
        timestamp += 1
        dfn[u] = low[u] = timestamp
        stk.append(u)

        for v in g[u]:
            if not dfn[v]:
                tarjan(v)
                low[u] = min(low[u], low[v])
            # v in stk效率为O(n)，这里可以考虑加in_stk数组优化
            elif v in stk:
                low[u] = min(low[u], dfn[v])

        if low[u] == dfn[u]:
            scc_cnt += 1
            while True:
                y = stk.pop()
                id[y] = scc_cnt
                sz[scc_cnt] += 1
                if y == u:
                    break


    for _ in range(m):
        u, v = ri(), ri()
        g[u].append(v)

    for i in range(1, n + 1):
        if not dfn[i]:
            tarjan(i)

    for u in range(1, n + 1):
        for v in g[u]:
            if id[u] != id[v]:
                dout[id[u]] += 1
    
    zeros, sum = 0, 0
    for i in range(1, scc_cnt + 1):
        if not dout[i]:
            zeros += 1
            sum += sz[i]
        if zeros > 1:
            sum = 0
            break

    sys.stdout.write(f"{sum}\n")


if __name__ == "__main__":
    solve()
