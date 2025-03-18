// 依照input_while_sort_list.c的方法，改写string_sort_list.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
    char val[20];
    struct ListNode *next;
} ListNode;

ListNode *listInit()
{
    ListNode *head = (ListNode *)malloc(sizeof(ListNode));
    head->next = NULL;
    head->val[0] = '\0'; // 不初始化的话，系统会给随机值
    return head;
}

void print(ListNode *head)
{
    ListNode *current = head->next; // 从第一个节点开始
    while (current)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
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
        scanf("%s", p->val);                      // 输入新节点的值
        getchar();

        // 寻找插入位置，p之前的节点们都排好序了
        // 因为p_prev从哨兵开始，所以p_prev->next处理头节点不会越界
        while (p_prev->next != NULL && strcmp(p_prev->next->val, p->val) < 0) // next->val，出循环时，p正好插入到p_prev后面
            p_prev = p_prev->next;

        if (p_prev->next == NULL) // 头/尾节点情况
        {
            p_prev->next = p;
            p->next = NULL;
        }
        else
        {
            p->next = p_prev->next;
            p_prev->next = p;
        }
        p_prev = head; // 重置p_prev
    }
}

int main()
{
    ListNode *head = listInit(); // 哨兵初始化

    // 边输入边排序
    listAddAndSort(head);

    print(head);
    destroy(head);
    return 0;
}