# 分层图
# dist[i][j]：使用技能j次后，从1到达点i所消耗的最短时间

import sys
import heapq


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    inf = float("inf")

    n, m, k = ri(), ri(), ri()
    h = [[] for _ in range(n + 1)]
    dist = [[inf] * (k + 1) for _ in range(n + 1)]

    def dijkstra(start):
        dist[start][0] = 0
        # 时间 点 使用技能次数
        pq = [(0, start, 0)]

        while pq:
            d, u, t = heapq.heappop(pq)
            # 不可提前退出
            if d > dist[u][t]:
                continue
            for v, w, s, e in h[u]:
                if s <= d <= e:
                    # 此时，即可以直接走，也可以用技能
                    # 但是用技能显然不会得到最优解，直接略
                    if dist[v][t] > d + w:
                        dist[v][t] = d + w
                        heapq.heappush(pq, (dist[v][t], v, t))
                elif d < s:
                    # 此时既可以选择停留，也可以直接用技能
                    # 1.停留到s
                    if dist[v][t] > s + w:
                        dist[v][t] = s + w
                        heapq.heappush(pq, (dist[v][t], v, t))
                    # 2.用技能，不能复用下面，因为不属于同一条件分支
                    if t < k:
                        if dist[v][t + 1] > d + w:
                            dist[v][t + 1] = d + w
                            heapq.heappush(pq, (dist[v][t + 1], v, t + 1))
                else:
                    # 此时只能使用技能，前提是未超过限制
                    if t < k:
                        if dist[v][t + 1] > d + w:
                            dist[v][t + 1] = d + w
                            heapq.heappush(pq, (dist[v][t + 1], v, t + 1))

    for _ in range(m):
        u, v, w, s, e = ri(), ri(), ri(), ri(), ri()
        # 处理重边和自环：重边会自然淘汰，自环需要处理一下
        if u == v:
            continue
        h[u].append((v, w, s, e))
        h[v].append((u, w, s, e))

    dijkstra(1)
    res = inf
    for i in range(k + 1):
        res = min(res, dist[n][i])
    print(res if res != inf else -1)


if __name__ == "__main__":
    solve()
