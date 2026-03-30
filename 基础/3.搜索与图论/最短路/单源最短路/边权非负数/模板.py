import sys
import heapq  # python只有小根堆


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    # g[a]存储若干个二元组(b,c)，表示a->b的边权为c
    g = [[] for _ in range(n + 1)]

    def dijkstra(start):
        # dist列表的元素是基础类型，即不可变对象，直接浅拷贝即可
        # 换句话说，就是可以统一赋值
        # float("inf")表示正无穷，float("-inf")表示负无穷
        # 创建一个含有n+1个元素为无穷大的列表
        dist = [float("inf")] * (n + 1)
        dist[start] = 0

        # 定义heap列表作为堆，它只是列表
        heap = [(0, start)]
        while heap:
            d, u = heapq.heappop(heap)

            if u == n:
                break
            if d > dist[u]:
                continue

            for v, w in g[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    heapq.heappush(heap, (dist[v], v))
        return dist[n]

    for _ in range(m):
        a, b, c = ri(), ri(), ri()
        # g[i]->[(a,b),(c,d),...]
        g[a].append((b, c))

    res = dijkstra(1)
    # 三元表达式
    print(res if res != float("inf") else -1)


if __name__ == "__main__":
    solve()
