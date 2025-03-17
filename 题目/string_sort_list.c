// 20250317考试题，边输入边按照字符串字典序排序

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

void listAddAndSort(ListNode *head, char *val)
{
    // 开辟结构体接收信息
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    strcpy(new_node->val, val); // 不写课设的话，我考试根本不会用
    new_node->next = NULL;

    // 从哨兵开始遍历链表，寻找插入点
    // 我考试的时候，一开始设置current为head->next，导致一系列问题
    // 一般来说，有哨兵，就用哨兵，且遍历模式多用current->next。next问题也讲过，便于插入，不用再引入prev
    ListNode *current = head;
    while (current->next != NULL && strcmp(current->next->val, val) < 0) // 这里注意参数顺序，从左到右的顺序判断，总是优先判断越界
        current = current->next;

    // 插入
    // 总是有头尾节点判断
    if (current->next == NULL) // current当前是头节点，或者是尾节点
    {
        current->next = new_node;
    }
    else
    {
        new_node->next = current->next;
        current->next = new_node;
    }
}

int main()
{
    ListNode *head = listInit(); // 哨兵初始化

    // 模拟考试场景，外部for循环输入
    int n;
    scanf("%d", &n);
    getchar();
    char str[20];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", str);
        getchar(); // 没注意考试的时候怎么处理的
        listAddAndSort(head, str);
    }

    print(head);
    destroy(head);
    return 0;
}