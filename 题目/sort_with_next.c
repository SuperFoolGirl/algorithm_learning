// 探究next的用法，将插入排序改为next写法
// 当然，我们已经完成了边输入边插入排序（使用了next技巧），这里尝试单独的插入排序

// 之前在插入排序时，用r_prev和r来找到p的插入位置，将p插入到r_prev和r之间
// 通过 next和哨兵 优化，干掉r_prev，只用r来找到p的插入位置：遍历到r->next结束时，正好把p插在r的后面
// 简单来说，就是用r->next来代替r，r来代替r_prev，整体前移一位

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

    ListNode *current = head;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        scanf("%d", &new_node->val);
        current->next = new_node;
        current = new_node;
    }
    current->next = NULL;
    return head;
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

void listSort(ListNode *head)
{
    ListNode *p = head->next; // head是哨兵节点
    ListNode *p_prev = head;
    ListNode *q = NULL;

    while (p != NULL)
    {
        ListNode *r = head; // r用来代替r_prev，但必须从哨兵开始，否则没法用next。那天之所以失败就是这里的问题，考试前和考试时都犯了

        while (r->next != p && r->next->val < p->val)
            r = r->next;

        // if (r->next != p)
        // {
        //     // 讲一下这里的逻辑
        //     // 假设p_prev位于1，p位于2，p->next位于3：1->2->3
        //     // 独立之后，1->3
        //     // 这里把p独立除去之后，把p回退到1
        //     // 出了if之后，p向前推进到3，恰好符合
        //     // 但不得不说 写的一坨
        //     q = p;
        //     p_prev->next = p->next;
        //     p = p_prev; // 回退

        //     q->next = r->next;
        //     r->next = q;
        // }
        // p_prev = p;
        // p = p->next;

        // 这里提供一个优化
        // 修改if里对于p的操作，使得p不再需要回退。且此时p_prev本就位于合法位置
        // 如果不走if，正常双更新
        if (r->next != p)
        {
            q = p;
            p_prev->next = p->next;
            p = p_prev->next;

            q->next = r->next;
            r->next = q;
        }
        else
        {
            p_prev = p;
            p = p->next;
        }
    }
}

int main()
{
    ListNode *head = listInit();
    listSort(head);
    print(head);
    destroy(head);
    return 0;
}