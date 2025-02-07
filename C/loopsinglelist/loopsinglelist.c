#include <stdio.h>
#include <stdlib.h>
#define TRUE 1;
#define FALSE 0;
// 各个结点的结构
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 新建头节点
Node *inilist()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = L;
    return L;
}
// 头插法,和单链表没啥区别
void headinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = L->next;
    L->next = node;
    L->data++;
}
// 尾插法，和单链表差不多，同样需要尾指针
void tailinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    Node *p = L;
    /*使用while循环找到最后一个结点*/
    /* while (p->next != L)
    {
        p = p->next;
    } */
    /* 使用for循环找到最后一个结点 */
    for (int i = 0; i < L->data; i++)
    {
        p = p->next;
    }
    p->next = node;
    node->next = L;
    p = node;
    L->data++;
}

int deletelist(Node *L, int data)
{
    Node *pre = L;
    Node *node = L->next;
    while (node != L)
    {
        if (node->data == data)
        {
            Node *q = node;
            pre->next = q->next;
            node = q->next;
            free(q);
            L->data--;
        }
        else
        {
            pre = node;
            node = node->next;
        }
    }
    Node *q = L->next;
    // 用while循环进行遍历所有
    while (q != L)
    {
        if (q->data == data)
        {
            return FALSE;
        }
        q = q->next;
    }
    return TRUE;
}
// 遍历
void printList(Node *L)
{
    Node *node = L->next;
    while (node != L)
    {
        printf("node=%d\n", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
int main()
{
    Node *L = inilist();
    tailinsert(L, 1);
    tailinsert(L, 2);
    tailinsert(L, 3);
    tailinsert(L, 4);
    tailinsert(L, 5);
    headinsert(L, 8);
    headinsert(L, 7);
    headinsert(L, 8);
    headinsert(L, 9);
    headinsert(L, 10);
    printList(L);

    if (deletelist(L, 8))
    {
        printf("delete success!\n");
    }
    else
    {
        printf("delete unsuccess!\n");
    }
    printList(L);
    return 0;
}