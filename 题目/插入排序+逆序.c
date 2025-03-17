#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

node *create(int n)
{
    node *head = NULL;
    node *p0, *p1;
    for (int i = 0; i < n; i++)
    {
        p1 = (node *)malloc(sizeof(node));
        scanf("%d", &p1->val);
        if (!i)
            head = p1;
        else
            p0->next = p1;
        p0 = p1;
    }
    p1->next = NULL; // 这句可以最后写 不用每次添加都补 毕竟只有尾结点需要next置为null
    return head;
}

node *sort(node *head)
{
    node *p, *p0, *r, *r0, *q;
    node *dummy =(node *)malloc(sizeof(node));
    dummy->next = head;
				
    p0 = dummy, p = dummy->next;

    while (p)
    {
        r0 = dummy, r = dummy->next;

        while (r->val < p->val && r != p)
        {
            r0 = r;
            r = r->next;
        }
        if (r != p)
        {
            // 独立
            q = p;
            p0->next = p->next;
            p = p0; //不可省略，最外层while循环要求走完整个链表，此时p被插入到别的位置去了，必须借助p0继续前进

            q->next = r;
            r0->next = q;
        }
        p0 = p;
        p = p->next;
    }

    free(dummy);
    return head;
}

node *reverse(node *head)
{
    node *p0, *p;
    if (head == NULL || head->next == NULL)
        return head;
    p = head->next;
    head->next = NULL;
    while (p)
    {
        p0 = head;
        head = p;
        p = p->next;
        head->next = p0;
    }
    return head;
}

void print(node *head)
{
    while (head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
}

void clear(node *head)
{
    while (head)
    {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    node *head = create(n);
    head = sort(head);
    head = reverse(head);
    print(head);
    clear(head);
    return 0;
}