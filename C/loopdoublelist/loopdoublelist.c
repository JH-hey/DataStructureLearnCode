#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/* 结构体内部的内容 */
typedef struct Node
{
    struct Node *prior;
    int data;
    struct Node *next;
} Node;
/* 初始化 */
Node *inilist()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = L;
    L->prior = L;
    return L;
}
/* 头插法 ——要考虑元素为0和不为0两种情况*/
void headinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 当元素个数！=0时的操作 */
    if (L->data != 0)
    {
        node->prior = L;
        node->next = L->next;
        L->next->prior = node;
        L->next = node;
        L->data++;
    }
    else /* 当元素个数==0时的操作 */
    {
        node->prior = L;
        node->next = L->next;
        L->prior = node;
        L->next = node;
        L->data++;
    }
}

/* 尾插法——需要尾指针 */
void tailinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 找到尾结点 */
    Node *p = L;
    while (p->next != L)
    {
        p = p->next;
    }
    /* 操作 */
    node->prior = p;
    node->next = p->next;
    p->next->prior = node;
    p->next = node;
    p = node;
    L->data++;
}
/* 删除——需要两个指针，目标指针+辅助脱身指针 */
int deletelist(Node *L, int data)
{
    Node *node = L->next;
    /* 开始挨个检查 */
    while (node != L)
    {
        if (node->data == data)
        {
            /* 删除操作 */
            Node *q = node;
            node->prior->next = q->next;
            node->next->prior = q->prior;
            node = q->next;
            free(q);
            L->data--;
        }
        else
        {
            /* 不符合套件后，继续往后走 */
            node = node->next;
        }
    }
    /* 验证 */
    Node *p = L->next;
    while (p != L)
    {
        if (p->data == data)
        {
            return FALSE;
        }
        p = p->next;
    }
    return TRUE;
}
/* 遍历打印 */
void printList(Node *L)
{
    Node *p = L->next;
    while (p != L) // 注意与未循环单链表的区别
    {
        printf("node=%d\n", p->data);
        p = p->next;
    }
    printf("元素个数=%d\n", L->data);
    printf("NULL\n");
}

int main()
{
    Node *L = inilist();
    headinsert(L, 5);
    headinsert(L, 4);
    headinsert(L, 3);
    headinsert(L, 2);
    headinsert(L, 1);
    tailinsert(L, 6);
    tailinsert(L, 7);
    tailinsert(L, 3);
    tailinsert(L, 9);
    tailinsert(L, 10);
    printList(L);
    if (deletelist(L, 3))
    {
        printf("delete success\n");
    }
    else
    {
        printf("delete unsuccess\n");
    }
    printList(L);
    return 0;
}