#include <stdio.h>
#include <stdlib.h>
/* 栈的链表结构——单链表以“头节点”为头部，站立了起来。进栈的方法为头插法，栈底的next指针仍然为NULL */

/* 结构体 */
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
/* 初始化栈——建立头节点 */
Node *inistack()
{
    Node *S = (Node *)malloc(sizeof(Node)); /* 获得头指针S */
    S->data = 0;                            /* 头节点的data用来表明栈内元素个数 */
    S->next = NULL;                         /* next指向下面的元素 */
    return S;
}
/* 进栈——采用头插法 */
void push(Node *S, int data)
{
    Node *node = (Node *)malloc(sizeof(Node)); /* 新建结点 */
    node->data = data;
    /* 操作 */
    node->next = S->next;
    S->next = node;
    S->data++;
}
/* 判断栈是否为空 */
int isEmpty(Node *S)
{
    if (S->data == 0 || S->next == NULL)
    {
        return 1; /* 栈空返回1 */
    }
    else
    {
        return 0; /* 栈不空返回0 */
    }
}
/* 出栈 ——考虑是否栈空*/
int pop(Node *S)
{
    if (isEmpty(S))
    {
        return -1;
    }
    else
    {
        /* 出栈的操作 */
        Node *p = S->next;   /* 新建指针作为辅助 */
        int value = p->data; /* 得到即将出栈的值 */
        S->next = p->next;
        free(p);
        S->data--;
        return value;
    }
}
/* 获得栈顶的值 */
int gettop(Node *S)
{
    if (isEmpty(S))
    {
        return -1;
    }
    else
    {
        return S->next->data;
    }
}
/* 遍历打印 */
void printstack(Node *S)
{
    /* 同单链表的打印 */
    Node *node = S->next;
    while (node)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL ,");
    printf("栈内个数=%d\n", S->data);
}
int main()
{
    Node *S = inistack();
    push(S, 4);
    push(S, 3);
    push(S, 2);
    push(S, 1);
    printstack(S);
    if (isEmpty(S))
    {
        printf("栈为空\n");
    }
    else
    {
        printf("栈不为空\n");
    }
    int outtop = pop(S);
    printf("出栈的元素是%d\n", outtop);
    printf("当前栈：\n");
    printstack(S);

    int currennttop = gettop(S);
    printf("当前栈顶元素=%d", currennttop);
    return 0;
}
