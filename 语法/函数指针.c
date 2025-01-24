// 结构体
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Node
{
    int key;
    char val[10];
};

bool cmp(char *a, char *b)
{
    if (strcmp(a, b) == 1)
    {
        return true;
    }
    return false;
}

void my_sort(struct Node *node, bool (*p)(char *, char *)) // 注意形参写法
{
    char tmp[10] = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if (p(node[j].val, node[j + 1].val)) // 调用点
            {
                strcpy(tmp, node[j].val);
                strcpy(node[j].val, node[j + 1].val);
                strcpy(node[j + 1].val, tmp);
            }
        }
    }
}

int main()
{
    struct Node node[5] = {{3, "lisi"}, {9, "wangwu"}, {9, "yuanshen"}, {34, "yuying"}, {12, "kkk"}};
    my_sort(node, cmp);
    for (int i = 0; i < 5; i++)
    {
        printf("%d %s\n", node[i].key, node[i].val);
    }
    return 0;
}