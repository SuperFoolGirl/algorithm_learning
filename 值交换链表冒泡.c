#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

node *init(int n)
{
    node *head, *p, *p0;
    for (int i = 0; i < n; i++)
    {
        p = (node *)malloc(sizeof(node));
        scanf("%d", &p->val);
        if (!i)
            head = p;
        else
            p0->next = p;
        p0 = p;
    }
    p->next = NULL;
    return head;
}

void sort(node *head, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        node *h = head;
        for (int j = 0; j < n - 1 - i; j++, h = h->next)
        {
            if (h->val > h->next->val)
            {
                int tmp = h->val;
                h->val = h->next->val;
                h->next->val = tmp;
            }
        }
    }
}

void print(node *head)
{
    while (head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
}

void release(node *head)
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
    node *head = init(n);
    sort(head, n);
    print(head);
    release(head);
    return 0;
}