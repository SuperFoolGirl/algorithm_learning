import sys
from collections import deque

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    T = ri()
    
    while T:
        T -= 1

        # 注意，在本题多组输入样例下，为了避免使用静态列表，需要做一些调整
        # 对于每轮新数据，在已经输入n等参数后，重新创建各种列表(开销很小)
        # 这样就可以不设置N来记录点数上限了
        # 另外，为了避免函数传参，spfa需要定义在下方，而不能再写在上方了
        n, m1, m2 = ri(), ri(), ri()
        g = [[] for _ in range(n + 1)]
        dist = [0] * (n + 1)
        st = [False] * (n + 1)
        cnt = [0] * (n + 1)

        for _ in range(m1):
            u, v, w = ri(), ri(), ri()
            g[u].append((v, w))
            g[v].append((u, w))
        for _ in range(m2):
            u, v, w = ri(), ri(), ri()
            g[u].append((v, -w))

        def spfa():
            q = deque()
            for i in range(1, n + 1):
                q.append(i)
                st[i] = True

            while q:
                u = q.popleft()
                st[u] = False

                for v, w in g[u]:
                    if dist[v] > dist[u] + w:
                        dist[v] = dist[u] + w
                        cnt[v] = cnt[u] + 1

                        if cnt[v] >= n:
                            return True
                        
                        if not st[v]:
                            q.append(v)
                            st[v] = True

            return False
        
        if spfa():
            sys.stdout.write(f"YES\n")
        else:
            sys.stdout.write(f"NO\n")


if __name__ == "__main__":
    solve()
