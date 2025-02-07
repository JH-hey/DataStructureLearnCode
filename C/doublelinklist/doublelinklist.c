#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
// 每个结点的内容
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
    L->next = NULL;
    L->prior = NULL;
}

/* 头插法 */
void headinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 操作 */
    node->prior = L;
    node->next = L->next;
    if (L->data != 0) // 这里要注意，如果数据元素为0，即仅仅有头节点一个的话，此步骤不执行
    {
        L->next->prior = node;
    }
    L->next = node;
    L->data++;
}
/* 尾插法 */
void tailinsert(Node *L, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 找尾结点 ,需要一个指针*/
    Node *p = L;
    while (p->next != 0)
    {
        p = p->next;
    }
    /* 开始操作 */
    node->prior = p;
    node->next = p->next;
    p->next = node;
    p = node;
    L->data++;
}

/* 删除
    在单链表我们需要三个指针，目标指针，目标前指针，辅助脱身指针
    由于双链表中可以靠node->prior代替“目标前指针”，因此仅仅需要两个指针就可：目标指针+辅助脱身指针
 */
int deletelist(Node *L, int data)
{
    /* 目标指针 */
    Node *node = L->next;
    while (node)
    {
        if (node->data == data)
        {
            /* 删除操作 */
            Node *q = node; // 辅助脱身指针
            node->prior->next = q->next;
            node->next->prior = q->prior;
            node = q->next;
            free(q);
            L->data--;
        }
        else
        {
            node = node->next;
        }
    }
    /* 检验是否删除干净 */
    Node *p = L->next;
    while (p)
    {
        if (p->data == data)
        {
            return FALSE;
        }
        p = p->next;
    }
    return TRUE;
}
/* 遍历 */
void printList(Node *L)
{
    Node *node = L->next;
    while (node)
    {
        printf("node=%d\n", node->data);
        node = node->next;
    }
    printf("NULL\n");
    printf("数据元素=%d\n", L->data);
}

int main()
{
    Node *L = inilist();
    headinsert(L, 4);
    headinsert(L, 4);
    headinsert(L, 3);
    headinsert(L, 2);
    headinsert(L, 1);
    tailinsert(L, 6);
    tailinsert(L, 7);
    tailinsert(L, 8);
    tailinsert(L, 9);
    tailinsert(L, 10);
    printList(L);
    if (deletelist(L, 4))
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
