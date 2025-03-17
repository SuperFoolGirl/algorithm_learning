// 边输入边排序
// 这里我们全部使用哨兵节点

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

ListNode *listInit()
{
    ListNode *head = (ListNode *)malloc(sizeof(ListNode));
    head->next = NULL;
    head->val = 0; // 不初始化的话，系统会给随机值
    return head;
}

void destroy(ListNode *head)
{
    // 从哨兵开始, 释放所有节点
    while (head)
    {
        ListNode *del = head;
        head = head->next;
        free(del);
    }
}

void print(ListNode *head)
{
    ListNode *current = head->next; // 从第一个节点开始
    while (current)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    puts("");
}

void listAddAndSort(ListNode *head)
{
    ListNode *p = NULL;
    ListNode *p_prev = head; // 负责寻找插入位置，从哨兵开始

    // 输入元素个数
    int n;
    scanf("%d", &n);

    // 创建链表
    for (int i = 0; i < n; i++)
    {
        p = (ListNode *)malloc(sizeof(ListNode)); // 创建新节点
        scanf("%d", &p->val);                     // 输入新节点的值

        // 寻找插入位置，p之前的节点们都排好序了
        // 因为p_prev从哨兵开始，所以p_prev->next处理头节点不会越界
        while (p_prev->next != NULL && p_prev->next->val < p->val) // next->val，出循环时，p正好插入到p_prev后面
            p_prev = p_prev->next;

        if (p_prev->next == NULL) // 头节点情况
        {
            p_prev->next = p;
            p->next = NULL;
        }
        else // 其他情况
        {
            // 之前插入都是借助r和r_prev，注意这里怎样只借助一个p_prev来完成插入，画图理解
            p->next = p_prev->next;
            p_prev->next = p;
        }
        p_prev = head; // 重置p_prev为哨兵，为下一个节点插入要重新遍历链表
    }

    // 不需要返回值，因为head是哨兵节点，不会被排序移走
}

int main()
{
    ListNode *head = listInit(); // 哨兵初始化

    // 边输入边排序
    listAddAndSort(head); // 有哨兵节点，头节点不会移动，不需要返回值

    print(head);
    destroy(head);
    return 0;
}