#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
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

int matching(Node *S)
{
    int flag = 1; /* 判断输入进来的是否与栈顶的元素相同，相同则为1，不相同说明匹配失败 */
    char ch;
    printf("输入匹配的字符\n");
    scanf("%c", &ch);
    while (ch != '#' && flag == 1) /* 以#作为输入结束。若此时flag=0则说明输入进来的右括号已经匹配不成功了，不需要继续匹配,退出循环 */
    {
        switch (ch)
        {
        case '[': /* 左括号，压入栈内 */
            push(S, ch);
            break;
        case '(': /* 左括号，压入栈内 */
            push(S, ch);
            break;
        case ']': /* 右括号，判断匹配？ */
            if (isEmpty(S) == 0 && gettop(S) == '[')
            {
                pop(S);
            }
            else
            {
                flag = 0; /* 匹配失败，直接退出循环。flag为0后，不需要再匹配了，直接退出循环 */
            }
            break;
        case ')': /* 右括号，判断匹配？ */
            if (isEmpty(S) == 0 && gettop(S) == '(')
            {
                pop(S);
            }
            else
            {
                flag = 0; /* 匹配失败，直接退出循环。flag为0后，不需要再匹配了，直接退出循环 */
            }
            break;
        default: /* 当输入的字符不满足上述时，说明有非法字符，肯定不匹配，因此直接flag=0 ,例如(())】*/
            flag = 0;
            break;
        }
        scanf("%c", &ch);
    }
    if (isEmpty(S) == 1 && flag == 1) /* 必须当栈内空时，且flag为1。要避免（【【】】这种情况被判断为正确 */
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int main()
{
    Node *S = initStack();
    if (matching(S))
    {
        printf("匹配成功\n");
    }
    else
    {
        printf("匹配失败\n");
    }
}