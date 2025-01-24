#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

node *init()
{
    node *head = (node *)malloc(sizeof(node));
    node *prev = NULL;
    int Val;
    int cnt = 0;                     // 计数元素个数
    while (scanf("%d", &Val) != EOF) // 空格持续输入 换行中止
    {
        if (!cnt)
        {
            head->val = Val;
            head->next = NULL;
            prev = head;
        }
        else
        {
            node *new = (node *)malloc(sizeof(node));
            new->val = Val;
            new->next = NULL;
            prev->next = new;
            prev = new;
        }
        cnt++;
    }
    return head;
}

void print(node *head)
{
    node *h = head; // 注意命名方式
    while (h)
    {
        printf("%d ", h->val);
        h = h->next;
    }
}

void clear(node *head)
{
    node *del = NULL;
    while (head)
    {
        del = head;
        head = head->next;
        free(del);
    }
}

int main()
{
    node *head = init();
    if (head)
        print(head);
    else
        printf("NULL");
    clear(head);
    return 0;
}