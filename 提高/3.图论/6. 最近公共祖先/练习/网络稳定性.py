import sys
from collections import deque

# 1.lca可以快速算出树上两点之间的最小距离
# 2.本题不是树，需要将图转成树——生成树算法
# 3.根据本题性质，需要构造最大生成树
# 4.大坑：本题图不一定连通


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    inf = float("inf")

    n, m, Q = ri(), ri(), ri()
    h = [[] for _ in range(n + 1)]
    e = [(ri(), ri(), ri()) for _ in range(m)]
    tr_e = []  # 储存最大生成树，读入邻接表h中
    p = list(range(n + 1))
    # 二叉树是深度最大的树取最坏情况，log2(1e5)=17
    fa = [[0] * 18 for _ in range(n + 1)]
    depth = [inf] * (n + 1)

    def find(x):
        if x != p[x]:
            p[x] = find(p[x])
        return p[x]

    def kruskal():
        cnt = 0
        e.sort(key=lambda x: -x[2])
        for u, v, w in e:
            pu, pv = find(u), find(v)
            if pu != pv:
                p[pu] = pv
                tr_e.append((u, v, w))
                cnt += 1
            if cnt == n - 1:
                break

    def bfs(start):
        q = deque([start])
        depth[0] = 0
        depth[start] = 1
        while q:
            u = q.popleft()
            for v, w in h[u]:
                if depth[v] > depth[u] + 1:
                    depth[v] = depth[u] + 1
                    q.append(v)
                    fa[v][0] = u
                    for k in range(1, 18):
                        anc = fa[v][k - 1]
                        fa[v][k] = fa[anc][k - 1]

    # 在求lca的过程中无法维护稳定性，因为lca是倍增的
    # 不过，一直向上走就可以找到lca(只有一个父亲)，干脆一会线性遍历了
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

    def get_st(u, t):
        res = inf
        while u != t:
            for v, w in h[u]:
                # 无向树找唯一父亲
                if depth[v] < depth[u]:
                    u = v
                    res = min(res, w)
                    break
        return res

    # 求最大生成树
    kruskal()

    # 建树
    for u, v, w in tr_e:
        h[u].append((v, w))
        h[v].append((u, w))

    # 预处理fa和depth
    # 注意图不连通，需要处理所有连通块
    for i in range(1, n + 1):
        if depth[i] == inf:
            bfs(i)

    while Q:
        Q -= 1
        x, y = ri(), ri()
        # 找lca；如果不连通，则无法走到
        if find(x) == find(y):
            t = lca(x, y)
            # 求路径x->t和y->t上的稳定性，即路径上的最小边权
            print(min(get_st(x, t), get_st(y, t)))
        else:
            print(-1)


if __name__ == "__main__":
    solve()
