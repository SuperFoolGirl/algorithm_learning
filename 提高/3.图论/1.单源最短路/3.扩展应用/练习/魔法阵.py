import os
import sys
import heapq

# 请在此输入您的代码
# 本题有两个属性：路径长度、伤害量
# 分层图来了
# d[i][j]表示从起点到点i在剩余免费次数为k时受到的最小伤害


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    inf = float("inf")

    n, k, m = ri(), ri(), ri()
    h = [[] for _ in range(n)]
    dist = [[inf] * (k + 1) for _ in range(n)]

    for _ in range(m):
        u, v, w = ri(), ri(), ri()
        h[u].append((v, w))
        h[v].append((u, w))

    def dijkstra(start):
        dist[start][k] = 0
        pq = []
        heapq.heappush(pq, (dist[start][k], start, k))
        while pq:
            d, u, st = heapq.heappop(pq)
            if d > dist[u][st]:
                continue
            if u == n - 1:
                break
            for v, w in h[u]:
                # 未处于魔法状态
                if st == k:
                    # 可以不用魔法
                    if dist[v][st] > d + w:
                        dist[v][st] = d + w
                        heapq.heappush(pq, (dist[v][st], v, st))
                    # 也可以用魔法
                    if dist[v][st - 1] > d:
                        dist[v][st - 1] = d
                        heapq.heappush(pq, (dist[v][st - 1], v, st - 1))
                # 处于魔法状态，必须继续下去
                elif 0 < st < k:
                    if dist[v][st - 1] > d:
                        dist[v][st - 1] = d
                        heapq.heappush(pq, (dist[v][st - 1], v, st - 1))
                # 魔法结束，不能再用魔法了
                else:
                    if dist[v][0] > d + w:
                        dist[v][0] = d + w
                        heapq.heappush(pq, (dist[v][0], v, 0))
        res = inf
        for i in range(k + 1):
            res = min(res, dist[n - 1][i])
        return res

    print(dijkstra(0))


if __name__ == "__main__":
    solve()
