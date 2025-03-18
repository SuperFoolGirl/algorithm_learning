// 当题目没有给哨兵节点时，我们可以创建虚拟哨兵节点
// 下面是一个无哨兵链表，使用虚拟哨兵的例子，包括初始化、排序、反转、销毁

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode // 这里不写ListNode会警告
{
    int val;
    struct ListNode *next;
} ListNode;

ListNode *listInit(ListNode *head)
{
    // 创建虚拟哨兵节点
    // head在这里是空指针 直接用
    head = (ListNode *)malloc(sizeof(ListNode));
    head->next = NULL;

    // 输入链表元素
    int n;
    scanf("%d", &n);

    ListNode *current = head; // 统一从哨兵开始
    for (int i = 0; i < n; i++)
    {
        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        scanf("%d", &new_node->val);
        current->next = new_node;
        current = new_node;
    }
    current->next = NULL;

    // 销毁临时哨兵
    ListNode *ret = head->next;
    free(head);
    return ret;
}

void print(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    puts("");
}

ListNode *listSort(ListNode *head)
{
    // 创建虚拟哨兵节点，这里head不能直接拿来用了
    ListNode *dummy = (ListNode *)malloc(sizeof(ListNode));
    dummy->next = head;

    ListNode *p = dummy->next;
    ListNode *p_prev = dummy;
    ListNode *q = NULL;

    while (p != NULL)
    {
        ListNode *r = dummy->next; // 不要写head，head可能被排序移走了
        ListNode *r_prev = dummy;

        while (r != p && r->val < p->val) // 这里尝试一下r->next->val
        {
            r_prev = r;
            r = r->next;
        }

        // 关于这里的讲解，参考sort_with_next.c
        // if (r != p)
        // {
        //     // 独立
        //     q = p;
        //     p_prev->next = p->next;
        //     p = p_prev; // 不可省略，最外层while循环要求走完整个链表，此时p被插入到别的位置去了，必须借助p0继续前进

        //     // 插入
        //     q->next = r;
        //     r_prev->next = q;
        // }
        // p_prev = p;
        // p = p->next;

        // 优化
        if (r != p)
        {
            q = p;
            p_prev->next = p->next;
            p = p_prev->next;

            q->next = r;
            r_prev->next = q;
        }
        else
        {
            p_prev = p;
            p = p->next;
        }
    }
    // 销毁虚拟哨兵
    head = dummy->next;
    free(dummy);
    return head;
}

ListNode *listReverse(ListNode *head)
{
    // 这个就不用虚拟哨兵了
    if (head == NULL || head->next == NULL)
        return head;

    ListNode *p_prev, *p;
    p = head->next;

    // 断开头节点
    head->next = NULL;

    while (p)
    {
        p_prev = head;
        head = p;
        p = p->next;
        head->next = p_prev;
    }
    return head;
}

void destroy(ListNode *head)
{
    while (head)
    {
        ListNode *del = head;
        head = head->next;
        free(del);
    }
}

int main()
{
    ListNode *head = NULL; // 只给了一个头指针

    head = listInit(head); // 初始化，按输入写入链表
    print(head);

    head = listSort(head); // 选择排序
    print(head);

    head = listReverse(head); // 反转
    print(head);

    destroy(head);
    return 0;
}