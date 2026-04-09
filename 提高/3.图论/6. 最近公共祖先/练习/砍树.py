import os
import sys
from collections import deque

# 暗之连锁
# 每加入一条非树边，都会形成一个环
# 此时，从非树边的端点xy出发找lca，就能确定这个环
# 状态数组c统计树边信息：对于每条树边，需要砍断多少非树边才能实现不连通
# 其中，维护c的差分数组d来提高效率
# 根据上述信息，从xy到lca，每条树边都应+1
# 对于差分数组来说，只需要d[x]+=1,d[y]+=1,d[lca]-=2
# 对以u为根的所有结点d求和，可得到u到其父亲的边权


# 这个题更加简化，没有非树边这个概念
# 枚举询问数对，找其lca，其路径上每条边的边权+1
# 最终，我们要砍掉一条边权为m的编号最大的边
# 边权为m说明，如果砍断这条边，那m个数对都将满足不连通
def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    inf = float("inf")

    n, m = ri(), ri()
    h = [[] for _ in range(n + 1)]
    fa = [[0] * 18 for _ in range(n + 1)]
    depth = [inf] * (n + 1)
    d = [0] * (n + 1)
    res = -1
    rank = {}

    def bfs(root):
        q = deque([root])
        depth[0], depth[root] = 0, 1
        while q:
            u = q.popleft()
            for v in h[u]:
                if depth[v] > depth[u] + 1:
                    depth[v] = depth[u] + 1
                    q.append(v)
                    fa[v][0] = u
                    for k in range(1, 18):
                        anc = fa[v][k - 1]
                        fa[v][k] = fa[anc][k - 1]

    def lca(a, b):
        if depth[a] < depth[b]:
            a, b = b, a
        for k in range(17, -1, -1):
            if depth[fa[a][k]] >= depth[b]:
                a = fa[a][k]
        if a == b:
            return a
        for k in range(17, -1, -1):
            if fa[a][k] != fa[b][k]:
                a = fa[a][k]
                b = fa[b][k]
        return fa[a][0]

    # 存在树边u->v使得sum(v)=m即为答案
    def dfs(u, pa):
        nonlocal res
        sum = d[u]  # 记录每个点的差分和
        for v in h[u]:
            if v == pa:
                continue
            s = dfs(v, u)  # 记录每个儿子的差分和，试图找u->v边权为m
            if s == m:
                res = max(res, rank[(u, v)])
            sum += s
        return sum

    # 建树并存储编号排名
    for i in range(1, n):
        u, v = ri(), ri()
        h[u].append(v)
        h[v].append(u)
        rank[(u, v)] = rank[(v, u)] = i

    # lca预处理
    bfs(1)

    for _ in range(m):
        a, b = ri(), ri()
        p = lca(a, b)
        d[a] += 1
        d[b] += 1
        d[p] -= 2

    # 差分数组求和
    dfs(1, -1)

    print(res)


if __name__ == "__main__":
    solve()
