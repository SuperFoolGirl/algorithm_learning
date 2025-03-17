// 尾插法创建链表
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

void listAdd(ListNode *head)
{
    // 从哨兵开始
    ListNode *current = head;
    while (current->next) // next，出循环时current指向最后一个节点
        current = current->next;

    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    scanf("%d", &new_node->val);
    current->next = new_node;
    new_node->next = NULL;
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

int main()
{
    ListNode *head = listInit(); // 哨兵初始化

    // 输入链表元素，尾插
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        listAdd(head);
    print(head);
    destroy(head);
    return 0;
}