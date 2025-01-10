// 这里选择排序思路是有问题的！由于节点交换的特性 根本就不是选择排序！老老实实写插入排序吧

#include <stdio.h>
#include <malloc.h>
struct cell
{ // 单链表结点结构体定义
    int x;
    struct cell *next;
};
struct cell *build(void)
{ // 新建单链表，并将建好的单链表首结点地址返回
    struct cell *head, *tmp, *tail;
    head = tmp = tail = NULL;
    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        if (!head)
        {
            tmp = (struct cell *)malloc(sizeof(struct cell));
            head = tmp;
            head->x = n;
            head->next = NULL;
            tail = head;
        }
        else
        {
            tmp = (struct cell *)malloc(sizeof(struct cell));
            tmp->x = n;
            tmp->next = NULL;
            tail->next = tmp;
            tail = tmp;
        }
        scanf("%d", &n);
    }
    return head; // 返回单链表头
}
struct cell *sort(struct cell *head)
{ // 递增排序链表，head是单链表首结点指针
    struct cell *p, *p0, *r, *r0, *q;
    p = p0 = r = r0 = q = NULL;
    p = head;
    struct cell *dummy = (struct cell *)malloc(sizeof(struct cell));
    dummy->x = -1, dummy->next = head;
    // 未优化的选择排序
    for (p0 = dummy, p = head; p; p0 = p0->next, p = p->next)
    {
        for (r0 = p, r = p->next; r; r0 = r0->next, r = r->next)
        {
            if (p->x > r->x)
            {
                if (p->next != r) // 不相邻两项交换
                {
                    // 先交换后继 用到tmp变量
                    q = p->next;
                    p->next = r->next;
                    r->next = q;

                    // 再交换前驱
                    p0->next = r;
                    r0->next = p;

                    // 最后是交换自身（或者说重命名）
                    p = p0->next;
                    r = r0->next;
                }
                else // 相邻两项交换(理论上 上一段代码也可以用于相邻两项 但不知为何跑不动)
                {
                    // 先改变后继
                    p->next = r->next;
                    r->next = p;

                    // 再改变前驱
                    p0->next = r;
                    r0 = r;

                    // 最后交换自身
                    p = p0->next;
                    r = r0->next;
                }
            }
        }
    }
    /*
    第一轮 p是指向head的
    如果p第一轮就发生了交换，那head就跟着交换了
    如果第一个数是最小的，整个排序过程中，没有发生任何交换，然后进入下一层外循环，p指向下一个
    此时head就与p没关系了，p不论怎么交换，前面总是满足dummy->next==head（在本程序中 每次循环都能保证最小的一个到最前面去，也就是
    没有优化过的选择排序，因此，后面的循环中也不会再出现和第一个节点交换的情况）
    而第一轮中 p0指向dummy，发生了交换，即使dummy的next变了，它的相对位置也没变（即p0没有发生位置交换）
    因此dummy的next永远指向最小的元素，不会跟着p0跑
    */
    head = dummy->next;
    // 也就是说 只要首元素是最小数，这句代码就可以不写

    free(dummy);
    return head;
}
/*  sort */

void print(struct cell *head)
{ // 打印整个单链表,head是单链表首结点指针
    struct cell *p = head;
    int cnt = 0;
    while (p)
    {
        if (cnt)
            printf(" ");
        cnt++;
        printf("%d", p->x);
        p = p->next;
    }
}
void release(struct cell *head)
{ // 释放单链表空间,head是单链表首结点指针
    struct cell *p;
    while (head)
    {
        p = head->next;
        free(head);
        head = p;
    }
}
int main(void)
{
    struct cell *head;
    head = build();
    if (head != NULL)
    {
        head = sort(head);
        print(head);
    }
    else
        printf("NULL");
    release(head);
    return 0;
}