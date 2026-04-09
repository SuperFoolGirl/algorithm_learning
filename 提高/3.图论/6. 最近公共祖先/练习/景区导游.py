import os
import sys
from collections import deque

# 请在此输入您的代码
# 树上最短路问题还是lca
# 但本题是有权图，不能直接用depth统计路径长度了，需要倍增处理边权
# 但depth依然需要，lca中依赖depth来判断层间关系
# depth和d数组都是基于前缀和思想的


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    inf = float("inf")

    n, K = ri(), ri()
    fa = [[0] * 18 for _ in range(n + 1)]
    depth = [inf] * (n + 1)
    h = [[] for _ in range(n + 1)]
    dist = [inf] * (n + 1)  # 统计每个点到根结点的距离
    adj_dist = [0] * (K - 1)  # 统计path上相邻点的距离

    def bfs(root):
        q = deque([root])
        # depth[0]需要初始化，lca逻辑依赖这个边界
        # dist是我们额外的信息维护，与lca算法正确性无关，不需要管非法点0
        depth[0], depth[root] = 0, 1
        dist[root] = 0
        while q:
            u = q.popleft()
            for v, w in h[u]:
                # 无向树，为了防止走回父亲，加深度判断
                # 树间路径唯一，不重复走边时没有“最短路”可言，直接无脑按拓扑序更新
                if depth[v] > depth[u] + 1:
                    depth[v] = depth[u] + 1
                    dist[v] = dist[u] + w
                    q.append(v)
                    fa[v][0] = u
                    for k in range(1, 18):
                        anc = fa[v][k - 1]
                        fa[v][k] = fa[anc][k - 1]

    # 明确一下，自底向上走，路径是唯一的，不存在分支
    def lca(a, b):
        if depth[a] < depth[b]:
            a, b = b, a
        # 二进制拼凑
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

    def distance(a, b):
        return dist[a] + dist[b] - 2 * dist[lca(a, b)]

    for _ in range(n - 1):
        u, v, w = ri(), ri(), ri()
        h[u].append((v, w))
        h[v].append((u, w))

    path = [ri() for _ in range(K)]

    # 预处理
    bfs(1)

    # 预处理相邻点的距离
    for i in range(K - 1):
        adj_dist[i] = distance(path[i], path[i + 1])
    tot_dist = sum(adj_dist)

    # 对于中间缺少的点，特殊处理
    ans = []
    for i in range(K):
        if i == 0:
            ans.append(tot_dist - adj_dist[0])
        elif i == K - 1:
            ans.append(tot_dist - adj_dist[-1])  # 快速得到尾元素
        else:
            ans.append(
                tot_dist
                - adj_dist[i - 1]
                - adj_dist[i]
                + distance(path[i - 1], path[i + 1])
            )

    sys.stdout.write(" ".join(map(str, ans)))


if __name__ == "__main__":
    solve()
