import sys
from collections import deque

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))
    rs = lambda: next(it)

    n, m = ri(), ri()
    g = [rs() for _ in range(n)]
    st = [[False] * (n) for _ in range(n)]

    def bfs(sx, sy):
        # 注意写法：参数为列表里嵌套一个元组
        queue = deque([(sx, sy)])
        st[sx][sy] = True

        while queue:
            x, y = queue.popleft()
            for i in range(x - 1, x + 2):
                for j in range(y - 1, y + 2):
                    if i == x and j == y:
                        continue
                    if i < 0 or i >= n or j < 0 or j >= n:
                        continue
                    if g[i][j] == '.' or st[i][j]:
                        continue
                    queue.append((i, j))
                    st[i][j] = True

    cnt = 0
    for i in range(n):
        for j in range(n):
            if g[i][j] == 'W' and not st[i][j]:
                bfs(i, j)
                cnt += 1

    sys.stdout.write(f"{cnt}\n")


if __name__ == "__main__":
    solve()
