#include <stdlib.h>
#include <stdio.h>
typedef struct Node
{
    int data;
    struct Node *next;

} Node;
Node *initStack()
{
    Node *S = (Node *)malloc(sizeof(Node));
    S->data = 0;
    S->next = NULL;
    return S;
}

void push(Node *S, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = S->next;
    S->next = node;
    S->data++;
}

int isEmpty(Node *S)
{
    if (S->data == 0 || S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int pop(Node *S)
{
    if (isEmpty(S))
    {
        return -1;
    }
    else
    {
        int value;
        Node *p = S->next;
        S->next = p->next;
        value = p->data;
        free(p);
        S->data--;
        return value;
    }
}

void printstack(Node *S)
{
    Node *p = S->next;
    while (p != NULL)
    {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("栈内元素个数是：%d\n", S->data);
}
/*  开始转换*/
void conversion(Node *S, int n) /* 将头指针、被转换数输入 */
{
    while (n) /* 将余数依次压入栈内 */
    {
        push(S, n % 8);
        n = n / 8;
    }
    while (isEmpty(S) == 0) /* 出栈 */
    {
        printf("%d", pop(S));
    }
}
int main()
{
    Node *S = initStack();
    printf("输入要转换的数字:\n");
    int n;
    scanf("%d", &n);
    printf("8进制数:\n");
    conversion(S, n);
    return 0;
}