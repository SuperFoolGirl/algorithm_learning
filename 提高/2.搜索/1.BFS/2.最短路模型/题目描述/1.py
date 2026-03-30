import sys
from collections import deque


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n = ri()
    g = [[ri() for _ in range(n)] for _ in range(n)]  # 创建即读入
    pre = [[-1] * (n) for _ in range(n)]              # 类似memset
    dx = [-1, 0, 1, 0]
    dy = [0, 1, 0, -1]

    def bfs(sx, sy):
        queue = deque([(sx, sy)])
        pre[sx][sy] = (0, 0)

        while queue:
            x, y = queue.popleft()
            for i in range(4):
                a, b = x + dx[i], y + dy[i]
                if a < 0 or a >= n or b < 0 or b >= n:
                    continue
                if g[a][b]:
                    continue
                if pre[a][b] != -1:
                    continue

                queue.append((a, b))
                pre[a][b] = (x, y)

    bfs(n - 1, n - 1)

    # 直接解包
    x, y = 0, 0
    while True:
        # f-string与write绝配，正好输出的是字符串
        sys.stdout.write(f"{x} {y}\n")
        if (x, y) == (n - 1, n - 1):
            break
        x, y = pre[x][y]


if __name__ == "__main__":
    solve()
