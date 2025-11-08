// 归并代码的代码加一句即可

const int N = 1e5 + 10;

int q[N], tmp[N], cnt;

void merge_sort(int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    // 递归回来时，左右两部分各自是有序的
    // 如果出现了左边的数大于右边的数，说明出现了逆序对
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
            // 这里统计逆序对
            cnt += (mid - i + 1);  // 统计逆序对数量
        }
    }

    while (i <= mid) {
        tmp[k++] = q[i++];
    }

    while (j <= r) {
        tmp[k++] = q[j++];
    }

    for (i = l, j = 0; i <= r; ++i, ++j) {
        q[i] = tmp[j];
    }
}